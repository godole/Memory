#pragma once
#include "cocos2d.h"

USING_NS_CC;

class TransectorProfile
{
public:
	CCPoint*	m_vpHoldingPosition;
	CCPoint		m_vCurrentPosition;
	CCRect		m_TransectRange;
};

#define HOLD_POS ccp(0, 80)