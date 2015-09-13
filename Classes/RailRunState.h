#pragma once
#include "RailBehaviorState.h"

class CRailRunState :
	public CRailBehaviorState
{
public :
	virtual bool Action(CCPoint a_Pos) override;

public:
	CRailRunState(){}
	~CRailRunState(){}

private :
	void BehaviorInit();
};

