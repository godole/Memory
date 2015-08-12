#include "WaterDefaultState.h"
#include "WaterHoldingState.h"
#include "ScrollManager.h"


CWaterDefaultState::CWaterDefaultState()
{
}


CWaterDefaultState::~CWaterDefaultState()
{
}

bool CWaterDefaultState::Action(Vec2 a_TouchPos)
{
	if (!k_bIsDoing &&
		m_pWater->m_pSprite->getBoundingBox().containsPoint(a_TouchPos) &&
		m_pWater->m_bIsRanged)
	{
		k_bIsDoing = true;
		m_pWater->m_pWaterSprite->setVisible(true);
		m_pWater->m_pWaterSprite->setZOrder(2);
		auto state = std::shared_ptr<CWaterBehaviorState>(new CWaterHoldingState);
		m_pWater->ChangeState(state);
		return true;
	}
	else
		return false;
}

void CWaterDefaultState::BehaviorInit()
{
	m_pWater->m_pSprite->setPosition(m_pWater->m_vStartPosition + CScrollManager::getInstance()->getDeltaPosition());
}
