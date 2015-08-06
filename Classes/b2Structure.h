#ifndef __B2_STRUCTURE__
#define __B2_STRUCTURE__
#include "cocos2d.h"
#include "PhysicsDefine.h"

USING_NS_CC;

struct b2Structure
{
	b2BodyDef bodyDef;
	b2Body* body;
	b2FixtureDef fixtureDef;
	b2Fixture* fixture;
};

static b2Structure CreateStructure(b2World* world, CCSprite* sprite, b2BodyType type, CCPoint anchor = Vec2::ANCHOR_MIDDLE)
{
	b2Structure structure;

	structure.bodyDef.userData = sprite;
	structure.bodyDef.type = type;
	structure.body = world->CreateBody(&structure.bodyDef);
	b2PolygonShape shape;
	float centerX = (0.5f - sprite->getAnchorPoint().x) * sprite->getContentSize().width / PTM_RATIO;
	float centerY = (0.5f - sprite->getAnchorPoint().y) * sprite->getContentSize().height / PTM_RATIO;
	shape.SetAsBox((sprite->getContentSize().width / 2) / PTM_RATIO, (sprite->getContentSize().height / 2) / PTM_RATIO,
	{ centerX, centerY }, 0);
	structure.fixture = structure.body->CreateFixture(&shape, 0.0);

	return structure;
}

static b2Structure CreateStaticStructure(b2World* world, CCSprite* sprite, CCPoint anchor = Vec2::ANCHOR_MIDDLE)
{
	b2Structure structure = CreateStructure(world, sprite, b2_staticBody, anchor);

	return structure;
}

static b2Structure CreateDynamicStructure(b2World* world, CCSprite* sprite, CCPoint anchor = Vec2::ANCHOR_MIDDLE)
{
	b2Structure structure = CreateStructure(world, sprite, b2_dynamicBody, anchor);

	return structure;
}

#endif