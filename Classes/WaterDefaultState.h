#pragma once
#include "WaterBehaviorState.h"
class CWaterDefaultState :
	public CWaterBehaviorState
{
public :
	virtual bool Action(Vec2 a_TouchPos);
	virtual void Update(){}

public:
	CWaterDefaultState();
	~CWaterDefaultState();

private :
	virtual void BehaviorInit() override;
};

