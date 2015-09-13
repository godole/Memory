#include "Rail.h"
#include "ScrollManager.h"
#include "RailBehaviorState.h"
#include "RailDefaultState.h"
#include "RailRunState.h"
#include "Behavior.h"
#include "LayerDefine.h"
#include "ObjectManager.h"
#include "CTextureFactory.h"

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

	string objfileroot = "map/map2/object/";

	m_pRailLeftTexture = CTextureFactory::CreateTexture(objfileroot + "rail_left.png");
	m_pRailRightTexture = CTextureFactory::CreateTexture(objfileroot + "rail_right.png");

	for (int i = 0; i < a_Data.m_nRailCount; i++)
	{
		CCSprite* sprite;
		if (a_Data.m_eStartDirection == e_drLeft)
			sprite = CCSprite::createWithTexture(m_pRailLeftTexture);

		else if (a_Data.m_eStartDirection == e_drRight)
			sprite = CCSprite::createWithTexture(m_pRailRightTexture);

		a_ParentLayer->addChild(sprite, OBJECT_ZORDER);

		auto box2dsprite = shared_ptr<CBox2dSprite>(new CBox2dSprite);
		box2dsprite->Init(sprite, a_World, b2BodyType::b2_staticBody);
		box2dsprite->setPositionTo(ccp(a_Data.m_vPosition.x + sprite->getContentSize().width * i, a_Data.m_vPosition.y));

		CObjectManager::getInstance()->getBox2dSprite()->InsertObject(box2dsprite);
		m_parrRailSprite.push_back(box2dsprite);
	}

	m_pLeverOnTexture = CTextureFactory::CreateTexture(objfileroot + "button_left_on.png");
	m_pLeverOffTexture = CTextureFactory::CreateTexture(objfileroot + "button_right_off.png");

	m_pLeverSprite = CCSprite::createWithTexture(m_pLeverOffTexture);
	m_pLeverSprite->setPosition(a_Data.m_vLeverPosition);
	a_ParentLayer->addChild(m_pLeverSprite, OBJECT_ZORDER);

	m_pBehavior = CreateBehavior();

	m_pActionSprite = m_pLeverSprite;
}

void CRail::Scroll(Vec2 a_vScrollVelocity)
{
	for (int i = 0; i < m_parrRailSprite.size(); i++)
	{
		m_parrRailSprite[i]->setPositionBy(a_vScrollVelocity);
	}
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