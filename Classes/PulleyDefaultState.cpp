#include "PulleyDefaultState.h"
#include "PulleyRunState.h"
#include "EDirection.h"
#include "Pulley.h"

void CPulleyDefaultState::BehaviorInit()
{
	m_pPulley->m_drCurrentDirection = EDirection::e_drNULL;
	m_pPulley->m_fCurrentLength = m_pPulley->m_fStartLength;
	m_pPulley->m_pLeverSprite->setTexture(m_pPulley->m_pLeverOffTexture);
	m_pPulley->m_pPulleySprite->setTexture(m_pPulley->m_pPulleyOffTexture);

	m_pPulley->setBodyPositionTo(m_pPulley->m_vStartPosition);
	m_pPulley->m_pBody->SetType(b2BodyType::b2_staticBody);
}

bool CPulleyDefaultState::Action(CCPoint a_vPos)
{
	if (m_pPulley->m_pLeverSprite->getBoundingBox().containsPoint(a_vPos) &&
		!k_bIsDoing &&
		m_pPulley->m_bIsRanged)
	{
		m_pPulley->ChangeState(shared_ptr<CPulleyBehaviorState>(new CPulleyRunState));
		return true;
	}
	else
		return false;
}