#pragma once
#include "cocos2d.h"
#include "PlayLayerEntity.h"

USING_NS_CC;

class Stage2Object :
	public PlayLayerEntity
{
public:
	CREATE_FUNC(Stage2Object);
	void LayerInit();

	virtual void update(float dt) override;

	virtual ~Stage2Object()
	{

	}

private :
	vector<shared_ptr<CRail>>	 m_arrRail;
};

