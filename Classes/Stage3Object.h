#pragma once
#include "PlayLayerEntity.h"
#include <memory>
#include <vector>

class CWindBox;

class Stage3Object :
	public PlayLayerEntity
{
public:
	void LayerInit();

	CREATE_FUNC(Stage3Object);
private :
	void update(float dt);
	std::vector<std::shared_ptr<CWindBox>> m_arrWindBox;
};

