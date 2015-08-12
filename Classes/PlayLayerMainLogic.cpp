#include "PlayLayerMainLogic.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "UpdateManager.h"
#include "Box2dSprite.h"
#include "DataManager.h"
#include "Behavior.h"


void PlayLayerMainLogic::LayerInit()
{
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

	m_pLeftMoveButton = new CButton;
	m_pLeftMoveButton->Init(this, "ui/left_on.png", "ui/left_off.png", Vec2(100, 80), 3);
	m_pLeftMoveButton->m_ButtonOnFunc = [&]{
		m_bIsLeftButtonTouched = true;
		m_pLayerData->m_pPlayer->PlayMoveAnimation();
	};

	m_pLeftMoveButton->m_ButtonOffFunc = [&]{
		m_pLayerData->m_pPlayer->Stop();
		m_bIsLeftButtonTouched = false;
	};

	m_pRightMoveButton = new CButton;
	m_pRightMoveButton->Init(this, "ui/right_on.png", "ui/right_off.png", Vec2(185, 80), 3);
	m_pRightMoveButton->m_ButtonOnFunc = [&]{
		m_bIsRightButtonTouched = true;
		m_pLayerData->m_pPlayer->PlayMoveAnimation();
	};

	m_pRightMoveButton->m_ButtonOffFunc = [&]{
		m_pLayerData->m_pPlayer->Stop();
		m_bIsRightButtonTouched = false;
	};

	//Vec2(1100, 80)
	m_pJumpButton = new CButton;
	m_pJumpButton->Init(this, "ui/jump_on.png", "ui/jump_off.png", Vec2(1100, 80), 3);
	m_pJumpButton->m_ButtonOnFunc = [&]{
		m_pLayerData->m_pPlayer->Jump(m_pParticleLayer);
	};
	m_pJumpButton->m_ButtonOffFunc = []{};

	auto film = CCSprite::create("ui/film.png");
	film->setPosition(ccp(200, 600));
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

	m_bIsEnd = false;
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
	}
}

void PlayLayerMainLogic::GoNextStage()
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
	CSceneManager::getInstance()->ChangeScene(ESceneType::e_SceneTitle);
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

		m_pLeftMoveButton->OnTouchBegan(touchPos);
		m_pRightMoveButton->OnTouchBegan(touchPos);
		m_pJumpButton->OnTouchBegan(touchPos);

		for (int i = 0; i < m_pLayerData->m_arrObject.size(); i++)
		{
			if (m_pLayerData->m_pPlayer->Action(this, m_pLayerData->m_arrObject[i]->getBehaviorPtr(), touchPos))
				break;
		}
	}
}

void PlayLayerMainLogic::onTouchesMoved(const vector<Touch*>&touches, Event* event)
{
	for (auto itr = touches.begin(); itr != touches.end(); itr++)
	{
		CCPoint touchPos = (*itr)->getLocation();

		m_pLeftMoveButton->OnTouchMoved(touchPos);
		m_pRightMoveButton->OnTouchMoved(touchPos);
		m_pJumpButton->OnTouchMoved(touchPos);
	}
}

void PlayLayerMainLogic::onTouchesEnded(const vector<Touch*>&touches, Event* event)
{
	for (auto itr = touches.begin(); itr != touches.end(); itr++)
	{
		CCPoint touchPos = (*itr)->getLocation();

		m_pLeftMoveButton->OnTouchEnded(touchPos);
		m_pRightMoveButton->OnTouchEnded(touchPos);
		m_pJumpButton->OnTouchEnded(touchPos);
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