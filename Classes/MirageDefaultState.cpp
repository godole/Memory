#include "MirageDefaultState.h"
#include "MirageCrashedState.h"

void CMirageDefaultState::BehaviorInit()
{
	m_pMirage->m_pGlassSprite->setTexture(m_pMirage->m_pGlassTexture);
	m_pMirage->m_pWallSprite->setVisible(true);
	m_pMirage->m_pBody->SetActive(true);
}

bool CMirageDefaultState::Action(CCPoint a_Pos)
{
	if (m_pMirage->m_pGlassSprite->getBoundingBox().containsPoint(a_Pos) &&
		!k_bIsDoing &&
		m_pMirage->m_bIsRanged)
	{
		m_pMirage->ChangeState(std::shared_ptr<CMirageBehaviorState>(new CMirageCrashedState));
		return true;
	}

	else
		return false;
}

