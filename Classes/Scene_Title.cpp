#include "Scene_Title.h"
#include "SceneManager.h"
#include <string>
#include "DataManager.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;


cocos2d::Scene* Scene_Title::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Scene_Title::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool Scene_Title::init()
{
	auto background = CCSprite::create("title/main.png");
	background->setAnchorPoint(ccp(0, 0));
	this->addChild(background, 0);

	EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
	auto* touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(Scene_Title::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(Scene_Title::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Scene_Title::onTouchEnded, this);

	dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	CDataManager::getInstance()->LoadPlayerData();

	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/title.mp3", true);

	return true;
}

bool Scene_Title::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	/*CDataManager::getInstance()->setCurrentStage(2, 3);
	CDataManager::getInstance()->LoadMapData(
		StringUtils::format("map/data/map%d-%d.txt", 2, 3));
	CSceneManager::getInstance()->ChangeScene(ESceneType::e_SceneStage2);*/
	CDataManager::getInstance()->LoadMapData("map/data/maptest.txt");
	CSceneManager::getInstance()->ChangeScene(ESceneType::e_SceneStageTest);
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	return true;
}

void Scene_Title::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{

}

void Scene_Title::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{

}
