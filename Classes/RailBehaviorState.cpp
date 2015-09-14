#include "RailBehaviorState.h"
#include "RailDefaultState.h"
#include "Rail.h"
#include <memory>

using namespace std;

void CRailBehaviorState::setStateToDefault()
{
	m_pRail->ChangeState(shared_ptr<CRailDefaultState>(new CRailDefaultState));
}

string CRailBehaviorState::getIconFileName()
{
	return string("ui/motion_rail.png");
}

void CRailBehaviorState::Init(CRail* a_ptr)
{
	m_pRail = a_ptr;

	BehaviorInit();
}