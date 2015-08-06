#include "RailDefaultState.h"
#include "RailRunState.h"
#include "EDirection.h"
#include "Rail.h"
#include <memory>

using namespace std;

bool CRailDefaultState::Action(CCPoint a_Pos)
{
	if (m_pRail->m_pLeverSprite->getBoundingBox().containsPoint(a_Pos) &&
		!k_bIsDoing &&
		m_bIsRanged)
	{
		m_pRail->ChangeState(shared_ptr<CRailRunState>(new CRailRunState));
		return true;
	}
	else
		return false;
}

void CRailDefaultState::BehaviorInit()
{
	m_pRail->m_eCurrentDirection = m_pRail->m_eStartDirection;
	m_pRail->m_pLeverSprite->setTexture(m_pRail->m_pLeverOffTexture);

	if (m_pRail->m_eStartDirection == EDirection::e_drLeft)
		m_pRail->m_pRailSprite->setTexture(m_pRail->m_pRailLeftTexture);

	if (m_pRail->m_eStartDirection == EDirection::e_drRight)
		m_pRail->m_pRailSprite->setTexture(m_pRail->m_pRailRightTexture);
}
