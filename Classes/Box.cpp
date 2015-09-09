#include "Box.h"
#include "BoxBehaviorState.h"
#include "BoxDefaultState.h"
#include "BoxHoldOnState.h"
#include "BoxAfterState.h"
#include "ObjectManager.h"
#include "UpdateManager.h"
#include "ScrollManager.h"
#include "Behavior.h"
#include "Box2dSprite.h"
#include "LayerDefine.h"


CBox::CBox()
{
}

CBox::~CBox()
{
}

void CBox::Init(CCLayer* a_ParentLayer, b2World* a_World, BoxData a_Data)
{
	m_vStartPosition = a_Data.m_vStartPosition;
	m_pBoxSprite = CCSprite::create(a_Data.m_szTextureName);
	m_ValueMap["spriteName"] = new string(a_Data.m_szTextureName);

	m_ValueMap["holdPosition"] = (void*)m_pTransectorProfile->m_vpHoldingPosition;
	
	m_pTransProfile = m_pTransectorProfile;

	m_pBodySprite = shared_ptr<CBox2dSprite>(new CBox2dSprite);
	m_pBodySprite->Init(m_pBoxSprite, a_World, b2BodyType::b2_staticBody, 80, 80);
	m_pBody = m_pBodySprite->getBodyStructure().body;
	a_ParentLayer->addChild(m_pBoxSprite, OBJECT_ZORDER);
	CObjectManager::getInstance()->getBox2dSprite()->InsertObject(m_pBodySprite);

	m_pActionSprite = m_pBoxSprite;

	m_ValueMap["readySprite"] = nullptr;
	m_ValueMap["bodySprite"] = m_pBoxSprite;
	m_ValueMap["profile"] = m_pTransectorProfile;

	m_pBehavior = CreateBehavior();
}

void CBox::setStateToDefault()
{
	ChangeState(shared_ptr<CBoxDefaultState>(new CBoxDefaultState));
}

void CBox::ChangeState(shared_ptr<CBoxBehaviorState> a_Ptr)
{
	a_Ptr->Init(this, &m_ValueMap);

	m_pBehavior = a_Ptr;
	m_pBoxState = a_Ptr;
}

shared_ptr<Behavior> CBox::CreateBehavior()
{
	m_pBoxState = shared_ptr<CBoxDefaultState>(new CBoxDefaultState);
	m_pBoxState->Init(this, &m_ValueMap);

	return m_pBoxState;
}

void CBox::Scroll(Vec2 a_vScrollVelocity)
{
	setBodyPositionBy(a_vScrollVelocity);
	if (m_ValueMap["readySprite"] != nullptr)
	{
		auto sprite = static_cast<CCSprite*>(m_ValueMap["readySprite"]);
		sprite->setPosition(sprite->getPosition() + a_vScrollVelocity);
	}
	
}

void CBox::ObjectUpdate()
{
	m_pBoxState->Update();
}