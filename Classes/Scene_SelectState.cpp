#include "Scene_SelectState.h"
#include "UpdateManager.h"
#include "DataManager.h"
#include "StageBox.h"

USING_NS_CC;

Scene* Scene_SelectState::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Scene_SelectState::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

Scene_SelectState::Scene_SelectState()
{
}

Scene_SelectState::~Scene_SelectState()
{
}

bool Scene_SelectState::init()
{
	settingTouchManager();

	BackgroundInit();

	scheduleUpdate();

	m_pStageBox = new CStageBox;
	m_pStageBox->init(this);

	return true;
}

void Scene_SelectState::update(float dt)
{
	UpdateManager::getInstance()->Updating();
}

void Scene_SelectState::BackgroundInit()
{
	auto _pBackground = Sprite::create("stageselect/menu_ground.png");
	_pBackground->setAnchorPoint(Point(0, 0));
	this->addChild(_pBackground);

	auto _RepeatAction_m1 = RepeatForever::create
		(Sequence::create(
		MoveBy::create(3.0f, Point(0, 100)),
		MoveBy::create(3.0f, Point(0, -100)), NULL));

	auto _RepeatAction_m2 = RepeatForever::create
		(Sequence::create(
		MoveBy::create(3.0f, Point(0, -100)),
		MoveBy::create(3.0f, Point(0, 100)),
		NULL));

	m_pMenu1 = Sprite::create("stageselect/menu_1.png");
	m_pMenu1->setAnchorPoint(Point(0, 0));
	m_pMenu1->setPositionY(-100);
	this->addChild(m_pMenu1, 0);

	m_pMenu2 = Sprite::create("stageselect/menu_2.png");
	m_pMenu2->setAnchorPoint(Point(0, 0));
	m_pMenu2->setPositionY(100);
	this->addChild(m_pMenu2, 0);

	m_pMenu1->runAction(_RepeatAction_m1);
	m_pMenu2->runAction(_RepeatAction_m2);
}

void Scene_SelectState::settingTouchManager()
{
	EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
	auto* touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(Scene_SelectState::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(Scene_SelectState::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Scene_SelectState::onTouchEnded, this);

	dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool Scene_SelectState::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	auto _pTouchpos = touch->getLocation();

	auto _touchparticle = ParticleSystemQuad::create("stageselect/particle_texture.plist");
	_touchparticle->setPosition(Point(_pTouchpos.x, _pTouchpos.y));
	this->addChild(_touchparticle);

	m_pStageBox->touch(_pTouchpos);

	return true;
}
void Scene_SelectState::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{

}
void Scene_SelectState::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{

}
