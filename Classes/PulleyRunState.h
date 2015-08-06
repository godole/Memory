#pragma once
#include "PulleyBehaviorState.h"

class CPulleyRunState :
	public CPulleyBehaviorState
{
public :
	bool Action(CCPoint a_vPos);
	void Update();

public:
	CPulleyRunState(){}
	~CPulleyRunState(){}

private :
	void BehaviorInit();
};

