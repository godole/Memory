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
		for (int i = 0; i < m_pRail->m_parrRailSprite.size(); i++)
		{
			auto sprite = m_pRail->m_parrRailSprite[i]->getSpritePtr();
			sprite->setTexture(m_pRail->m_pRailRightTexture);
		}
	}

	else if (m_pRail->m_eCurrentDirection == EDirection::e_drRight)
	{
		m_pRail->m_eCurrentDirection = EDirection::e_drLeft;
		for (int i = 0; i < m_pRail->m_parrRailSprite.size(); i++)
		{
			auto sprite = m_pRail->m_parrRailSprite[i]->getSpritePtr();
			sprite->setTexture(m_pRail->m_pRailLeftTexture);
		}
	}

	m_pRail->m_pLeverSprite->setTexture(m_pRail->m_pLeverOnTexture);
}