#pragma once
#include "BoxBehaviorState.h"
class CBoxReadyState :
	public CBoxBehaviorState
{
public :
	virtual bool Action(Vec2 a_TouchPos);
	virtual void Update();

public:
	CBoxReadyState();
	~CBoxReadyState();

private:
	virtual void BehaviorInit() override;
};

