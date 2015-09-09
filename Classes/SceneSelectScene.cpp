#include "SceneSelectScene.h"
#include "UpdateManager.h"
#include "OptionLayer.h"
#include "StageBox.h"
#include "UserData.h"
#include "Option.h"

SceneSelectScene::SceneSelectScene(){}
SceneSelectScene::~SceneSelectScene(){
	UpdateManager::getInstance()->Release();
}

Scene* SceneSelectScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SceneSelectScene::create();
	scene->addChild(layer);
	return scene;
}

bool SceneSelectScene::init()
{
	settingTouchManager();

	m_pStageSelectLayer = Layer::create();
	m_pStageSelectLayer->setVisible(true);
	addChild(m_pStageSelectLayer);

	m_pOptionPageLayer = Layer::create();
	m_pOptionPageLayer->setVisible(false);
	addChild(m_pOptionPageLayer);

	BackgroundInit();

	scheduleUpdate();

	m_pOption = std::shared_ptr<COption>(new COption);
	m_pOption->init(this);

	m_pOptionLayer = std::shared_ptr<COptionLayer>(new COptionLayer);
	m_pOptionLayer->init(m_pOptionPageLayer,this);

	m_pStageBox = std::shared_ptr<CStageBox>(new CStageBox);
	m_pStageBox->init(m_pStageSelectLayer);
	UpdateManager::getInstance()->Insert(m_pStageBox);


	return true;
}

void SceneSelectScene::update(float dt)
{
	UpdateManager::getInstance()->Updating();

	BackgroundScroll();

	if (m_pOption->getLayerState() == ELayerState::Option)
	{
		m_pOptionPageLayer->setVisible(true); 
		m_pStageSelectLayer->setVisible(false);
	}
	else if (m_pOption->getLayerState() == ELayerState::SceneSelect)
	{
		m_pOptionPageLayer->setVisible(false);
		m_pStageSelectLayer->setVisible(true);
	}
}

void SceneSelectScene::BackgroundInit()
{
	// 이거 다른 클래스로 옮겨야할것같다 음음
	auto _pBackground = Sprite::create("stageselect/menu_ground.png");
	_pBackground->setAnchorPoint(Point(0, 0));
	m_pStageSelectLayer->addChild(_pBackground);

	m_pScrollBack[0] = Sprite::create("stageselect/menu_1.png");
	m_pScrollBack[0]->setAnchorPoint(Point(0, 0));
	m_pScrollBack[0]->setPosition(Point(0, 0));
	m_pStageSelectLayer->addChild(m_pScrollBack[0]);

	m_pScrollBack[1] = Sprite::create("stageselect/menu_1.png");
	m_pScrollBack[1]->setAnchorPoint(Point(0, 0));
	m_pScrollBack[1]->setPosition(Point(0, -1440));
	m_pStageSelectLayer->addChild(m_pScrollBack[1]);

	m_pScrollBack[2] = Sprite::create("stageselect/menu_2.png");
	m_pScrollBack[2]->setAnchorPoint(Point(0, 0));
	m_pScrollBack[2]->setPosition(Point(0, 0));
	m_pStageSelectLayer->addChild(m_pScrollBack[2]);

	m_pScrollBack[3] = Sprite::create("stageselect/menu_2.png");
	m_pScrollBack[3]->setAnchorPoint(Point(0, 0));
	m_pScrollBack[3]->setPosition(Point(0, -1440));
	m_pStageSelectLayer->addChild(m_pScrollBack[3]);
}
void SceneSelectScene::BackgroundScroll()
{
	for (int i = 0; i < 4; i++)
	{
		if (m_pScrollBack[i]->getPositionY() >= 720)
			m_pScrollBack[i]->setPositionY(-1440);

		if (i >1)
			m_pScrollBack[i]->setPositionY(
			m_pScrollBack[i]->getPositionY() + 2);
		else
			m_pScrollBack[i]->setPositionY(
			m_pScrollBack[i]->getPositionY() + 1);
	}
}

void SceneSelectScene::settingTouchManager()
{
	EventListenerTouchOneByOne * listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(SceneSelectScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(SceneSelectScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(SceneSelectScene::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
}

bool SceneSelectScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	auto _ptTouchpos = touch->getLocation();

	// Particle
	auto _touchparticle = ParticleSystemQuad::create("stageselect/particle_texture.plist");
	_touchparticle->setPosition(Point(_ptTouchpos.x, _ptTouchpos.y));
	this->addChild(_touchparticle);

	m_pOption->TouchBegan(_ptTouchpos);

	if (m_pOption->getLayerState() == ELayerState::SceneSelect)
		m_pStageBox->StageTouchBegan(_ptTouchpos);
	else if (m_pOption->getLayerState() == ELayerState::Option)
		m_pOptionLayer->TouchBegan(_ptTouchpos);

	return true;
}

void SceneSelectScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	m_pStageBox->StageTouchEnded(touch->getLocation());
}

void SceneSelectScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	if (m_pOption->getLayerState() == ELayerState::SceneSelect)
		m_pStageBox->StageTouchMoved(touch->getLocation());
	else if (m_pOption->getLayerState() == ELayerState::Option)
		m_pOptionLayer->TouchMoved(touch->getLocation());
}
