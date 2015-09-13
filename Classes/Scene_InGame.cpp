#include "Scene_InGame.h"
#include "Scene_Stage1.h"
#include "Scene_Stage2.h"
#include "Scene_Stage3.h"
#include "Scene_ObjTest.h"
#include "LayerDefine.h"

USING_NS_CC;

Scene* Scene_InGame::createScene(ESceneType type)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

	switch (type)
	{
	case ESceneType::e_SceneStage1:
		scene->addChild(Scene_Stage1::create(), 0, MAIN_LAYER);
		break;
	case ESceneType::e_SceneStage2:
		scene->addChild(Scene_Stage2::create(), 0, MAIN_LAYER);
		break;
	case ESceneType::e_SceneStage3:
		scene->addChild(Scene_Stage3::create(), 0, MAIN_LAYER);
		break;
	case ESceneType::e_SceneStageTest :
		scene->addChild(Scene_ObjTest::create(), 0, MAIN_LAYER);
	default:
		break;
	}

    // return the scene
    return scene;
}
