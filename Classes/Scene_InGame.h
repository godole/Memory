#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Scene_InGame
{
public:
	static cocos2d::Scene* createScene(CCLayer* a_pMainLayer, CCLayer* a_pBackgroundLayer, CCLayer* a_pObjectLayer);
};