#pragma once
#include "cocos2d.h"
#include "PlayLayerMainLogic.h"

class Scene_Stage3 :
	public PlayLayerMainLogic
{
public:
	// implement the "static create()" method manually
	CREATE_FUNC(Scene_Stage3);

public:
	virtual void BackgroundInit();
	virtual void ObjectInit();
	virtual void BackgroundUpdate();
	virtual void ObjectUpdate();

public:
	Scene_Stage3();
	~Scene_Stage3();

private :
	
};

