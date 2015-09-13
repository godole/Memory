#include "Water.h"
#include "LayerDefine.h"
#include "WaterBehaviorStates.h"
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
	m_pActionSprite = CCSprite::create("map/map3/object/waterblock.png");
	m_pActionSprite->setPosition(a_data.m_vPosition);
	m_pParentLayer->addChild(m_pActionSprite, OBJECT_ZORDER);

	m_pWaterSprite = CCSprite::create("map/map3/object/bottle.png");
	m_pWaterSprite->setPosition(a_data.m_vPosition);
	m_pWaterSprite->setVisible(false);
	m_pParentLayer->addChild(m_pWaterSprite, OBJECT_ZORDER);

	m_vStartPosition = a_data.m_vPosition;
	m_pTransectorProfile = a_Profile;

	m_ValueMap["blockSprite"] = m_pActionSprite;
	m_ValueMap["bottleSprite"] = m_pWaterSprite;
	m_ValueMap["profile"] = m_pTransectorProfile;
	m_ValueMap["sand"] = nullptr;

	m_pBehavior = shared_ptr<CWaterBehaviorState>(new CWaterDefaultState);
	m_pBehavior->Init(this, &m_ValueMap);
}

void CWater::setStateToDefault()
{
	ChangeState(shared_ptr<CWaterBehaviorState>(new CWaterDefaultState));
}

void CWater::Scroll(Vec2 a_vScrollVelocity)
{
	m_pActionSprite->setPosition(m_pActionSprite->getPosition() + a_vScrollVelocity);
}