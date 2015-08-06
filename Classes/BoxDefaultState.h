#pragma once
#include "BoxBehaviorState.h"

class CBoxDefaultState :
	public CBoxBehaviorState
{
public :
	virtual bool Action(Vec2 a_TouchPos);
	virtual void Update();

public :
	CBoxDefaultState(){}
	~CBoxDefaultState(){}

private :
	virtual void BehaviorInit() override;
};