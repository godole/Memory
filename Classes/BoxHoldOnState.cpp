#include "BoxHoldOnState.h"
#include "BoxAfterState.h"
#include "ObjectManager.h"
#include "Box2dSprite.h"
#include "UpdateManager.h"
#include "ScrollManager.h"
#include <memory>

bool CBoxHoldOnState::Action(Vec2 a_TouchPos)
{
	auto arr = CObjectManager::getInstance()->getBox2dSprite();
	CCPoint setPos;
	bool bIsEnable = true;
	CCRect rect;

	for (int i = 0; i <= 20; i++)
	{
		for (int j = 0; j <= 20; j++)
		{
			CCRect r;
			r.setRect(i * 105 + CScrollManager::getInstance()->getDeltaPosition().x, j * 105 + CScrollManager::getInstance()->getDeltaPosition().y, 105, 105);

			if (r.containsPoint(a_TouchPos))
			{
				setPos = ccp(r.getMidX(), r.getMidY());
				rect = r;
			}
		}
	}

	for (int i = 0; i < arr->getSize(); i++)
	{
		if (arr->getObjectAt(i)->getSpritePtr() == m_pBox->m_pBoxSprite)
			continue;

		auto boxsprite = m_pBox->m_pBoxSprite;
		auto anothersprite = arr->getObjectAt(i)->getSpritePtr();

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
		m_pBox->setBodyPositionTo(setPos);
		m_pBox->ChangeState(shared_ptr<CBoxBehaviorState>(new CBoxAfterState));
	}

	auto parent = Director::sharedDirector()->getRunningScene()->getChildByTag(2);

	return false;
}

void CBoxHoldOnState::Update()
{
	m_pBox->setBodyPositionTo(*m_pBox->m_pTransProfile->m_vpHoldingPosition);
}

void CBoxHoldOnState::BehaviorInit()
{
	m_pBox->m_pBody->SetActive(false);
	m_pBox->m_pBoxSprite->setZOrder(3);
}