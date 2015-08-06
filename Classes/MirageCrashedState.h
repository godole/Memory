#pragma once
#include "cocos2d.h"
#include "MirageBehaviorState.h"

USING_NS_CC;	

class CMirageCrashedState :
	public CMirageBehaviorState
{
public :
	bool Action(CCPoint a_Pos);

public:
	CMirageCrashedState(){}
	~CMirageCrashedState(){}

private :
	virtual void BehaviorInit() override;
};

