#include "SpannerHoldOnState.h"
#include "SpannerUsedState.h"
#include "TransectorProfile.h"
#include "ObjectManager.h"
#include "Spanner.h"


CSpannerHoldOnState::CSpannerHoldOnState()
{
}


CSpannerHoldOnState::~CSpannerHoldOnState()
{
}

bool CSpannerHoldOnState::Action(Vec2 a_TouchPos)
{
	auto spannerarr = CObjectManager::getInstance()->getDoorArray();

	for (int i = 0; i < spannerarr->getSize(); i++)
	{
		if (spannerarr->getObjectAt(i)->getSpritePtr()->getBoundingBox().containsPoint(a_TouchPos))
		{
			(*m_pValueMap)["door"] = spannerarr->getObjectAt(i).get();
			spannerarr->getObjectAt(i)->On();
			k_bIsDoing = false;
			m_pSprite->setVisible(false);
			m_pParent->ChangeState(shared_ptr<CSpannerBehaviorState>(new CSpannerUsedState));
			break;
		}
	}
	return false;
}

void CSpannerHoldOnState::Update()
{
	CCPoint holdPos = *static_cast<TransectorProfile*>((*m_pValueMap)["profile"])->m_vpHoldingPosition;
	m_pSprite->setPosition(holdPos);
}

void CSpannerHoldOnState::BehaviorInit()
{

}