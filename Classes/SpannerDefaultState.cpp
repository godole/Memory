#include "SpannerDefaultState.h"
#include "SpannerHoldOnState.h"
#include "ScrollManager.h"
#include "Spanner.h"


CSpannerDefaultState::CSpannerDefaultState()
{
}


CSpannerDefaultState::~CSpannerDefaultState()
{
}


bool CSpannerDefaultState::Action(Vec2 a_TouchPos)
{
	if (!k_bIsDoing &&
		m_pSprite->getBoundingBox().containsPoint(a_TouchPos) &&
		m_pParent->getIsRanged())
	{
		k_bIsDoing = true;
		m_pParent->ChangeState(std::shared_ptr<CSpannerHoldOnState>(new CSpannerHoldOnState));
		return true;
	}
	else
		return false;
}

void CSpannerDefaultState::Update()
{

}

void CSpannerDefaultState::BehaviorInit()
{
	m_pSprite->setPosition(m_vStartPosition + CScrollManager::getInstance()->getDeltaPosition());
	m_pSprite->setVisible(true);
}