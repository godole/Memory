#include "PulleyBehaviorState.h"
#include "Pulley.h"

void CPulleyBehaviorState::Init(CPulley* a_pPulley)
{
	m_pPulley = a_pPulley;

	BehaviorInit();
}

void CPulleyBehaviorState::setStateToDefault()
{
	m_pPulley->setStateToDefault();
}

string CPulleyBehaviorState::getIconFileName()
{
	return string("ui/motion_ele.png");
}
