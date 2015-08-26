#include "Scene_InGame.h"
#include "PlayLayerMainLogic.h"
#include "PlayLayerEntity.h"
#include "LayerDefine.h"

USING_NS_CC;

Scene* Scene_InGame::createScene(CCLayer* a_pMainLayer, CCLayer* a_pBackgroundLayer, CCLayer* a_pObjectLayer)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

	scene->addChild(a_pBackgroundLayer, 0, BG_LAYER);
	scene->addChild(a_pObjectLayer, 1, OBJ_LAYER);
    // add layer as a child to scene
	scene->addChild(a_pMainLayer, 2, MAIN_LAYER);

    // return the scene
    return scene;
}
