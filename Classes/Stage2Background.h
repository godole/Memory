#pragma once
#include "PlayLayerEntity.h"

class Stage2Background :
	public PlayLayerEntity
{
public:
	CREATE_FUNC(Stage2Background);
	void LayerInit() override;
};

