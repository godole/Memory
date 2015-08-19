#pragma once
#include "PlayLayerEntity.h"

class CScrollSprite;

class Stage2Background :
	public PlayLayerEntity
{
public:
	CREATE_FUNC(Stage2Background);
	void LayerInit() override;

private :
	shared_ptr<CScrollSprite> m_pBackgroundBuild;
	vector<shared_ptr<CScrollSprite>> m_arrCloud;
};

