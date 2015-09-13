#pragma once
#include "BoxBehaviorState.h"

class CBoxHoldOnState :
	public CBoxBehaviorState
{
public :
	virtual bool Action(Vec2 a_TouchPos);
	virtual void Update();

public:
	CBoxHoldOnState(){}
	~CBoxHoldOnState(){}

private :
	virtual void BehaviorInit() override;
};

