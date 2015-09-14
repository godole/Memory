#include "WaterAfterState.h"
#include "Sand.h"


CWaterAfterState::CWaterAfterState()
{
}


CWaterAfterState::~CWaterAfterState()
{
}

bool CWaterAfterState::Action(Vec2 a_TouchPos)
{
	return false;
}

void CWaterAfterState::BehaviorInit()
{
	m_pWater->m_pWaterSprite->setPosition(m_pWater->m_pSprite->getPosition());
	m_pWater->m_pWaterSprite->setVisible(false);
}