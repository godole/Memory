#include "PlayLayerMainLogic.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "UpdateManager.h"
#include "Box2dSprite.h"
#include "DataManager.h"
#include "Behavior.h"
#include "BackgroundCloud.h"
#include "SimpleAudioEngine.h"
#include "ScrollSprite.h"
#include "Player.h"
#include "ObjectFactory.h"
#include "LayerDefine.h"
#include <string>
#include "GameSharing.h"

using namespace ui;
using namespace std;
using namespace CocosDenshion;

bool PlayLayerMainLogic::init()
{
	if (!Layer::init())
	{
		return false;
	}

	m_bIsJumpButtonTouched = false;
	m_bIsLeftButtonTouched = false;
	m_bIsRightButtonTouched = false;

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	this->setTouchEnabled(true);

	UpdateManager::getInstance()->Release();
	CScrollManager::getInstance()->Release();
	CObjectManager::getInstance()->Init();
	settingKeyboardManager();

	b2Init();
	scheduleUpdate();

	m_pPlayer = shared_ptr<CPlayer>(new CPlayer);
	m_pPlayer->Init(this, m_pWorld, 10, CHARACTER_ZORDER);
	m_pPlayer->setPositionTo(ccp(50, 300));
	UpdateManager::getInstance()->Insert(m_pPlayer);
	CScrollManager::getInstance()->Insert(m_pPlayer);

	m_pCharParticleNode = CCNode::create();
	this->addChild(m_pCharParticleNode, CHARACTER_ZORDER, CHAR_PARTICLE_NODE);

	m_pScreenParticleNode = CCNode::create();
	this->addChild(m_pScreenParticleNode, PARTICLE_ZORDER, SCR_PARTICLE_NODE);

	auto button = CSLoader::createNode("ui/button.csb");
	this->addChild(button, UI_ZORDER);

	m_pLeftMoveButton = (Button*)(button->getChildByName("left"));
	m_pLeftMoveButton->addTouchEventListener(CC_CALLBACK_2(PlayLayerMainLogic::leftButtonCallback, this));

	m_pRightMoveButton = (Button*)(button->getChildByName("right"));
	m_pRightMoveButton->addTouchEventListener(CC_CALLBACK_2(PlayLayerMainLogic::rightButtonCallback, this));

	m_pJumpButton = (Button*)(button->getChildByName("jump"));
	m_pJumpButton->addTouchEventListener(CC_CALLBACK_2(PlayLayerMainLogic::jumpButtonCallback, this));

	auto film = CCSprite::create("ui/film.png");
	film->setPosition(ccp(220, 650));
	this->addChild(film, UI_ZORDER);

	stringstream s;
	s << m_pPlayer->getLatestCount();
	string ss = s.str();
	m_pPlayerBehaviorCount = Label::createWithTTF("fonts/arial.ttf", ss);
	m_pPlayerBehaviorCount->setPosition(ccp(85, 650));
	m_pPlayerBehaviorCount->setColor(Color3B(0, 0, 0));
	m_pPlayerBehaviorCount->setSystemFontSize(40);
	this->addChild(m_pPlayerBehaviorCount, UI_ZORDER);
	
	auto pTempSprite = CCSprite::create(CDataManager::getInstance()->getDestinationData()->m_szTextureName);
	pTempSprite->setPosition(CDataManager::getInstance()->getDestinationData()->m_vPosition);
	pTempSprite->setAnchorPoint(ccp(0.5, 0));
	this->addChild(pTempSprite);

	m_pDestination = shared_ptr<CScrollSprite>(new CScrollSprite);
	m_pDestination->Init(pTempSprite);
	CScrollManager::getInstance()->Insert(m_pDestination);

	m_pMenuBackground = CCSprite::create("ui/stage_dead.png");
	m_pMenuBackground->setAnchorPoint(ccp(0, 0));
	m_pMenuBackground->setVisible(false);
	this->addChild(m_pMenuBackground, MENU_ZORDER);

	m_pRetryButton = CCSprite::create("ui/menu_dead_retry.png");
	m_pRetryButton->setPosition(ccp(visibleSize.width / 2 - 300, visibleSize.height / 2));
	m_pRetryButton->setVisible(false);
	this->addChild(m_pRetryButton, MENU_ZORDER);

	m_pGoHomeButton = CCSprite::create("ui/menu_dead_home.png");
	m_pGoHomeButton->setPosition(ccp(visibleSize.width / 2 + 300, visibleSize.height / 2));
	m_pGoHomeButton->setVisible(false);
	this->addChild(m_pGoHomeButton, MENU_ZORDER);

	ObjInit();
	BGInit();

	m_bIsEnd = false;
	m_bIsPaused = false;

	return true;
}

void PlayLayerMainLogic::b2Init()
{
	b2Vec2 gravity;
	gravity.Set(0.0f, -15.0f);
	m_pWorld = new b2World(gravity);
	m_pWorld->SetAllowSleeping(true);
	m_pWorld->SetContinuousPhysics(true);

	this->schedule(schedule_selector(PlayLayerMainLogic::b2tick));
}

void PlayLayerMainLogic::settingKeyboardManager()
{
	auto* keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(PlayLayerMainLogic::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(PlayLayerMainLogic::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	setKeypadEnabled(true);
}

void PlayLayerMainLogic::settingTouchDispatcher()
{
	auto listener = EventListenerTouchAllAtOnce::create();

	listener->onTouchesBegan = CC_CALLBACK_2(PlayLayerMainLogic::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(PlayLayerMainLogic::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(PlayLayerMainLogic::onTouchesEnded, this);
	listener->onTouchesCancelled = CC_CALLBACK_2(PlayLayerMainLogic::onTouchesCancelled, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void PlayLayerMainLogic::b2tick(float dt)
{
	int32 velocityIterator = 8;
	int32 positionIterator = 3;

	m_pWorld->Step(dt, velocityIterator, positionIterator);

	for (b2Body *b = m_pWorld->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != NULL)
		{
			CCSprite *spriteData = (CCSprite *)b->GetUserData();
			spriteData->setPosition(ccp(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
			spriteData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}
}

void PlayLayerMainLogic::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		m_bIsLeftButtonTouched = true;
		m_pPlayer->Move(md_Left);
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		m_bIsRightButtonTouched = true;
		m_pPlayer->Move(md_Right);
		break;

	case EventKeyboard::KeyCode::KEY_SPACE:
		m_pPlayer->Jump();
		break;

	case EventKeyboard::KeyCode::KEY_F12:
		GoNextStage();
		break;
	}
}

void PlayLayerMainLogic::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		m_bIsLeftButtonTouched = false;
		m_pPlayer->Stop();
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		m_bIsRightButtonTouched = false;
		m_pPlayer->Stop();
		break;

	case EventKeyboard::KeyCode::KEY_BACK :
	case EventKeyboard::KeyCode::KEY_BACKSPACE :
		ShowDeadMenu();
		break;
	}
}

void PlayLayerMainLogic::GoNextStage()
{
	int Score;
	if (m_pPlayer->getCurrentBehaviorCount() < 6)
		Score = 3;

	else if (m_pPlayer->getCurrentBehaviorCount() < 8)
		Score = 2;

	else
		Score = 1;

	/*if (CDataManager::getInstance()->getCurrentStageScoreSum() >= 30)
		GameSharing::UnlockAchivement(2);

	else if (CDataManager::getInstance()->getCurrentStageScoreSum() >= 20)
		GameSharing::UnlockAchivement(3);

	else if (CDataManager::getInstance()->getCurrentStageScoreSum() >= 10)
		GameSharing::UnlockAchivement(4);*/

	Release();
	CSceneManager::getInstance()->ChangeScene(ESceneType::e_SceneSelectStage);
	CDataManager::getInstance()->SavePlayerData();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void PlayLayerMainLogic::update(float dt)
{
	ObjUpdate();
	if (m_pDestination->getSpritePtr()->getBoundingBox().containsPoint(m_pPlayer->getPosition()) && !m_bIsEnd)
	{
		GoNextStage();
	}

	if (m_bIsLeftButtonTouched)
		m_pPlayer->Move(MoveDirection::md_Left);

	if (m_bIsRightButtonTouched)
		m_pPlayer->Move(MoveDirection::md_Right);

	if (m_pPlayer->Isfall())
		ShowDeadMenu();

	UpdateManager::getInstance()->Updating();
	Scroll();
}

void PlayLayerMainLogic::onTouchesBegan(const vector<Touch*>&touches, Event* event)
{
	for (auto itr = touches.begin(); itr != touches.end(); itr++)
	{
		CCPoint touchPos = (*itr)->getLocation();

		if (!m_bIsPaused)
		{
			for (int i = 0; i < m_arrObject.size(); i++)
			{
				if (m_pPlayer->Action(m_arrObject[i]->getBehaviorPtr(), touchPos))
				{
					stringstream s;
					s << m_pPlayer->getLatestCount();
					string ss = s.str();
					m_pPlayerBehaviorCount->setString(ss);
					break;
				}
			}
		}

		if (m_pRetryButton->getBoundingBox().containsPoint(touchPos) &&
			m_bIsPaused)
		{
			Behavior::k_bIsDoing = false;
			scheduleUpdate();
			m_pPlayer->setStateToBefore();
			CloseDeadMenu();
		}

		if (m_pGoHomeButton->getBoundingBox().containsPoint(touchPos) &&
			m_bIsPaused)
		{
			GoNextStage();
			Director::sharedDirector()->resume();
		}
	}
}

void PlayLayerMainLogic::onTouchesMoved(const vector<Touch*>&touches, Event* event)
{
	for (auto itr = touches.begin(); itr != touches.end(); itr++)
	{
		CCPoint touchPos = (*itr)->getLocation();
	}
}

void PlayLayerMainLogic::onTouchesEnded(const vector<Touch*>&touches, Event* event)
{
	for (auto itr = touches.begin(); itr != touches.end(); itr++)
	{
		CCPoint touchPos = (*itr)->getLocation();
	}
}

void PlayLayerMainLogic::onTouchesCancelled(const vector<Touch*>&touches, Event* event)
{

}

void PlayLayerMainLogic::Scroll()
{
	Vec2 cv = visibleSize / 2;
	Vec2 sv = cv - m_pPlayer->getPosition();
	sv = sv / 9;

	if (m_pBackground->getSpritePtr()->getPositionX() + sv.x > 0)
	{
		sv.x = -m_pBackground->getSpritePtr()->getPositionX();
	}

	if (m_pBackground->getSpritePtr()->getPositionX() + m_pBackground->getSpritePtr()->getContentSize().width + sv.x < visibleSize.width)
	{
		sv.x = visibleSize.width - m_pBackground->getSpritePtr()->getBoundingBox().getMaxX();
	}

	if (m_pBackground->getSpritePtr()->getPositionY() + sv.y > 0)
	{
		sv.y = -m_pBackground->getSpritePtr()->getPositionY();
	}

	m_pZeroWall->setPositionBy(sv);
	m_pMaxWall->setPositionBy(sv);

	m_pBGParticleNode->setPosition(m_pBGParticleNode->getPosition() + sv);
	m_pObjParticleNode->setPosition(m_pObjParticleNode->getPosition() + sv);
	m_pCharParticleNode->setPosition(m_pCharParticleNode->getPosition() + sv);
	m_pScreenParticleNode->setPosition(m_pScreenParticleNode->getPosition() + sv);

	CScrollManager::getInstance()->Scroll(sv);
}

CBox2dSprite* PlayLayerMainLogic::CreateWall(string filename, CCPoint pos)
{
	auto pWall1 = CCSprite::create(filename);
	pWall1->setPosition(pos);
	this->addChild(pWall1);

	auto wall = new CBox2dSprite;
	wall->Init(pWall1, m_pWorld, b2BodyType::b2_staticBody, ccp(0.5, 0));

	return wall;
}

void PlayLayerMainLogic::ShowDeadMenu()
{
	m_pMenuBackground->setVisible(true);
	m_pRetryButton->setVisible(true);
	m_pGoHomeButton->setVisible(true);

	unscheduleUpdate();

	m_bIsPaused = true;

	m_pLeftMoveButton->setEnabled(false);
	m_pRightMoveButton->setEnabled(false);
	m_pJumpButton->setEnabled(false);

	m_pPlayer->Stop();
}

void PlayLayerMainLogic::CloseDeadMenu()
{
	m_pMenuBackground->setVisible(false);
	m_pRetryButton->setVisible(false);
	m_pGoHomeButton->setVisible(false);

	scheduleUpdate();

	m_bIsPaused = false;

	m_pLeftMoveButton->setEnabled(true);
	m_pRightMoveButton->setEnabled(true);
	m_pJumpButton->setEnabled(true);
}

void PlayLayerMainLogic::Release()
{
	m_bIsEnd = true;
	m_pPlayer->Stop();
	this->unschedule(schedule_selector(PlayLayerMainLogic::update));
	CScrollManager::getInstance()->Release();
	UpdateManager::getInstance()->Release();
	m_arrObject.clear();
	CObjectManager::getInstance()->Release();
	CDataManager::getInstance()->Release();
	Behavior::k_bIsDoing = false;
}

void PlayLayerMainLogic::leftButtonCallback(Ref* sender, Widget::TouchEventType type)
{
	if (m_bIsPaused)
		return;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		m_bIsLeftButtonTouched = true;
		m_pPlayer->PlayMoveAnimation();
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		m_pPlayer->Stop();
		m_bIsLeftButtonTouched = false;
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED :
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		m_pPlayer->Stop();
		m_bIsLeftButtonTouched = false;
		break;
	default:
		break;
	}
}

void PlayLayerMainLogic::rightButtonCallback(Ref* sender, Widget::TouchEventType type)
{
	if (m_bIsPaused)
		return;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		m_bIsRightButtonTouched = true;
		m_pPlayer->PlayMoveAnimation();
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		m_pPlayer->Stop();
		m_bIsRightButtonTouched = false;
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		m_pPlayer->Stop();
		m_bIsRightButtonTouched = false;
		break;
	default:
		break;
	}
}

void PlayLayerMainLogic::jumpButtonCallback(Ref* sender, Widget::TouchEventType type)
{
	if (m_bIsPaused)
		return;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		m_pPlayer->Jump();
		break;
	default:
		break;
	}
}

void PlayLayerMainLogic::draw(Renderer *renderer, const kmMat4& transform, bool transformUpdated)
{
	glEnableVertexAttribArray(0);
	m_pWorld->DrawDebugData();
}

void PlayLayerMainLogic::ObjInit()
{
	auto factory = CObjectFactory::getInstance();
	auto mgr = CDataManager::getInstance();
	auto profile = m_pPlayer->getActorProfile();

	for (auto itr = mgr->getBoxData()->begin(); itr != mgr->getBoxData()->end(); itr++)
	{
		auto box = factory->CreateBox(this, m_pWorld, profile, *itr);
		m_arrObject.push_back(box);
	}

	ObjectInit();

	for (auto itr = mgr->getPedData()->begin(); itr != mgr->getPedData()->end(); itr++)
	{
		factory->CreatePed(this, m_pWorld, *itr);
	}

	for (auto itr = mgr->getGroundData()->begin(); itr != mgr->getGroundData()->end(); itr++)
	{
		factory->CreateGround(this, m_pWorld, *itr);
	}

	m_pZeroWall = CreateWall("object/20.png", ccp(0, 100));
	m_pMaxWall = CreateWall("object/20.png", ccp(1920, 100));

	m_pObjParticleNode = CCNode::create();
	this->addChild(m_pObjParticleNode, OBJECT_ZORDER, OBJ_PARTICLE_NODE);
}

void PlayLayerMainLogic::BGInit()
{
	BackgroundInit();

	m_pBGParticleNode = CCNode::create();
	this->addChild(m_pBGParticleNode, BACKGROUND_ZORDER, BG_PARTICLE_NODE);
}

void PlayLayerMainLogic::ObjUpdate()
{
	m_pBackgroundCloud->Update();

	ObjectUpdate();
}
