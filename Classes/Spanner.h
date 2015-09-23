#pragma once
#include "Things.h"
#include "DataStructure.h"
#include "TransectorProfile.h"
#include <map>
#include <string>
#include <memory>

class CSpannerBehaviorState;
class CSpannerDefaultState;

class CSpanner :
	public CThings
{
public:
	void Init(cocos2d::CCLayer* parentLayer, TransectorProfile* profile, SpannerData data);
	void setStateToDefault() override;

public:
	void Scroll(cocos2d::Vec2 a_vVelocity);

public:
	CSpanner();
	~CSpanner();

private:
	void Active() override;
	void DisActive() override;

	cocos2d::CCSprite* m_pSprite;
	CCPoint* m_vStartPosition;
};

