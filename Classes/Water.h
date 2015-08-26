#pragma once
#include "cocos2d.h"
#include "Things.h"
#include "DataStructure.h"
#include "TransectorProfile.h"
#include <memory>

USING_NS_CC;
using namespace std;

class CWaterBehaviorState;
class CWaterDefaultState;
class CWaterHoldingState;
class CWaterAfterState;
class CSand;

class CWater :
	public CThings
{
	friend class CWaterBehaviorState;
	friend class CWaterDefaultState;
	friend class CWaterHoldingState;
	friend class CWaterAfterState;
	   
public:
	CWater();
	~CWater();
public :
	void Init(CCLayer* m_pParentLayer, TransectorProfile* a_Profile, WaterData a_data);
	void setStateToDefault() override;
	void ChangeState(shared_ptr<CWaterBehaviorState> m_pWaterState);
	void Scroll(Vec2 a_vScrollVelocity);

public :
	void Active() override{}
	void DisActive() override{}
	void ObjectUpdate() override;

private :
	virtual shared_ptr<Behavior> CreateBehavior() override;

	shared_ptr<CWaterBehaviorState> m_pWaterState;
	CCSprite* m_pSprite;
	CCSprite* m_pWaterSprite;
	shared_ptr<CSand> m_pSand;
	CCPoint m_vStartPosition;
};

