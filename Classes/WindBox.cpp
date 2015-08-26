#include "WindBox.h"
#include "LayerDefine.h"
#include "WindBehaviorState.h"
#include "WindDefaultState.h"
#include "Box2dSprite.h"
#include "ObjectManager.h"
#include <map>

using namespace cocos2d;
using namespace std;

CWindBox::CWindBox()
{
}


CWindBox::~CWindBox()
{
}

void CWindBox::Init(CCLayer* a_pParentLayer, b2World* a_pWorld, TransectorProfile* a_Profile, WindBoxData a_Data)
{
	m_pSprite = CCSprite::create("map/map3/object/box_wind.png");
	a_pParentLayer->addChild(m_pSprite);

	m_pTransectorProfile = a_Profile;

	m_pBox2dSprite = shared_ptr<CBox2dSprite>(new CBox2dSprite);
	m_pBox2dSprite->Init(m_pSprite, a_pWorld, b2BodyType::b2_staticBody, 70, 70);
	m_pBox2dSprite->setPositionTo(a_Data.m_vPosition);
	CObjectManager::getInstance()->getBox2dSprite()->InsertObject(m_pBox2dSprite);
	
	m_ValueMap.insert({ "sprite", (void*)m_pSprite });
	m_ValueMap.insert({ "box2dsprite", (void*)m_pBox2dSprite.get() });

	m_pActionSprite = m_pSprite;

	m_pBehavior = CreateBehavior();
}

void CWindBox::setStateToDefault()
{
	ChangeState(shared_ptr<CWindBehaviorState>(new CWindDefaultState));
}

void CWindBox::Scroll(Vec2 a_vScrollVelocity)
{
	m_pBox2dSprite->setPositionBy(a_vScrollVelocity);
}

shared_ptr<Behavior> CWindBox::CreateBehavior()
{
	m_pState = shared_ptr<CWindBehaviorState>(new CWindDefaultState);
	m_pState->Init(this, &m_ValueMap);
	CThings::m_pBehavior = m_pState;

	return m_pState;
}

void CWindBox::ChangeState(shared_ptr<CWindBehaviorState> a_pBehavior)
{
	a_pBehavior->Init(this, &m_ValueMap);

	m_pState = a_pBehavior;
	m_pBehavior = a_pBehavior;
}