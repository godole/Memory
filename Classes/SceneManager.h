#pragma once
#include "cocos2d.h"
#include "Singleton.h"

USING_NS_CC;

enum class ESceneType
{
	e_SceneTitle,
	e_SceneStage1,
	e_SceneStage2,
	e_SceneStage3,
	e_SceneStageTest,
	e_SceneSelectStage
};

class CSceneManager :
	public Singleton<CSceneManager>
{
public :
	void	ChangeScene(ESceneType e_type);
	void	ChangeScene(ESceneType e_type, float fadetime);

public:
	void SceneChange(ESceneType e_type, float fadetime);

	CSceneManager();
	~CSceneManager();
};

