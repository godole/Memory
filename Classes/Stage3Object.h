#pragma once
#include "PlayLayerEntity.h"

class CBox;
class CMirage;
class CWater;
class CSand;

class Stage3Object :
	public PlayLayerEntity
{
public:
	void LayerInit();

	CREATE_FUNC(Stage3Object);
};

