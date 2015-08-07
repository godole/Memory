#pragma once
#include <memory>
#include "cocos2d.h"
#include "PlayLayerShareData.h"
#include "Scene_PlayLayer.h"

USING_NS_CC;

class CThings;
class CRail;

class Scene_PlayObjLayer :
	public Scene_PlayLayer
{
public:
	CREATE_FUNC(Scene_PlayObjLayer);

	//TouchCallback
	virtual bool onTouchBegan(Touch* touches, Event* event) override;
	virtual void onTouchMoved(Touch* touches, Event* event) override;
	virtual void onTouchEnded(Touch* touches, Event* event) override;

	virtual void update(float dt) override;

	void LayerInit() override;

private :
	void settingTouchDispatcher();

	vector<shared_ptr<CThings>> m_arrObject;
	vector<shared_ptr<CRail>>	 m_arrRail;
};

