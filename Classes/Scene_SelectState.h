#pragma once
#include "cocos2d.h"
#include <memory>

using namespace std;

USING_NS_CC;

class CStageBox;
class Scene_SelectState :
	public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	//TouchCallback
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);

	//MainLoop
	virtual void update(float dt) override;

	CREATE_FUNC(Scene_SelectState);

public:
	Scene_SelectState();
	~Scene_SelectState();

private:
	void BackgroundInit();
	void settingTouchManager();

private:
	CStageBox* m_pStageBox;

	Sprite * m_pMenu1;
	Sprite * m_pMenu2;
};

