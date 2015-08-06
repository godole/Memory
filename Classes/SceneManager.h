#pragma once
#include "cocos2d.h"
#include "Singleton.h"

USING_NS_CC;

enum class ESceneType
{
	e_SceneTitle,
	e_ScenePlay,
	e_SceneTest,
	e_SceneLoadMap
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

