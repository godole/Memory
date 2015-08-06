#include "BoxAfterState.h"
#include "BoxDefaultState.h"

bool CBoxAfterState::Action(Vec2 a_TouchPos)
{
	return false;
}

void CBoxAfterState::Update()
{

}

void CBoxAfterState::BehaviorInit()
{
	m_pBox->m_pBody->SetActive(true);
}