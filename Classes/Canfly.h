#pragma once
#include "cocos2d.h"
#include "PhysicsDefine.h"

class ICanfly
{
public :
	virtual void Fly(cocos2d::Vec2 a_vVelocity) = 0;
	virtual cocos2d::Rect getCanFlyRect() = 0;
};