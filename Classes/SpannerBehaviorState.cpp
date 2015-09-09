#include "SpannerBehaviorState.h"
#include "Spanner.h"


CSpannerBehaviorState::CSpannerBehaviorState()
{
}


CSpannerBehaviorState::~CSpannerBehaviorState()
{
}

void CSpannerBehaviorState::Init(CSpanner* a_pThings, std::map<string, void* >* a_pValueMap)
{
	m_pValueMap = a_pValueMap;
	m_pParent = a_pThings;

	m_pSprite = static_cast<CCSprite*>((*m_pValueMap)["sprite"]);
	m_vStartPosition = *static_cast<CCPoint*>((*m_pValueMap)["startPos"]);

	BehaviorInit();
}

void CSpannerBehaviorState::setStateToDefault()
{
	m_pParent->setStateToDefault();
}