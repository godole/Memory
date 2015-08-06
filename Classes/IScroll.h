#pragma once 
#include "ScrollManager.h"
#include "cocos2d.h"

USING_NS_CC;

class IScroll
{
public :
	IScroll()
	{
	}
	virtual void Scroll(Vec2 a_vScollVelocity) = 0;
};