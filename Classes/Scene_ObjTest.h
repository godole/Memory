#pragma once
#include "cocos2d.h"
#include "PlayLayerMainLogic.h"

class CWindBox;
class CRail;

class Scene_ObjTest :
	public PlayLayerMainLogic
{
public:
	// implement the "static create()" method manually
	CREATE_FUNC(Scene_ObjTest);

public:
	virtual void BackgroundInit();
	virtual void ObjectInit();
	virtual void BackgroundUpdate();
	virtual void ObjectUpdate();

public:
	Scene_ObjTest();
	~Scene_ObjTest();

private:
	std::vector<std::shared_ptr<CWindBox>> m_arrWindBox;
	std::vector<std::shared_ptr<CRail>>	 m_arrRail;
};

