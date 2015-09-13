#include "Rail.h"
#include "ScrollManager.h"
#include "RailBehaviorStates.h"
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
	m_DataProfile.m_eStartDirection = a_Data.m_eStartDirection;
	m_DataProfile.m_eCurrentDirection = a_Data.m_eStartDirection;

	string objfileroot = "map/map2/object/";

	auto railLeft = CTextureFactory::CreateTexture(objfileroot + "rail_left.png");
	auto railRight = CTextureFactory::CreateTexture(objfileroot + "rail_right.png");

	for (int i = 0; i < a_Data.m_nRailCount; i++)
	{
		CCSprite* sprite;
		if (a_Data.m_eStartDirection == e_drLeft)
			sprite = CCSprite::createWithTexture(railLeft);

		else if (a_Data.m_eStartDirection == e_drRight)
			sprite = CCSprite::createWithTexture(railRight);

		a_ParentLayer->addChild(sprite, OBJECT_ZORDER);

		auto box2dsprite = shared_ptr<CBox2dSprite>(new CBox2dSprite);
		box2dsprite->Init(sprite, a_World, b2BodyType::b2_staticBody);
		box2dsprite->setPositionTo(ccp(a_Data.m_vPosition.x + sprite->getContentSize().width * i, a_Data.m_vPosition.y));

		CObjectManager::getInstance()->getBox2dSprite()->InsertObject(box2dsprite);
		CObjectManager::getInstance()->getNotBoxArray()->InsertObject(box2dsprite);
		m_parrRailSprite.push_back(box2dsprite);
	}

	auto leverOn = CTextureFactory::CreateTexture(objfileroot + "button_left_on.png");
	auto leverOff = CTextureFactory::CreateTexture(objfileroot + "button_right_off.png");

	m_pActionSprite = CCSprite::createWithTexture(leverOff);
	m_pActionSprite->setPosition(a_Data.m_vLeverPosition);
	a_ParentLayer->addChild(m_pActionSprite, OBJECT_ZORDER);

	m_ValueMap["leverSprite"] = m_pActionSprite;
	m_ValueMap["pedLeftTexture"] = railLeft;
	m_ValueMap["pedRightTexture"] = railRight;
	m_ValueMap["leverOnTexture"] = leverOn;
	m_ValueMap["leverOffTexture"] = leverOff;
	m_ValueMap["arrPed"] = &m_parrRailSprite;
	m_ValueMap["railProfile"] = &m_DataProfile;

	m_pBehavior = shared_ptr<CRailDefaultState>(new CRailDefaultState);
	m_pBehavior->Init(this, &m_ValueMap);
}

void CRail::Scroll(Vec2 a_vScrollVelocity)
{
	for (int i = 0; i < m_parrRailSprite.size(); i++)
	{
		m_parrRailSprite[i]->setPositionBy(a_vScrollVelocity);
	}
	m_pActionSprite->setPosition(m_pActionSprite->getPosition() + a_vScrollVelocity);
}