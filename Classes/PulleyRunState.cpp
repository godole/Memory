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
		for (int i = 0; i < m_pPulley->m_parrPulleySprite.size(); i++)
		{
			m_pPulley->m_parrPulleySprite[i]->getBodyStructure().body->SetLinearVelocity(ChangeVecTob2Vec2(Vec2::ZERO));
		}
	}
	else
		m_pPulley->m_fCurrentLength -= m_pPulley->m_fMoveSpeed / PTM_RATIO;
}

void CPulleyRunState::BehaviorInit()
{
	m_pPulley->m_drCurrentDirection = m_pPulley->m_drStartDirection;
	m_pPulley->m_pLeverSprite->setTexture(m_pPulley->m_pLeverOnTexture);

	for (int i = 0; i < m_pPulley->m_parrPulleySprite.size(); i++)
	{
		auto pulleySprite = m_pPulley->m_parrPulleySprite[i];
		auto body = pulleySprite->getBodyStructure().body;
		pulleySprite->getSpritePtr()->setTexture(m_pPulley->m_pPulleyOnTexture);
		body->SetType(b2BodyType::b2_dynamicBody);
		body->SetGravityScale(0);

		b2MassData massdata;
		massdata.mass = 100000;
		massdata.center = body->GetWorldCenter();
		body->SetMassData(&massdata);

		if (m_pPulley->m_drCurrentDirection == EDirection::e_drUp)
		{
			body->SetLinearVelocity(ChangeVecTob2Vec2(Vec2(0, m_pPulley->m_fMoveSpeed)));
		}

		else if (m_pPulley->m_drCurrentDirection == EDirection::e_drDown)
		{
			body->SetLinearVelocity(ChangeVecTob2Vec2(Vec2(0, -m_pPulley->m_fMoveSpeed)));
		}
	}
}