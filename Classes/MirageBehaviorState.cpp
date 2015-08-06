#include "MirageBehaviorState.h"
#include "MirageDefaultState.h"

void CMirageBehaviorState::Init(CMirage* a_pMirage)
{
	m_pMirage = a_pMirage;

	BehaviorInit();
}

void CMirageBehaviorState::setStateToDefault()
{
	m_pMirage->ChangeState(shared_ptr<CMirageDefaultState>(new CMirageDefaultState));
}