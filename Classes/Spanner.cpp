#include "Spanner.h"
#include "LayerDefine.h"
#include "SpannerBehaviorState.h"
#include "SpannerDefaultState.h"

USING_NS_CC;
using namespace std;


CSpanner::CSpanner()
{
}


CSpanner::~CSpanner()
{
	delete m_vStartPosition;
}

void CSpanner::Init(cocos2d::CCLayer* parentLayer, TransectorProfile* profile, SpannerData data)
{
	m_pSprite = CCSprite::create("map/map2/object/box_fix.png");
	m_pSprite->setPosition(data.m_vPosition);
	parentLayer->addChild(m_pSprite, OBJECT_ZORDER);

	m_pTransectorProfile = profile;

	m_vStartPosition = new CCPoint(data.m_vPosition);

	m_ValueMap["sprite"] = m_pSprite;
	m_ValueMap["profile"] = profile;
	m_ValueMap["startPos"] = m_vStartPosition;
	m_ValueMap["door"] = nullptr;

	m_pBehavior = CreateBehavior();

	m_pActionSprite = m_pSprite;
}

void CSpanner::setStateToDefault()
{
	ChangeState(shared_ptr<CSpannerBehaviorState>(new CSpannerDefaultState));
}

void CSpanner::ObjectUpdate()
{
	m_pState->Update();
}

void CSpanner::Active()
{

}

void CSpanner::DisActive()
{

}

shared_ptr<Behavior> CSpanner::CreateBehavior()
{
	m_pState = shared_ptr<CSpannerBehaviorState>(new CSpannerDefaultState);
	m_pState->Init(this, &m_ValueMap);

	return m_pState;
}

void CSpanner::ChangeState(shared_ptr<CSpannerBehaviorState> a_Ptr)
{
	m_pState = a_Ptr;
	m_pState->Init(this, &m_ValueMap);

	m_pBehavior = a_Ptr;
}

void CSpanner::Scroll(Vec2 a_vVelocity)
{
	m_pSprite->setPosition(m_pSprite->getPosition() + a_vVelocity);
}