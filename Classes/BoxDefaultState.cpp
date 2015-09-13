#include "BoxDefaultState.h"
#include "BoxHoldOnState.h"
#include "UpdateManager.h"
#include <memory>

bool CBoxDefaultState::Action(Vec2 a_TouchPos)
{
	if (!k_bIsDoing &&
		m_pBox->m_pBoxSprite->getBoundingBox().containsPoint(a_TouchPos) &&
		m_pBox->m_bIsRanged)
	{
		auto state = std::shared_ptr<CBoxBehaviorState>(new CBoxHoldOnState);
		m_pBox->ChangeState(state);
		k_bIsDoing = true;
		return true;
	}
	else
		return false;
}

void CBoxDefaultState::Update()
{

}

void CBoxDefaultState::BehaviorInit()
{
	m_pBox->m_pBody->SetActive(true);
	m_pBox->setBodyPositionTo(m_pBox->m_vStartPosition + CScrollManager::getInstance()->getDeltaPosition());
	m_pBox->m_pBoxSprite->setZOrder(0);
}