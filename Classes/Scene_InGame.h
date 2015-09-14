#pragma once
#include "SceneManager.h"
#include "cocos2d.h"

USING_NS_CC;

class Scene_InGame
{
public:
	static cocos2d::Scene* createScene(ESceneType type);
};