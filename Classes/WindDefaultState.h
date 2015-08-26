#pragma once
#include "WindBehaviorState.h"

class CWindDefaultState :
	public CWindBehaviorState
{
public :
	virtual bool Action(CCPoint a_vPosition);
	virtual void Update();
	virtual void BehaviorInit();

public:
	CWindDefaultState();
	~CWindDefaultState();
};

