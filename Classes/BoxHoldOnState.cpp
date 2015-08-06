#include "BoxHoldOnState.h"
#include "BoxAfterState.h"
#include "ObjectManager.h"
#include "Box2dSprite.h"
#include "UpdateManager.h"
#include <memory>

bool CBoxHoldOnState::Action(Vec2 a_TouchPos)
{
	auto arr = CObjectManager::getInstance()->getBox2dSprite();
	bool bIsEnable = true;

	for (int i = 0; i < arr->getSize(); i++)
	{
		if (arr->getObjectAt(i)->getSpritePtr() == m_pBox->m_pBoxSprite)
			continue;

		auto boxsprite = m_pBox->m_pBoxSprite;
		auto anothersprite = arr->getObjectAt(i)->getSpritePtr();

		CCRect rect = m_pBox->m_pBoxSprite->getBoundingBox();
		rect.setRect(a_TouchPos.x - (boxsprite->getAnchorPoint().x * boxsprite->getContentSize().width), a_TouchPos.y - (boxsprite->getAnchorPoint().y * boxsprite->getContentSize().height),
			boxsprite->getContentSize().width, boxsprite->getContentSize().height);

		if (rect.intersectsRect(anothersprite->getBoundingBox()))
			bIsEnable = false;
	}

	if (!m_pBox->m_pTransectorProfile->m_TransectRange.containsPoint(a_TouchPos))
	{
		bIsEnable = false;
	}

	if (bIsEnable)
	{
		k_bIsDoing = false;
		m_pBox->setBodyPositionTo(a_TouchPos);
		m_pBox->ChangeState(shared_ptr<CBoxBehaviorState>(new CBoxAfterState));
	}

	return false;
}

void CBoxHoldOnState::Update()
{
	m_pBox->setBodyPositionTo(*m_pBox->m_pTransProfile->m_vpHoldingPosition);
}

void CBoxHoldOnState::BehaviorInit()
{
	m_pBox->m_pBody->SetActive(false);
}