#include "MirageCrashedState.h"


bool CMirageCrashedState::Action(CCPoint a_Pos)
{
	return false;
}

void CMirageCrashedState::BehaviorInit()
{
	m_pMirage->m_pGlassSprite->setTexture(m_pMirage->m_pGlassCrashedTexture);
	m_pMirage->m_pWallSprite->setVisible(false);
	m_pMirage->m_pBody->SetActive(false);
}