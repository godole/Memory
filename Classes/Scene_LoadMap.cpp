#include "Scene_LoadMap.h"
#include "DataManager.h"
#include "SceneManager.h"

Scene* Scene_LoadMap::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Scene_LoadMap::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool Scene_LoadMap::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	CDataManager::getInstance()->LoadNextMapData();

	schedule(CC_SCHEDULE_SELECTOR(Scene_LoadMap::change), 0.5);

	return true;
}

void Scene_LoadMap::change(float dt)
{
	unschedule(CC_SCHEDULE_SELECTOR(Scene_LoadMap::change));
	CSceneManager::getInstance()->ChangeScene(ESceneType::e_ScenePlay);
}