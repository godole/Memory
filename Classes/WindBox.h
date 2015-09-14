#pragma once
#include "cocos2d.h"
#include "Things.h"
#include "DataStructure.h"
#include "PhysicsDefine.h"
#include <memory>

class CWindBehaviorState;
class CBox2dSprite;
class ICanfly;

class CWindBox :
	public CThings
{
public :
	void MakeFly(ICanfly* a_pCanfly);

public :
	void Init(cocos2d::CCLayer* a_pParentLayer, b2World* a_pWorld, TransectorProfile* a_Profile, WindBoxData a_Data);

public :	//Things
	virtual void Active() override{}
	virtual void DisActive() override{}
	void setStateToDefault() override;
	void Scroll(Vec2 a_vScrollVelocity) override;

public:
	CWindBox();
	~CWindBox();

private :
	std::shared_ptr<CBox2dSprite> m_pBox2dSprite;

	bool m_bIsRun;
};

