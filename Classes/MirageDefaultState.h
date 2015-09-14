#pragma once
#include "cocos2d.h"
#include "MirageBehaviorState.h"

USING_NS_CC;

class CMirageDefaultState :
	public CMirageBehaviorState
{
public :
	bool Action(CCPoint a_Pos) override;

public:
	CMirageDefaultState(){}
	~CMirageDefaultState() {}

private :
	virtual void BehaviorInit() override;

};

