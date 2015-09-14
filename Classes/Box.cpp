#include "Box.h"
#include "BoxBehaviorStates.h"
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
	m_pActionSprite = CCSprite::create(a_Data.m_szTextureName);
	
	m_pTransProfile = m_pTransectorProfile;

	m_pBodySprite = shared_ptr<CBox2dSprite>(new CBox2dSprite);
	m_pBodySprite->Init(m_pActionSprite, a_World, b2BodyType::b2_staticBody, 90, 90);
	a_ParentLayer->addChild(m_pActionSprite, OBJECT_ZORDER);
	CObjectManager::getInstance()->getBox2dSprite()->InsertObject(m_pBodySprite);
	CObjectManager::getInstance()->getNotBoxArray()->InsertObject(m_pBodySprite);

	m_ValueMap["spriteName"] = new string(a_Data.m_szTextureName);
	m_ValueMap["holdPosition"] = (void*)m_pTransectorProfile->m_vpHoldingPosition;
	m_ValueMap["startPosition"] = &m_vStartPosition;
	m_ValueMap["readySprite"] = nullptr;
	m_ValueMap["sprite"] = m_pActionSprite;
	m_ValueMap["bodySprite"] = m_pBodySprite.get();
	m_ValueMap["profile"] = m_pTransectorProfile;

	m_pBehavior = shared_ptr<CBoxDefaultState>(new CBoxDefaultState);
	m_pBehavior->Init(this, &m_ValueMap);
}

void CBox::setStateToDefault()
{
	ChangeState(shared_ptr<CBoxDefaultState>(new CBoxDefaultState));
}

void CBox::Scroll(Vec2 a_vScrollVelocity)
{
	m_pBodySprite->setPositionBy(a_vScrollVelocity);
	if (m_ValueMap["readySprite"] != nullptr)
	{
		auto sprite = static_cast<CCSprite*>(m_ValueMap["readySprite"]);
		sprite->setPosition(sprite->getPosition() + a_vScrollVelocity);
	}
	
}