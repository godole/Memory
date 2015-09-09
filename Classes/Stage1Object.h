#pragma once
#include <memory>
#include "cocos2d.h"
#include "PlayLayerShareData.h"
#include "PlayLayerEntity.h"

USING_NS_CC;

class CThings;
class CRail;

class Stage1Object :
	public PlayLayerEntity
{
public:
	CREATE_FUNC(Stage1Object);

	void LayerInit() override;
};

