#pragma once
#include "cocos2d.h"
#include <string>
#include <map>

USING_NS_CC;
using namespace std;

class CThings;

class Behavior
{
public :
	virtual void setStateToDefault() = 0;
	virtual bool Action(CCPoint a_TouchPos) = 0;
	virtual string getIconFileName() = 0;
	virtual void BehaviorInit() = 0;
	virtual void Init(CThings* a_pObject, std::map<string, void* >* a_pValueMap) = 0;
	virtual void Update() = 0;

	static bool k_bIsDoing;
};

#define _VMAP_STATIC_CAST(x, y) static_cast<x>((*m_pValueMap)[y])