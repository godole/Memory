#pragma once
#include "RailBehaviorState.h"
class CRailDefaultState :
	public CRailBehaviorState
{
public :
	virtual bool Action(CCPoint a_Pos) override;

public:
	CRailDefaultState(){}
	~CRailDefaultState(){}

private :
	virtual void BehaviorInit() override;
};

