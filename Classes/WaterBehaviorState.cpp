#include "WaterBehaviorState.h"


CWaterBehaviorState::CWaterBehaviorState()
{
}


CWaterBehaviorState::~CWaterBehaviorState()
{
}

void CWaterBehaviorState::Init(CWater* a_pWater)
{
	this->m_pWater = a_pWater;

	BehaviorInit();
}

void CWaterBehaviorState::setStateToDefault()
{

}