#pragma once
#include "WindBehaviorState.h"

class CWindRunState :
	public CWindBehaviorState
{
public:
	virtual bool Action(CCPoint a_vPosition);
	virtual void Update();
	virtual void BehaviorInit();

public:
	CWindRunState();
	~CWindRunState();
};

