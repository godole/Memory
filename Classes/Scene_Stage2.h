#pragma once
#include "PlayLayerMainLogic.h"

class CRail;

class Scene_Stage2 :
	public PlayLayerMainLogic
{
public:
	// implement the "static create()" method manually
	CREATE_FUNC(Scene_Stage2);

public:
	virtual void BackgroundInit();
	virtual void ObjectInit();
	virtual void BackgroundUpdate();
	virtual void ObjectUpdate();

public:
	Scene_Stage2();
	~Scene_Stage2();

private :
	vector<shared_ptr<CRail>>	 m_arrRail;
	shared_ptr<CScrollSprite> m_pBackgroundBuild;
};

