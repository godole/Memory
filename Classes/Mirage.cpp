#include "Mirage.h"
#include "Behavior.h"
#include "LayerDefine.h"
#include "MirageBehaviorStates.h"
#include "ObjectManager.h"
#include "CTextureFactory.h"
#include "Things.h"
#include "Box2dSprite.h"


CMirage::CMirage()
{
}


CMirage::~CMirage()
{
}

void CMirage::Init(CCLayer* a_pParentLayer, b2World* a_World, MirageData a_Data)
{
	m_pWallSprite = CCSprite::create("map/map3/object/box_wall.png");
	m_pWallSprite->setPosition(a_Data.m_vWallPosition);
	a_pParentLayer->addChild(m_pWallSprite, OBJECT_ZORDER);

	m_pWallBodySprite = shared_ptr<CBox2dSprite>(new CBox2dSprite);
	m_pWallBodySprite->Init(m_pWallSprite, a_World, b2BodyType::b2_staticBody);
	m_pWallBodySprite->setPositionTo(a_Data.m_vWallPosition);

	CObjectManager::getInstance()->getBox2dSprite()->InsertObject(m_pWallBodySprite);
	CObjectManager::getInstance()->getNotBoxArray()->InsertObject(m_pWallBodySprite);

	m_pGlassTexture = CTextureFactory::CreateTexture("map/map3/object/glass.png");
	m_pGlassCrashedTexture = CTextureFactory::CreateTexture("map/map3/object/glass_piece.png");

	m_pActionSprite = CCSprite::createWithTexture(m_pGlassTexture);
	m_pActionSprite->setPosition(a_Data.m_vGlassPosition);
	a_pParentLayer->addChild(m_pActionSprite, OBJECT_ZORDER);

	m_ValueMap["glassSprite"] = m_pActionSprite;
	m_ValueMap["glassTexture"] = m_pGlassTexture;
	m_ValueMap["glassCrashedTexture"] = m_pGlassCrashedTexture;
	m_ValueMap["wallBodySprite"] = m_pWallBodySprite.get();

	m_pBehavior = shared_ptr<CMirageBehaviorState>(new CMirageDefaultState);
	m_pBehavior->Init(this, &m_ValueMap);
}

void CMirage::Scroll(Vec2 a_vScrollVelocity)
{
	m_pWallBodySprite->setPositionBy(a_vScrollVelocity);
	m_pActionSprite->setPosition(m_pActionSprite->getPosition() + a_vScrollVelocity);
}

void CMirage::setStateToDefault()
{
	ChangeState(shared_ptr<CMirageBehaviorState>(new CMirageDefaultState));
}