#pragma once
#include "BoxBehaviorState.h"

class CBoxAfterState :
	public CBoxBehaviorState
{
public :
	bool Action(Vec2 a_TouchPos);
	void Update();

public:
	CBoxAfterState(){}
	~CBoxAfterState(){}

private :
	void BehaviorInit() override;
};

