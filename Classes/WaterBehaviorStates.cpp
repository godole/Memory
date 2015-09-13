#include "WaterBehaviorStates.h"
#include "ObjectManager.h"
#include "Things.h"
#include "Sand.h"
#include "LayerDefine.h"


CWaterBehaviorState::CWaterBehaviorState()
{
}


CWaterBehaviorState::~CWaterBehaviorState()
{
}

void CWaterBehaviorState::Init(CThings* a_pObject, std::map<string, void* >* a_pValueMap)
{
	m_pObject = a_pObject;
	m_pValueMap = a_pValueMap;

	m_pWaterBlockSprite = _VMAP_STATIC_CAST(CCSprite*, "blockSprite");
	m_pBottleSprite = _VMAP_STATIC_CAST(CCSprite*, "bottleSprite");
	m_pPlayerProfile = _VMAP_STATIC_CAST(TransectorProfile*, "profile");
	m_pSand = _VMAP_STATIC_CAST(CSand*, "sand");

	BehaviorInit();
}

void CWaterBehaviorState::setStateToDefault()
{
	m_pObject->ChangeState(shared_ptr<CWaterDefaultState>(new CWaterDefaultState));
}



CWaterDefaultState::CWaterDefaultState()
{
}


CWaterDefaultState::~CWaterDefaultState()
{
}

bool CWaterDefaultState::Action(Vec2 a_TouchPos)
{
	if (!k_bIsDoing &&
		m_pWaterBlockSprite->getBoundingBox().containsPoint(a_TouchPos) &&
		m_pObject->getIsRanged())
	{
		k_bIsDoing = true;
		m_pBottleSprite->setVisible(true);
		m_pBottleSprite->setZOrder(2);
		m_pObject->ChangeState(std::shared_ptr<CWaterBehaviorState>(new CWaterHoldingState));
		return true;
	}
	else
		return false;
}

void CWaterDefaultState::BehaviorInit()
{
	m_pBottleSprite->setPosition(m_pBottleSprite->getPosition());
	m_pBottleSprite->setVisible(false);
	if (m_pSand != nullptr)
	{
		m_pSand->Off();
		m_pSand = nullptr;
	}
}



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
			(*m_pValueMap)["sand"] = sandarray->getObjectAt(i).get();
			sandarray->getObjectAt(i)->On();
			k_bIsDoing = false;
			m_pObject->ChangeState(shared_ptr<CWaterBehaviorState>(new CWaterAfterState));
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
	CCPoint holdPos = Director::getInstance()->getRunningScene()->getChildByTag(MAIN_LAYER)->getChildByTag(CHAR_NODE)->getPosition() + HOLD_POS;
	m_pBottleSprite->setPosition(holdPos);
}




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
	m_pBottleSprite->setPosition(m_pWaterBlockSprite->getPosition());
	m_pBottleSprite->setVisible(false);
}