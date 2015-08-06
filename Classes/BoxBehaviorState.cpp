#include "BoxBehaviorState.h"
#include "BoxDefaultState.h"

void CBoxBehaviorState::Init(CBox* a_pBox)
{
	m_pBox = a_pBox;

	BehaviorInit();
}

void CBoxBehaviorState::setStateToDefault()
{
	m_pBox->ChangeState(shared_ptr<CBoxBehaviorState>(new CBoxDefaultState));
}