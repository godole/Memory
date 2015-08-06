#include "PulleyRunState.h"
#include "Pulley.h"

bool CPulleyRunState::Action(CCPoint a_vPos)
{
	return false;
}

void CPulleyRunState::Update()
{
	if (m_pPulley->m_fCurrentLength < 0)
	{
		m_pPulley->m_pBody->SetLinearVelocity(ChangeVecTob2Vec2(Vec2::ZERO));
	}
	else
		m_pPulley->m_fCurrentLength -= m_pPulley->m_fMoveSpeed / PTM_RATIO;
}

void CPulleyRunState::BehaviorInit()
{
	m_pPulley->m_drCurrentDirection = m_pPulley->m_drStartDirection;
	m_pPulley->m_pLeverSprite->setTexture(m_pPulley->m_pLeverOnTexture);
	m_pPulley->m_pPulleySprite->setTexture(m_pPulley->m_pPulleyOnTexture);
	m_pPulley->m_pBody->SetType(b2BodyType::b2_dynamicBody);
	m_pPulley->m_pBody->SetGravityScale(0);

	b2MassData massdata;
	massdata.mass = 100000;
	massdata.center = m_pPulley->m_pBody->GetWorldCenter();
	m_pPulley->m_pBody->SetMassData(&massdata);

	if (m_pPulley->m_drCurrentDirection == EDirection::e_drUp)
	{
		m_pPulley->m_pBody->SetLinearVelocity(ChangeVecTob2Vec2(Vec2(0, m_pPulley->m_fMoveSpeed)));
	}

	else if (m_pPulley->m_drCurrentDirection == EDirection::e_drDown)
	{
		m_pPulley->m_pBody->SetLinearVelocity(ChangeVecTob2Vec2(Vec2(0, -m_pPulley->m_fMoveSpeed)));
	}
	
}