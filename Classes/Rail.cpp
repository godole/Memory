#include "Rail.h"
#include "ScrollManager.h"
#include "RailBehaviorState.h"
#include "RailDefaultState.h"
#include "RailRunState.h"
#include "Behavior.h"
#include "LayerDefine.h"
#include "ObjectManager.h"

CRail::CRail()
{
}


CRail::~CRail()
{
}

void CRail::Init(CCLayer* a_ParentLayer, b2World* a_World, RailData a_Data)
{
	m_eStartDirection = a_Data.m_eStartDirection;
	m_eCurrentDirection = a_Data.m_eStartDirection;

	auto railleft = new CCImage;
	railleft->initWithImageFile(a_Data.m_szRailLeftTextureName);
	m_pRailLeftTexture = new CCTexture2D;
	m_pRailLeftTexture->initWithImage(railleft);

	auto railright = new CCImage;
	railright->initWithImageFile(a_Data.m_szRailRightTextureName);
	m_pRailRightTexture = new CCTexture2D;
	m_pRailRightTexture->initWithImage(railright);

	if (a_Data.m_eStartDirection == e_drLeft)
		m_pRailSprite = CCSprite::createWithTexture(m_pRailLeftTexture);

	else if (a_Data.m_eStartDirection == e_drRight)
		m_pRailSprite = CCSprite::createWithTexture(m_pRailRightTexture);

	a_ParentLayer->addChild(m_pRailSprite, OBJECT_ZORDER);

	m_pBodySprite = shared_ptr<CBox2dSprite>(new CBox2dSprite);
	m_pBodySprite->Init(m_pRailSprite, a_World, b2BodyType::b2_staticBody);

	CObjectManager::getInstance()->getBox2dSprite()->InsertObject(m_pBodySprite);

	auto leveron = new CCImage;
	leveron->initWithImageFile(a_Data.m_szLeverOnTextureName);
	
	m_pLeverOnTexture = new CCTexture2D;
	m_pLeverOnTexture->initWithImage(leveron);

	auto leveroff = new CCImage;
	leveroff->initWithImageFile(a_Data.m_szLeverOnTextureName);

	m_pLeverOffTexture = new CCTexture2D;
	m_pLeverOffTexture->initWithImage(leveroff);

	m_pLeverSprite = CCSprite::createWithTexture(m_pLeverOffTexture);
	m_pLeverSprite->setPosition(a_Data.m_vLeverPosition);
	a_ParentLayer->addChild(m_pLeverSprite, OBJECT_ZORDER);

	m_pBehavior = CreateBehavior();

	m_pActionSprite = m_pLeverSprite;

	setBodyPositionTo(a_Data.m_vPosition);
}

void CRail::Scroll(Vec2 a_vScrollVelocity)
{
	setBodyPositionBy(a_vScrollVelocity);
	m_pLeverSprite->setPosition(m_pLeverSprite->getPosition() + a_vScrollVelocity);
}

void CRail::ChangeState(shared_ptr<CRailBehaviorState> a_ptr)
{
	a_ptr->Init(this);

	m_pBehavior = a_ptr;
}

shared_ptr<Behavior> CRail::CreateBehavior()
{
	auto state = shared_ptr<CRailDefaultState>(new CRailDefaultState);

	state->Init(this);

	return state;
}