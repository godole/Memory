#include "Scene_Play.h"

//Define
#include "LayerDefine.h"
#include "EDirection.h"

//Objects
#include "Things.h"
#include "Rail.h"
#include "ScrollSprite.h"
#include "Box2dSprite.h"

//interface
#include "IScroll.h"

//Manager
#include "DataManager.h"
#include "UpdateManager.h"
#include "ScrollManager.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "ObjectFactory.h"

#include "Player.h"

#include "SimpleAudioEngine.h"
#include "PhysicsDefine.h"
#include "Behavior.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* Scene_Play::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Scene_Play::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool Scene_Play::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	m_bIsLeftButtonTouched = false;
	m_bIsRightButtonTouched = false;

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	CObjectManager::getInstance()->Init();

	settingTouchManager();
	settingKeyboardManager();

	b2Init();
	UIInit();
	BackgroundInit();
	m_pPlayer = CreatePlayer();
	ObjectInit();
	scheduleUpdate();

	m_bIsEnd = false;
    
    return true;
}

void Scene_Play::b2Init()
{
	b2Vec2 gravity;
	gravity.Set(0.0f, -15.0f);
	m_world = new b2World(gravity);
	m_world->SetAllowSleeping(true);
	m_world->SetContinuousPhysics(true);

	this->schedule(schedule_selector(Scene_Play::b2tick));
}

void Scene_Play::UIInit()
{
	m_pLeftButtonOn = CreateTexture("ui/left_on.png");
	m_pLeftButtonOff = CreateTexture("ui/left_off.png");
	m_pRightButtonOn = CreateTexture("ui/right_on.png");
	m_pRightButtonOff = CreateTexture("ui/right_off.png");
	m_pJumpButtonOn = CreateTexture("ui/jump_on.png");
	m_pJumpButtonOff = CreateTexture("ui/jump_off.png");

	m_pLeftMoveButton = CCSprite::createWithTexture(m_pLeftButtonOff);
	m_pLeftMoveButton->setPosition(Vec2(100, 80));
	this->addChild(m_pLeftMoveButton, UI1_ZORDER);

	m_pRightMoveButton = CCSprite::createWithTexture(m_pRightButtonOff);
	m_pRightMoveButton->setPosition(Vec2(185, 80));
	this->addChild(m_pRightMoveButton, UI1_ZORDER);

	m_pJumpButton = CCSprite::createWithTexture(m_pJumpButtonOff);
	m_pJumpButton->setPosition(Vec2(1100, 80));
	this->addChild(m_pJumpButton, UI1_ZORDER);

	m_pFilmSprite = CCSprite::create("ui/film.png");
	m_pFilmSprite->setPosition(ccp(200, 600));
	this->addChild(m_pFilmSprite, UI1_ZORDER);
}

void Scene_Play::ObjectInit()
{
	auto factory = CObjectFactory::getInstance();
	auto mgr = CDataManager::getInstance();
	auto profile = m_pPlayer->getActorProfile();

	for (auto itr = mgr->getBoxData()->begin(); itr != mgr->getBoxData()->end(); itr++)
	{
		auto box = factory->CreateBox(this, m_world, profile, *itr);
		m_arrObject.push_back(box);
	}

	for (auto itr = mgr->getRailData()->begin(); itr != mgr->getRailData()->end(); itr++)
	{
		auto rail = factory->CreateRail(this, m_world, profile, *itr);
		m_arrObject.push_back(rail);
		m_arrRail.push_back(rail);
	}

	for (auto itr = mgr->getPulleyData()->begin(); itr != mgr->getPulleyData()->end(); itr++)
	{
		auto pulley = factory->CreatePulley(this, m_world, profile, *itr);
		m_arrObject.push_back(pulley);
	}

	for (auto itr = mgr->getMirageData()->begin(); itr != mgr->getMirageData()->end(); itr++)
	{
		auto mirage = factory->CreateMirage(this, m_world, profile, *itr);
		m_arrObject.push_back(mirage);
	}

	for (auto itr = mgr->getGroundData()->begin(); itr != mgr->getGroundData()->end(); itr++)
	{
		factory->CreateGround(this, m_world, *itr);
	}

	auto pTempSprite = CCSprite::create(mgr->getDestinationData()->m_szTextureName);
	pTempSprite->setPosition(mgr->getDestinationData()->m_vPosition);
	pTempSprite->setAnchorPoint(ccp(0.5, 0));
	this->addChild(pTempSprite);

	m_pDestination = shared_ptr<CScrollSprite>(new CScrollSprite);
	m_pDestination->Init(pTempSprite);
	CScrollManager::getInstance()->Insert(m_pDestination);

	m_pZeroWall = CreateWall("object/20.png", ccp(0, 100));
	m_pMaxWall =  CreateWall("object/20.png", ccp(2560, 100));
}

void Scene_Play::BackgroundInit()
{
	auto background = CCSprite::create(CDataManager::getInstance()->getBackgroundTextureName());
	background->setAnchorPoint(ccp(0, 0));
	this->addChild(background, 0);

	m_pBackground = shared_ptr<CScrollSprite>(new CScrollSprite());
	m_pBackground->Init(background);

	CScrollManager::getInstance()->Insert(m_pBackground);
}

void Scene_Play::settingTouchManager()
{
	EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
	auto* touchListener = EventListenerTouchAllAtOnce::create();

	touchListener->onTouchesBegan = CC_CALLBACK_2(Scene_Play::onTouchesBegan, this);
	touchListener->onTouchesMoved = CC_CALLBACK_2(Scene_Play::onTouchesMoved, this);
	touchListener->onTouchesEnded = CC_CALLBACK_2(Scene_Play::onTouchesEnded, this);
	touchListener->onTouchesCancelled = CC_CALLBACK_2(Scene_Play::onTouchesCancelled, this);

	dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void Scene_Play::settingKeyboardManager()
{
	auto* keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Scene_Play::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Scene_Play::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void Scene_Play::onTouchesBegan(const vector<Touch*>&touches, Event* event)
{
	for (auto itr = touches.begin(); itr != touches.end(); itr++)
	{
		CCPoint touchPos = (*itr)->getLocation();

		if (m_pLeftMoveButton->boundingBox().containsPoint(touchPos))
		{
			m_pLeftMoveButton->setTexture(m_pLeftButtonOn);
			m_bIsLeftButtonTouched = true;
			m_pPlayer->PlayMoveSound();
		}

		if (m_pRightMoveButton->boundingBox().containsPoint(touchPos))
		{
			m_pRightMoveButton->setTexture(m_pRightButtonOn);
			m_bIsRightButtonTouched = true;
			m_pPlayer->PlayMoveSound();
		}

		if (m_pJumpButton->boundingBox().containsPoint(touchPos))
		{
			m_pPlayer->Jump();
			m_pJumpButton->setTexture(m_pJumpButtonOn);
			m_bIsJumpButtonTouched = true;
		}

		for (int i = 0; i < m_arrObject.size(); i++)
		{
			if (m_pPlayer->Action(this, m_arrObject[i]->getBehaviorPtr(), touchPos))
				break;
		}
	}
}

void Scene_Play::onTouchesMoved(const vector<Touch*>&touches, Event* event)
{
	for (auto itr = touches.begin(); itr != touches.end(); itr++)
	{
		CCPoint touchPos = (*itr)->getLocation();

		if (m_pLeftMoveButton->boundingBox().containsPoint(touchPos))
		{
			m_pLeftMoveButton->setTexture(m_pLeftButtonOn);
			m_bIsLeftButtonTouched = true;
			m_pPlayer->PlayMoveSound();
		}
		else
		{
			m_pLeftMoveButton->setTexture(m_pLeftButtonOff);
			m_pPlayer->Stop();
			m_bIsLeftButtonTouched = false;
		}

		if (m_pRightMoveButton->boundingBox().containsPoint(touchPos))
		{
			m_pRightMoveButton->setTexture(m_pRightButtonOn);
			m_bIsRightButtonTouched = true;
			m_pPlayer->PlayMoveSound();
		}
		else
		{
			m_pRightMoveButton->setTexture(m_pRightButtonOff);
			m_pPlayer->Stop();
			m_bIsRightButtonTouched = false;
		}

		if (m_pJumpButton->boundingBox().containsPoint(touchPos))
		{
			m_pPlayer->Jump();
			m_pJumpButton->setTexture(m_pJumpButtonOn);
			m_bIsJumpButtonTouched = true;
		}
		else
		{
			m_bIsJumpButtonTouched = false;
			m_pJumpButton->setTexture(m_pJumpButtonOff);
		}
	}
}

void Scene_Play::onTouchesEnded(const vector<Touch*>&touches, Event* event)
{
	for (auto itr = touches.begin(); itr != touches.end(); itr++)
	{
		CCPoint touchPos = (*itr)->getLocation();

		if (m_pLeftMoveButton->boundingBox().containsPoint(touchPos))
		{
			m_pLeftMoveButton->setTexture(m_pLeftButtonOff);
			m_pPlayer->Stop();
			m_bIsLeftButtonTouched = false;
		}

		if (m_pRightMoveButton->boundingBox().containsPoint(touchPos))
		{
			m_pRightMoveButton->setTexture(m_pRightButtonOff);
			m_pPlayer->Stop();
			m_bIsRightButtonTouched = false;
		}

		if (m_pJumpButton->boundingBox().containsPoint(touchPos))
		{
			m_bIsJumpButtonTouched = false;
			m_pJumpButton->setTexture(m_pJumpButtonOff);
		}
	}
}

void Scene_Play::onTouchesCancelled(const vector<Touch*>&touches, Event* event)
{

}

void Scene_Play::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW :
		m_bIsLeftButtonTouched = true;
		m_pPlayer->Move(md_Left);
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW :
		m_bIsRightButtonTouched = true;
		m_pPlayer->Move(md_Right);
		break;
		
	case EventKeyboard::KeyCode::KEY_SPACE :
		m_pPlayer->Jump();
		break;

	case EventKeyboard::KeyCode::KEY_F12 :
		GoNextStage();
		break;
	}
}

void Scene_Play::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
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
	}
}

void Scene_Play::update(float dt)
{
	if (m_pDestination->getSpritePtr()->getBoundingBox().containsPoint(m_pPlayer->getPosition()) && !m_bIsEnd)
	{
		GoNextStage();
	}

	if (m_bIsLeftButtonTouched)
		m_pPlayer->Move(MoveDirection::md_Left);
	
	if (m_bIsRightButtonTouched)
		m_pPlayer->Move(MoveDirection::md_Right);

	for (auto itr = m_arrRail.begin(); itr != m_arrRail.end(); itr++)
	{
		CCRect r;
		r.setRect(itr->get()->getSpritePtr()->getBoundingBox().getMinX(), itr->get()->getSpritePtr()->getBoundingBox().getMaxY(),
			itr->get()->getSpritePtr()->getContentSize().width, itr->get()->getSpritePtr()->getContentSize().height + 3);

		if (m_pPlayer->getBodySpritePtr()->getBoundingBox().intersectsRect(r))
		{
			m_pPlayer->RunRail(itr->get()->getDirection());
		}
	}

	Scrolling();
	UpdateManager::getInstance()->Updating();
}

void Scene_Play::b2tick(float dt)
{
	int32 velocityIterator = 8;
	int32 positionIterator = 3;

	m_world->Step(dt, velocityIterator, positionIterator);

	for (b2Body *b = m_world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != NULL)
		{
			CCSprite *spriteData = (CCSprite *)b->GetUserData();
			spriteData->setPosition(ccp(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
			spriteData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}
}

void Scene_Play::Scrolling()
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
	CScrollManager::getInstance()->Scroll(sv);
}

CCTexture2D* Scene_Play::CreateTexture(string filename)
{
	auto image = new CCImage;
	image->initWithImageFile(filename);

	auto texture = new CCTexture2D;
	texture->initWithImage(image);

	return texture;
}

shared_ptr<CPlayer> Scene_Play::CreatePlayer()
{
	auto temp = shared_ptr<CPlayer>(new CPlayer);
	temp->Init(this, m_world, CCSprite::create("char/box_stand.png"));
	temp->setPositionTo(ccp(50, 300));
	CScrollManager::getInstance()->Insert(temp);
	UpdateManager::getInstance()->Insert(temp);

	return temp;
}

CBox2dSprite* Scene_Play::CreateWall(string filename, CCPoint pos)
{
	auto pWall1 = CCSprite::create(filename);
	pWall1->setPosition(pos);
	this->addChild(pWall1);

	auto wall = new CBox2dSprite;
	wall->Init(pWall1, m_world, b2BodyType::b2_staticBody, ccp(0.5, 0));

	return wall;
}

void Scene_Play::GoNextStage()
{
	m_bIsEnd = true;
	this->unschedule(schedule_selector(Scene_Play::update));
	CScrollManager::getInstance()->Release();
	UpdateManager::getInstance()->Release();
	CSceneManager::getInstance()->ChangeScene(ESceneType::e_SceneLoadMap);
	m_arrObject.clear();
	m_arrRail.clear();
}