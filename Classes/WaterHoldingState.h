#pragma once
#include "WaterBehaviorState.h"
class CWaterHoldingState :
	public CWaterBehaviorState
{
public :
	virtual bool Action(Vec2 a_TouchPos);
	virtual void Update();

public:
	CWaterHoldingState();
	~CWaterHoldingState();

private :
	virtual void BehaviorInit() override;
};

