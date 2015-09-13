#pragma once
#include "cocos2d.h"
#include "EDirection.h"
#include "Box2dSprite.h"

USING_NS_CC;

struct RailProfile
{
	EDirection	m_eCurrentDirection;
	EDirection	m_eStartDirection;
};