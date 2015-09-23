#include "SceneManager.h"
#include "Scene_InGame.h"
#include "Stage1Background.h"
#include "Stage1Object.h"
#include "Stage2Background.h"
#include "Stage2Object.h"
#include "Stage3Object.h"
#include "Stage3Background.h"
#include "PlayLayerMainLogic.h"
#include "SceneSelectScene.h"
#include "Scene_Title.h"


CSceneManager::CSceneManager()
{
}


CSceneManager::~CSceneManager()
{
}


void CSceneManager::ChangeScene(ESceneType e_type)
{
	SceneChange(e_type, 0.4f);
}

void CSceneManager::ChangeScene(ESceneType e_type, float fadetime)
{
	SceneChange(e_type, fadetime);
}

void CSceneManager::SceneChange(ESceneType e_type, float fadetime)
{
	CCScene* pScene;
	CCLayer* main;
	CCLayer* background;
	CCLayer* obj;

	switch (e_type)
	{
	case ESceneType::e_SceneStage1:
		main = PlayLayerMainLogic::create();
		background = Stage1Background::create();
		obj = Stage1Object::create();

		pScene = Scene_InGame::createScene(main, background, obj);
		break;
		
	case ESceneType::e_SceneStage2 :
		main = PlayLayerMainLogic::create();
		background = Stage2Background::create();
		obj = Stage2Object::create();

		pScene = Scene_InGame::createScene(main, background, obj);
		break;

	case ESceneType::e_SceneStage3 :
		main = PlayLayerMainLogic::create();
		background = Stage3Background::create();
		obj = Stage3Object::create();

		pScene = Scene_InGame::createScene(main, background, obj);
		break;

	case ESceneType::e_SceneTitle:
		pScene = Scene_Title::createScene();
		break;

	case ESceneType::e_SceneSelectStage :
		pScene = SceneSelectScene::createScene();
		break;
	}

	CCTransitionScene* pTran = CCTransitionFade::create(fadetime, pScene);
	CCDirector::getInstance()->replaceScene(pTran);
}