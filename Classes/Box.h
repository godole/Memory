#pragma once
#include "cocos2d.h"
#include "ThingsWithBody.h"
#include "DataStructure.h"
#include "TransectorProfile.h"
#include "b2Structure.h"
#include "PhysicsDefine.h"

USING_NS_CC;

class CBoxBehaviorState;
class CBoxDefaultState;
class CBoxHoldOnState;
class CBoxAfterState;
class Behavior;

class CBox :
	public CThingsWithBody
{
	friend class CBoxDefaultState;
	friend class CBoxHoldOnState;
	friend class CBoxAfterState;

public :
	void Init(CCLayer* a_ParentLayer, b2World* a_World, BoxData a_Data);
	void setStateToDefault() override;
	void ChangeState(shared_ptr<CBoxBehaviorState> a_Ptr);
	void Scroll(Vec2 a_vScrollVelocity);

public:
	CBox();
	~CBox();

private :
	virtual shared_ptr<Behavior> CreateBehavior() override;

	void Active() override{}
	void DisActive() override{}
	void ObjectUpdate() override;

	b2Body* m_pBody;
	CCSprite* m_pBoxSprite;
	TransectorProfile* m_pTransProfile;
	CCPoint m_vStartPosition;
	shared_ptr<CBoxBehaviorState> m_pBoxState;
};

