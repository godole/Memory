#pragma once
#include "WaterBehaviorState.h"
class CWaterAfterState :
	public CWaterBehaviorState
{
public :
	virtual bool Action(Vec2 a_TouchPos);
	virtual void Update(){}

public:
	CWaterAfterState();
	~CWaterAfterState();

private :
	virtual void BehaviorInit() override;
};

