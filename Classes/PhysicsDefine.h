#pragma once

#include "Box2D/Box2D.h"
#include "cocos2d.h"

#define PTM_RATIO 72.0f

USING_NS_CC;

static b2Vec2 ChangeVecTob2Vec2(Vec2 Pos)
{
	return b2Vec2(Pos.x / PTM_RATIO, Pos.y / PTM_RATIO);
}
