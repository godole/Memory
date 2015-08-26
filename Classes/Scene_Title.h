#pragma once
#include "cocos2d.h"

class Scene_Title :
	public cocos2d::CCLayer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	//TouchCallback
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);

	CREATE_FUNC(Scene_Title);

private :

};

