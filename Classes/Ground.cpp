#include "Ground.h"
#include "ScrollManager.h"
#include "Box2dSprite.h"
#include "ObjectManager.h"
#include "LayerDefine.h"


CGround::CGround()
{
}


CGround::~CGround()
{
}

void CGround::Init(CCLayer* a_pParentLayer, b2World* a_World, GroundData a_data)
{
	auto sprite = CCSprite::create(a_data.m_szTextureName);
	a_pParentLayer->addChild(sprite, OBJECT_ZORDER);

	m_pBodySprite = shared_ptr<CBox2dSprite>(new CBox2dSprite);
	m_pBodySprite->Init(sprite, a_World, b2BodyType::b2_staticBody);

	setPositionTo(a_data.m_vPosition);

	CObjectManager::getInstance()->getBox2dSprite()->InsertObject(m_pBodySprite);
}

void CGround::setPositionTo(CCPoint a_Pos)
{
	m_pBodySprite->setPositionTo(a_Pos);
}

void CGround::Scroll(Vec2 a_vScrollVelocity)
{
	setPositionBy(a_vScrollVelocity);
}

void CGround::setPositionBy(CCPoint a_Pos)
{
	m_pBodySprite->setPositionBy(a_Pos);
}