#include "RailRunState.h"
#include "Rail.h"

bool CRailRunState::Action(CCPoint a_Pos)
{
	return false;
}

void CRailRunState::BehaviorInit()
{
	if (m_pRail->m_eCurrentDirection == EDirection::e_drLeft)
	{
		m_pRail->m_eCurrentDirection = EDirection::e_drRight;
		m_pRail->m_pRailSprite->setTexture(m_pRail->m_pRailRightTexture);
	}

	else if (m_pRail->m_eCurrentDirection == EDirection::e_drRight)
	{
		m_pRail->m_eCurrentDirection = EDirection::e_drLeft;
		m_pRail->m_pRailSprite->setTexture(m_pRail->m_pRailLeftTexture);
	}

	m_pRail->m_pLeverSprite->setTexture(m_pRail->m_pLeverOnTexture);
}