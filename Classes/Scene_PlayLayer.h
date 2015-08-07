#pragma once
#include "cocos2d.h"
#include "PlayLayerShareData.h"

USING_NS_CC;

class Scene_PlayLayer : 
	public Layer
{
public:
	virtual bool init();

public :
	static PlayLayerShareData* m_pLayerData;

protected :
	virtual void LayerInit() = 0;

	Size visibleSize;
	Vec2 origin;
};

