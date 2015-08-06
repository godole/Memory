#include "SceneManager.h"
#include "Scene_Play.h"
#include "Scene_SelectState.h"
#include "Scene_LoadMap.h"


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
	case ESceneType::e_ScenePlay:
		pScene = Scene_Play::createScene();
		break;

	case ESceneType::e_SceneTitle:
		pScene = Scene_SelectState::createScene();
		break;

	case ESceneType::e_SceneLoadMap :
		pScene = Scene_LoadMap::createScene();
		break;
	}

	CCTransitionScene* pTran = CCTransitionFade::create(fadetime, pScene);
	CCDirector::getInstance()->replaceScene(pTran);
}