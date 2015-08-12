#include "Water.h"
#include "LayerDefine.h"
#include "WaterBehaviorState.h"
#include "WaterDefaultState.h"
#include "WaterHoldingState.h"
#include "WaterAfterState.h"
#include "Sand.h"


CWater::CWater()
{
	m_pWaterSprite = nullptr;
}


CWater::~CWater()
{
}

void CWater::Init(CCLayer* m_pParentLayer, TransectorProfile* a_Profile, WaterData a_data)
{
	m_pSprite = CCSprite::create("object/bottle.png");
	m_pSprite->setPosition(a_data.m_vPosition);
	m_pParentLayer->addChild(m_pSprite);

	m_pWaterSprite = CCSprite::create("map/map3/object/bottle.png");
	m_pWaterSprite->setPosition(a_data.m_vPosition);
	m_pWaterSprite->setVisible(false);
	m_pParentLayer->addChild(m_pWaterSprite);

	m_pTransectorProfile = a_Profile;
}

void CWater::setStateToDefault()
{

}

void CWater::Scroll(Vec2 a_vScrollVelocity)
{
	m_pSprite->setPosition(m_pSprite->getPosition() + a_vScrollVelocity);
}

void CWater::ChangeState(shared_ptr<CWaterBehaviorState> m_pWaterState)
{

}

shared_ptr<Behavior> CWater::CreateBehavior()
{
	m_pWaterState = shared_ptr<CWaterDefaultState>(shared_ptr<CWaterDefaultState>(new CWaterDefaultState));

	return m_pWaterState;
}