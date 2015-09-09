#include "SceneManager.h"
#include "Scene_InGame.h"
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

	switch (e_type)
	{
	case ESceneType::e_SceneStage1 :
	case ESceneType::e_SceneStage2 :
	case ESceneType::e_SceneStage3 :
		pScene = Scene_InGame::createScene(e_type);
		break;

	case ESceneType::e_SceneTitle :
		pScene = Scene_Title::createScene();
		break;

	case ESceneType::e_SceneSelectStage :
		pScene = SceneSelectScene::createScene();
		break;
	}

	CCTransitionScene* pTran = CCTransitionFade::create(fadetime, pScene);
	CCDirector::getInstance()->replaceScene(pTran);
}