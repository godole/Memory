#pragma once
#include "cocos2d.h"
#include "BehaviorState.h"

USING_NS_CC;

class ITransector
{
public :
	virtual CCPoint* getHoldingPositionPtr() = 0;
	virtual CCPoint	getCurrentPosition() = 0;
};