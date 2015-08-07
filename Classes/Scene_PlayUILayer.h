#pragma once
#include "cocos2d.h"
#include "PlayLayerShareData.h"
#include "Scene_PlayLayer.h"

USING_NS_CC;

class Scene_PlayUILayer :
	public Scene_PlayLayer
{
public:
	CREATE_FUNC(Scene_PlayUILayer);

	//TouchCallback
	virtual void onTouchesBegan(const vector<Touch*>&touches, Event* event);
	virtual void onTouchesMoved(const vector<Touch*>&touches, Event* event);
	virtual void onTouchesEnded(const vector<Touch*>&touches, Event* event);
	virtual void onTouchesCancelled(const vector<Touch*>&touches, Event* event);

private :
	void LayerInit() override;
	void settingTouchDispatcher();

	Size visibleSize;
	Vec2 origin;

	CCSprite* m_pLeftMoveButton;
	CCTexture2D* m_pLeftButtonOn;
	CCTexture2D* m_pLeftButtonOff;

	CCSprite* m_pRightMoveButton;
	CCTexture2D* m_pRightButtonOn;
	CCTexture2D* m_pRightButtonOff;

	CCSprite* m_pJumpButton;
	CCTexture2D* m_pJumpButtonOn;
	CCTexture2D* m_pJumpButtonOff;

	CCSprite* m_pFilmSprite;
};

