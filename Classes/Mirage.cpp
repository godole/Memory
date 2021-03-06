#include "Mirage.h"
#include "Behavior.h"
#include "LayerDefine.h"
#include "MirageBehaviorState.h"
#include "MirageDefaultState.h"
#include "MirageCrashedState.h"
#include "ObjectManager.h"
#include "CTextureFactory.h"


CMirage::CMirage()
{
}


CMirage::~CMirage()
{
}

void CMirage::Init(CCLayer* a_pParentLayer, b2World* a_World, MirageData a_Data)
{
	auto wallSprite = CCSprite::create("map/map3/object/box_wall.png");
	wallSprite->setPosition(a_Data.m_vWallPosition);
	a_pParentLayer->addChild(wallSprite, OBJECT_ZORDER);
	
	m_pWallSprite = wallSprite;

	m_pBodySprite = shared_ptr<CBox2dSprite>(new CBox2dSprite);
	m_pBodySprite->Init(wallSprite, a_World, b2BodyType::b2_staticBody);

	CObjectManager::getInstance()->getBox2dSprite()->InsertObject(m_pBodySprite);

	m_pBody = m_pBodySprite->getBodyStructure().body;

	m_pGlassTexture = CTextureFactory::CreateTexture("map/map3/object/glass.png");

	m_pGlassCrashedTexture = CTextureFactory::CreateTexture("map/map3/object/glass_piece.png");

	m_pGlassSprite = CCSprite::createWithTexture(m_pGlassTexture);
	m_pGlassSprite->setPosition(a_Data.m_vGlassPosition);

	setBodyPositionTo(a_Data.m_vWallPosition);
	a_pParentLayer->addChild(m_pGlassSprite, OBJECT_ZORDER);

	m_pActionSprite = m_pGlassSprite;

	m_pBehavior = CreateBehavior();
}

void CMirage::Scroll(Vec2 a_vScrollVelocity)
{
	setBodyPositionBy(a_vScrollVelocity);
	m_pGlassSprite->setPosition(m_pGlassSprite->getPosition() + a_vScrollVelocity);
}

bool CMirage::Action(CCPoint a_vPos)
{
	return m_pBehavior->Action(a_vPos);
}

void CMirage::ChangeState(shared_ptr<CMirageBehaviorState> a_ptr)
{
	a_ptr->Init(this);

	m_pBehavior = a_ptr;
}

void CMirage::setStateToDefault()
{
	ChangeState(shared_ptr<CMirageBehaviorState>(new CMirageDefaultState));
}

shared_ptr<Behavior> CMirage::CreateBehavior()
{
	auto behavior = shared_ptr<CMirageBehaviorState>(new CMirageDefaultState);
	behavior->Init(this);
	
	return behavior;
}