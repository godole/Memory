#include "WaterHoldingState.h"
#include "ObjectManager.h"
#include "WaterAfterState.h"


CWaterHoldingState::CWaterHoldingState()
{
}


CWaterHoldingState::~CWaterHoldingState()
{
}

bool CWaterHoldingState::Action(Vec2 a_TouchPos)
{
	auto sandarray = CObjectManager::getInstance()->getSandArray();
	for (int i = 0; i < sandarray->getSize(); i++)
	{
		if (sandarray->getObjectAt(i)->getSpritePtr()->getBoundingBox().containsPoint(a_TouchPos))
		{
			m_pWater->m_pSand = sandarray->getObjectAt(i);
			sandarray->getObjectAt(i)->On();
			k_bIsDoing = false;
			m_pWater->ChangeState(shared_ptr<CWaterBehaviorState>(new CWaterAfterState));
			break;
		}
	}
	return false;
}

void CWaterHoldingState::BehaviorInit()
{

}

void CWaterHoldingState::Update()
{
	m_pWater->m_pWaterSprite->setPosition(*m_pWater->m_pTransectorProfile->m_vpHoldingPosition);
}