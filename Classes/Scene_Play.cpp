#include "Scene_Play.h"

//Define
#include "LayerDefine.h"
#include "EDirection.h"

//Objects
#include "ScrollSprite.h"

//interface
#include "IScroll.h"

//Manager
#include "UpdateManager.h"
#include "SceneManager.h"
#include "ObjectManager.h"

#include "Player.h"

#include "SimpleAudioEngine.h"

//Layer
#include "Scene_PlayBGLayer.h"
#include "Scene_PlayObjLayer.h"
#include "Scene_PlayUILayer.h"
#include "Scene_PlayLayer.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* Scene_Play::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

	auto layer = Scene_Play::create();
	auto data = layer->getLayerDataPtr();
	Scene_PlayLayer::m_pLayerData = data;
	
	auto background = Scene_PlayBGLayer::create();
	auto objlayer = Scene_PlayObjLayer::create();
	auto ui = Scene_PlayUILayer::create();

	scene->addChild(background, 0);
	scene->addChild(objlayer, 1);
	scene->addChild(ui, 2);
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

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	CObjectManager::getInstance()->Init();
	settingKeyboardManager();

	b2Init();
	m_LayerData.m_pPlayer = CreatePlayer();
	scheduleUpdate();

	m_LayerData.m_bIsJumpButtonTouched = false;
	m_LayerData.m_bIsLeftButtonTouched = false;
	m_LayerData.m_bIsRightButtonTouched = false;

	m_bIsEnd = false;
    
    return true;
}

void Scene_Play::b2Init()
{
	b2Vec2 gravity;
	gravity.Set(0.0f, -15.0f);
	m_LayerData.m_pWorld = new b2World(gravity);
	m_LayerData.m_pWorld->SetAllowSleeping(true);
	m_LayerData.m_pWorld->SetContinuousPhysics(true);

	this->schedule(schedule_selector(Scene_Play::b2tick));
}

void Scene_Play::settingKeyboardManager()
{
	auto* keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Scene_Play::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Scene_Play::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void Scene_Play::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW :
		m_LayerData.m_bIsLeftButtonTouched = true;
		m_LayerData.m_pPlayer->Move(md_Left);
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW :
		m_LayerData.m_bIsRightButtonTouched = true;
		m_LayerData.m_pPlayer->Move(md_Right);
		break;
		
	case EventKeyboard::KeyCode::KEY_SPACE :
		m_LayerData.m_pPlayer->Jump();
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
		m_LayerData.m_bIsLeftButtonTouched = false;
		m_LayerData.m_pPlayer->Stop();
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		m_LayerData.m_bIsRightButtonTouched = false;
		m_LayerData.m_pPlayer->Stop();
		break;
	}
}

void Scene_Play::update(float dt)
{
	if (m_LayerData.m_pDestination->getSpritePtr()->getBoundingBox().containsPoint(m_LayerData.m_pPlayer->getPosition()) && !m_bIsEnd)
	{
		GoNextStage();
	}

	if (m_LayerData.m_bIsLeftButtonTouched)
		m_LayerData.m_pPlayer->Move(MoveDirection::md_Left);

	if (m_LayerData.m_bIsRightButtonTouched)
		m_LayerData.m_pPlayer->Move(MoveDirection::md_Right);

	UpdateManager::getInstance()->Updating();
}

void Scene_Play::b2tick(float dt)
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

shared_ptr<CPlayer> Scene_Play::CreatePlayer()
{
	auto temp = shared_ptr<CPlayer>(new CPlayer);
	temp->Init(this, m_LayerData.m_pWorld, CCSprite::create("char/box_stand.png"));
	temp->setPositionTo(ccp(50, 300));
	CScrollManager::getInstance()->Insert(temp);
	UpdateManager::getInstance()->Insert(temp);

	return temp;
}

void Scene_Play::GoNextStage()
{
	m_bIsEnd = true;
	this->unschedule(schedule_selector(Scene_Play::update));
	CScrollManager::getInstance()->Release();
	UpdateManager::getInstance()->Release();
	CSceneManager::getInstance()->ChangeScene(ESceneType::e_SceneLoadMap);
}