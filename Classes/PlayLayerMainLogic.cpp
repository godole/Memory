#include "PlayLayerMainLogic.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "UpdateManager.h"
#include "Box2dSprite.h"
#include "DataManager.h"
#include "Behavior.h"
#include "ui\CocosGUI.h"
#include "SimpleAudioEngine.h"

using namespace ui;
using namespace CocosDenshion;


void PlayLayerMainLogic::LayerInit()
{
	CScrollManager::getInstance()->Release();
	CObjectManager::getInstance()->Init();
	settingKeyboardManager();

	b2Init();
	scheduleUpdate();

	m_LayerData.m_pPlayer = shared_ptr<CPlayer>(new CPlayer);
	m_LayerData.m_pPlayer->Init(this, m_LayerData.m_pWorld, 1);
	m_LayerData.m_pPlayer->setPositionTo(ccp(50, 300));
	UpdateManager::getInstance()->Insert(m_LayerData.m_pPlayer);
	CScrollManager::getInstance()->Insert(m_LayerData.m_pPlayer);

	m_pParticleLayer = CCLayer::create();
	this->addChild(m_pParticleLayer, 3);

	m_bIsJumpButtonTouched = false;
	m_bIsLeftButtonTouched = false;
	m_bIsRightButtonTouched = false;

	auto button = CSLoader::createNode("ui/button.csb");
	this->addChild(button, 3);

	auto leftButton = (Button*)(button->getChildByName("left"));
	leftButton->addTouchEventListener(CC_CALLBACK_2(PlayLayerMainLogic::leftButtonCallback, this));

	auto rightButton = (Button*)(button->getChildByName("right"));
	rightButton->addTouchEventListener(CC_CALLBACK_2(PlayLayerMainLogic::rightButtonCallback, this));

	auto jumpButton = (Button*)(button->getChildByName("jump"));
	jumpButton->addTouchEventListener(CC_CALLBACK_2(PlayLayerMainLogic::jumpButtonCallback, this));

	auto film = CCSprite::create("ui/film.png");
	film->setPosition(ccp(170, 650));
	this->addChild(film, 3);

	m_pLayerData = &m_LayerData;

	m_pZeroWall = CreateWall("object/20.png", ccp(0, 100));
	m_pMaxWall = CreateWall("object/20.png", ccp(1920, 100));

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
	this->addChild(m_pMenuBackground, 4);

	m_pRetryButton = CCSprite::create("ui/menu_dead_retry.png");
	m_pRetryButton->setPosition(ccp(visibleSize.width / 2 - 300, visibleSize.height / 2));
	m_pRetryButton->setVisible(false);
	this->addChild(m_pRetryButton, 4);

	m_pGoHomeButton = CCSprite::create("ui/menu_dead_home.png");
	m_pGoHomeButton->setPosition(ccp(visibleSize.width / 2 + 300, visibleSize.height / 2));
	m_pGoHomeButton->setVisible(false);
	this->addChild(m_pGoHomeButton, 4);

	m_bIsEnd = false;
	m_bIsPaused = false;
}

void PlayLayerMainLogic::b2Init()
{
	b2Vec2 gravity;
	gravity.Set(0.0f, -15.0f);
	m_LayerData.m_pWorld = new b2World(gravity);
	m_LayerData.m_pWorld->SetAllowSleeping(true);
	m_LayerData.m_pWorld->SetContinuousPhysics(true);

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

	m_LayerData.m_pWorld->Step(dt, velocityIterator, positionIterator);

	for (b2Body *b = m_LayerData.m_pWorld->GetBodyList(); b; b = b->GetNext())
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
		m_LayerData.m_pPlayer->Move(md_Left);
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		m_bIsRightButtonTouched = true;
		m_LayerData.m_pPlayer->Move(md_Right);
		break;

	case EventKeyboard::KeyCode::KEY_SPACE:
		m_LayerData.m_pPlayer->Jump(m_pParticleLayer);
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
		m_LayerData.m_pPlayer->Stop();
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		m_bIsRightButtonTouched = false;
		m_LayerData.m_pPlayer->Stop();
		break;

	case EventKeyboard::KeyCode::KEY_BACK :
	case EventKeyboard::KeyCode::KEY_BACKSPACE :
			ShowDeadMenu();
		break;
	}
}

void PlayLayerMainLogic::GoNextStage()
{
	Release();
	CSceneManager::getInstance()->ChangeScene(ESceneType::e_SceneSelectStage);
	CDataManager::getInstance()->SavePlayerData();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void PlayLayerMainLogic::update(float dt)
{
	if (m_pDestination->getSpritePtr()->getBoundingBox().containsPoint(m_LayerData.m_pPlayer->getPosition()) && !m_bIsEnd)
	{
		GoNextStage();
	}

	if (m_bIsLeftButtonTouched)
		m_LayerData.m_pPlayer->Move(MoveDirection::md_Left);

	if (m_bIsRightButtonTouched)
		m_LayerData.m_pPlayer->Move(MoveDirection::md_Right);

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
			for (int i = 0; i < m_pLayerData->m_arrObject.size(); i++)
			{
				if (m_pLayerData->m_pPlayer->Action(m_pLayerData->m_arrObject[i]->getBehaviorPtr(), touchPos))
					break;
			}
		}

		if (m_pRetryButton->getBoundingBox().containsPoint(touchPos) &&
			m_bIsPaused)
		{
			Behavior::k_bIsDoing = false;
			scheduleUpdate();
			m_pLayerData->m_pPlayer->setStateToBefore();
			CloseDeadMenu();
		}

		if (m_pGoHomeButton->getBoundingBox().containsPoint(touchPos) &&
			m_bIsPaused)
		{
			GoNextStage();
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
	Vec2 sv = cv - m_LayerData.m_pPlayer->getPosition();
	sv = sv / 9;

	if (m_LayerData.m_pBackground->getSpritePtr()->getPositionX() + sv.x > 0)
	{
		sv.x = -m_LayerData.m_pBackground->getSpritePtr()->getPositionX();
	}

	if (m_LayerData.m_pBackground->getSpritePtr()->getPositionX() + m_LayerData.m_pBackground->getSpritePtr()->getContentSize().width + sv.x < visibleSize.width)
	{
		sv.x = visibleSize.width - m_LayerData.m_pBackground->getSpritePtr()->getBoundingBox().getMaxX();
	}

	if (m_LayerData.m_pBackground->getSpritePtr()->getPositionY() + sv.y > 0)
	{
		sv.y = -m_LayerData.m_pBackground->getSpritePtr()->getPositionY();
	}

	m_pZeroWall->setPositionBy(sv);
	m_pMaxWall->setPositionBy(sv);

	m_pParticleLayer->setPosition(m_pParticleLayer->getPosition() + sv);
	CScrollManager::getInstance()->Scroll(sv);
}

CBox2dSprite* PlayLayerMainLogic::CreateWall(string filename, CCPoint pos)
{
	auto pWall1 = CCSprite::create(filename);
	pWall1->setPosition(pos);
	this->addChild(pWall1);

	auto wall = new CBox2dSprite;
	wall->Init(pWall1, m_pLayerData->m_pWorld, b2BodyType::b2_staticBody, ccp(0.5, 0));

	return wall;
}

void PlayLayerMainLogic::ShowDeadMenu()
{
	m_pMenuBackground->setVisible(true);
	m_pRetryButton->setVisible(true);
	m_pGoHomeButton->setVisible(true);

	unscheduleUpdate();

	m_bIsPaused = true;
}

void PlayLayerMainLogic::CloseDeadMenu()
{
	m_pMenuBackground->setVisible(false);
	m_pRetryButton->setVisible(false);
	m_pGoHomeButton->setVisible(false);

	scheduleUpdate();

	m_bIsPaused = false;
}

void PlayLayerMainLogic::Release()
{
	m_bIsEnd = true;
	m_LayerData.m_pPlayer->Stop();
	this->unschedule(schedule_selector(PlayLayerMainLogic::update));
	CScrollManager::getInstance()->Release();
	UpdateManager::getInstance()->Release();
	m_LayerData.m_arrObject.clear();
	CObjectManager::getInstance()->Release();
	CDataManager::getInstance()->Release();
	Behavior::k_bIsDoing = false;
}

void PlayLayerMainLogic::leftButtonCallback(Ref* sender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		m_bIsLeftButtonTouched = true;
		m_pLayerData->m_pPlayer->PlayMoveAnimation();
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		m_pLayerData->m_pPlayer->Stop();
		m_bIsLeftButtonTouched = false;
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED :
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		m_pLayerData->m_pPlayer->Stop();
		m_bIsLeftButtonTouched = false;
		break;
	default:
		break;
	}
}

void PlayLayerMainLogic::rightButtonCallback(Ref* sender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		m_bIsRightButtonTouched = true;
		m_pLayerData->m_pPlayer->PlayMoveAnimation();
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		m_pLayerData->m_pPlayer->Stop();
		m_bIsRightButtonTouched = false;
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		m_pLayerData->m_pPlayer->Stop();
		m_bIsRightButtonTouched = false;
		break;
	default:
		break;
	}
}

void PlayLayerMainLogic::jumpButtonCallback(Ref* sender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		m_pLayerData->m_pPlayer->Jump(m_pParticleLayer);
		break;
	default:
		break;
	}
}