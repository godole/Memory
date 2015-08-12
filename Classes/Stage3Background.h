#pragma once
#include "cocos2d.h"
#include "PlayLayerEntity.h"

USING_NS_CC;

class Stage3Background :
	public PlayLayerEntity
{
public:
	void LayerInit();

	CREATE_FUNC(Stage3Background);
};

