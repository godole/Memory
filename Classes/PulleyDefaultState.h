#pragma once
#include "cocos2d.h"
#include "PulleyBehaviorState.h"

USING_NS_CC;

class CPulleyDefaultState :
	public CPulleyBehaviorState
{
public :
	bool Action(CCPoint a_vPos) override;
	void Update(){}

public:
	CPulleyDefaultState(){}
	~CPulleyDefaultState(){}

private :
	void BehaviorInit() override;
};

