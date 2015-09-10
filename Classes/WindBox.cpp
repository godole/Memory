#include "WindBox.h"
#include "LayerDefine.h"
#include "WindBehaviorState.h"
#include "WindDefaultState.h"
#include "Box2dSprite.h"
#include "ObjectManager.h"
#include <map>
#include "Canfly.h"

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
	a_pParentLayer->addChild(m_pSprite, OBJECT_ZORDER);

	m_pTransectorProfile = a_Profile;

	m_pBox2dSprite = shared_ptr<CBox2dSprite>(new CBox2dSprite);
	m_pBox2dSprite->Init(m_pSprite, a_pWorld, b2BodyType::b2_staticBody, 90, 90);
	m_pBox2dSprite->setPositionTo(a_Data.m_vPosition);
	CObjectManager::getInstance()->getBox2dSprite()->InsertObject(m_pBox2dSprite);
	
	m_ValueMap.insert({ "sprite", (void*)m_pSprite });
	m_ValueMap.insert({ "box2dsprite", (void*)m_pBox2dSprite.get() });
	m_ValueMap["bIsRun"] = (void*)&m_bIsRun;
	m_ValueMap["particle"] = nullptr;

	m_pActionSprite = m_pSprite;

	m_pBehavior = CreateBehavior();

	m_bIsRun = false;
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

void CWindBox::MakeFly(ICanfly* a_pCanfly)
{
	if (!m_bIsRun)
		return;

	CCRect r;
	r.setRect(m_pSprite->getBoundingBox().getMinX(), m_pSprite->getBoundingBox().getMaxY(), 100, 400);
	auto objarr = CObjectManager::getInstance()->getBox2dSprite()->getObjectArray();

	for (auto itr = objarr.begin(); itr != objarr.end(); ++itr)
	{
		if ((*itr) == m_pBox2dSprite)
			continue;

		CCRect r2 = (*itr)->getSpritePtr()->getBoundingBox();
		if (r.intersectsRect(r2))
		{
			r.setRect(m_pSprite->getBoundingBox().getMinX(), m_pSprite->getBoundingBox().getMaxY(), 100, r2.getMinY() - r.getMinY());
			break;
		}
	}

	if (r.intersectsRect(a_pCanfly->getCanFlyRect()))
	{
		float percent = 100 - ((a_pCanfly->getCanFlyRect().getMinY() - r.getMinY()) / 300 * 120);
		if (percent >= 0)
		a_pCanfly->Fly(Vec2(0, 4));
	}
}