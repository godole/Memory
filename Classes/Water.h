#pragma once
#include "cocos2d.h"
#include "Things.h"
#include "DataStructure.h"
#include "TransectorProfile.h"
#include <memory>

USING_NS_CC;
using namespace std;
class CSand;

class CWater :
	public CThings
{
public:
	void Init(CCLayer* m_pParentLayer, TransectorProfile* a_Profile, WaterData a_data);
	void setStateToDefault() override;
	void Scroll(Vec2 a_vScrollVelocity);

public:
	void Active() override{}
	void DisActive() override{}

public:
	CWater();
	~CWater();

private :
	CCSprite* m_pWaterSprite;
	CCPoint m_vStartPosition;
};

