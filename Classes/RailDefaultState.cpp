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

	for (int i = 0; i < m_pRail->m_parrRailSprite.size(); i++)
	{
		auto sprite = m_pRail->m_parrRailSprite[i]->getSpritePtr();
		if (m_pRail->m_eStartDirection == EDirection::e_drLeft)
			sprite->setTexture(m_pRail->m_pRailLeftTexture);

		if (m_pRail->m_eStartDirection == EDirection::e_drRight)
			sprite->setTexture(m_pRail->m_pRailRightTexture);
	}
}
