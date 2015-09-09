#include "Ped.h"
#include "Box2dSprite.h"
#include "LayerDefine.h"

using namespace cocos2d;

CPed::CPed()
{
}


CPed::~CPed()
{
}

void CPed::Init(cocos2d::CCLayer* parentLayer, b2World* world, PedData data)
{
	auto sprite = CCSprite::create(data.m_szTextureName);
	parentLayer->addChild(sprite, OBJECT_ZORDER);

	m_pBox2dSprite = shared_ptr<CBox2dSprite>(new CBox2dSprite);
	m_pBox2dSprite->Init(sprite, world,b2BodyType::b2_staticBody, 80, 80);
	m_pBox2dSprite->setPositionTo(data.m_vPosition);
}

void CPed::Scroll(cocos2d::Vec2 a_vVelocity)
{
	m_pBox2dSprite->setPositionBy(a_vVelocity);
}