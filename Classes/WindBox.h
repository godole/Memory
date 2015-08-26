#pragma once
#include "cocos2d.h"
#include "Things.h"
#include "DataStructure.h"
#include "PhysicsDefine.h"
#include <memory>

class CWindBehaviorState;
class CBox2dSprite;

class CWindBox :
	public CThings
{
public :
	void Init(b2World* a_pWorld, WindBoxData a_Data);
	void ChangeState(std::shared_ptr<CWindBehaviorState> a_pState);

public :	//Things
	virtual void Active() override{}
	virtual void DisActive() override{}
	void setStateToDefault() override;
	void Scroll(Vec2 a_vScrollVelocity) override;

private :	//Things
	virtual shared_ptr<Behavior> CreateBehavior() override;

public:
	CWindBox();
	~CWindBox();

private :
	cocos2d::CCSprite* m_pSprite;
	std::shared_ptr<CBox2dSprite> m_pBox2dSprite;
	std::shared_ptr<CWindBehaviorState> m_pState;

	std::map<string, void*> m_ValueMap;
};

