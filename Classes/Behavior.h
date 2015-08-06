#pragma once
#include "cocos2d.h"
#include <string>

USING_NS_CC;
using namespace std;

class Behavior
{
public :
	virtual void setStateToDefault() = 0;
	virtual bool Action(CCPoint a_TouchPos) = 0;
	virtual string getIconFileName() = 0;
	virtual void BehaviorInit() = 0;

	static bool k_bIsDoing;
};
