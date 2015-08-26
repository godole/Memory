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

void CWindBox::Init(b2World* a_pWorld, WindBoxData a_Data)
{
	auto parentLayer = Director::sharedDirector()->getRunningScene()->getChildByName(OBJ_LAYER);

	m_pSprite = CCSprite::create("map/map3/object/box_wind.png");
	m_pSprite->setPosition(a_Data.m_vPosition);
	parentLayer->addChild(m_pSprite);

	m_pBox2dSprite = shared_ptr<CBox2dSprite>(new CBox2dSprite);
	m_pBox2dSprite->Init(m_pSprite, a_pWorld, b2BodyType::b2_staticBody, 70, 70);
	CObjectManager::getInstance()->getBox2dSprite()->InsertObject(m_pBox2dSprite);
	
	m_ValueMap.insert({ "sprite", (void*)m_pSprite });
	m_ValueMap.insert({ "box2dsprite", (void*)m_pBox2dSprite.get() });

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
	CThings::m_pBehavior = m_pState;

	return m_pState;
}

void CWindBox::ChangeState(shared_ptr<CWindBehaviorState> a_pBehavior)
{
	a_pBehavior->Init(this, &m_ValueMap);

	m_pState = a_pBehavior;
	m_pBehavior = a_pBehavior;
}