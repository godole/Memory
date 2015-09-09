#include "WindBehaviorState.h"
#include "WindBox.h"

using namespace std;
using namespace cocos2d;


CWindBehaviorState::CWindBehaviorState()
{
}


CWindBehaviorState::~CWindBehaviorState()
{
}

void CWindBehaviorState::Init(CWindBox* a_pThings, map<string, void*>* a_pvalueMap)
{
	m_pThings = a_pThings;
	m_pValueMap = a_pvalueMap;

	CCSprite* sprite = (CCSprite*)a_pvalueMap->at("sprite");

	BehaviorInit();
}

void CWindBehaviorState::setStateToDefault()
{
	m_pThings->setStateToDefault();
}