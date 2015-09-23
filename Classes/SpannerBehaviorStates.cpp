#include "SpannerBehaviorStates.h"
#include "Door.h"
#include "ObjectManager.h"
#include "Things.h"


CSpannerBehaviorState::CSpannerBehaviorState()
{
}


CSpannerBehaviorState::~CSpannerBehaviorState()
{
}

void CSpannerBehaviorState::Init(CThings* a_pObject, std::map<string, void* >* a_pValueMap)
{
	m_pValueMap = a_pValueMap;
	m_pObject = a_pObject;

	m_pSprite = _VMAP_STATIC_CAST(CCSprite*, "sprite");
	m_vStartPosition = *_VMAP_STATIC_CAST(CCPoint*, "startPos");//*static_cast<CCPoint*>((*m_pValueMap)["startPos"]);

	BehaviorInit();
}

void CSpannerBehaviorState::setStateToDefault()
{
	m_pObject->ChangeState(shared_ptr<CSpannerDefaultState>(new CSpannerDefaultState));
}



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
		m_pObject->getIsRanged())
	{
		k_bIsDoing = true;
		m_pObject->ChangeState(std::shared_ptr<CSpannerHoldOnState>(new CSpannerHoldOnState));
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

	if ((*m_pValueMap)["door"] != nullptr)
	{
		_VMAP_STATIC_CAST(CDoor*, "door")->Off();
	}
}



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
			m_pObject->ChangeState(shared_ptr<CSpannerBehaviorState>(new CSpannerUsedState));
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



CSpannerUsedState::CSpannerUsedState()
{
}


CSpannerUsedState::~CSpannerUsedState()
{
}

bool CSpannerUsedState::Action(Vec2 a_TouchPos)
{
	return false;
}

void CSpannerUsedState::Update()
{

}

void CSpannerUsedState::BehaviorInit()
{

}