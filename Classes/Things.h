#pragma once
#include "cocos2d.h"
#include "IScroll.h"
#include "Update.h"
#include "TransectorProfile.h"
#include "physicsDefine.h"
#include <memory>

USING_NS_CC;
using namespace std;

class Behavior;
class CBox2dSprite;

class CThings :
	public IScroll,
	public IUpdate
{
public :
	void Update() final;

public :
	virtual void setTransectorProfile(TransectorProfile* a_pProfile){ m_pTransectorProfile = a_pProfile; }

	bool Action(Vec2 a_vTouchPos);
	shared_ptr<Behavior> getBehaviorPtr(){ return m_pBehavior; }
	bool getIsRanged(){ return m_bIsRanged; }

	virtual void	setStateToDefault() = 0;

public:
	CThings();
	~CThings();

protected :
	virtual shared_ptr<Behavior> CreateBehavior() = 0;
	virtual void	Active() = 0;
	virtual void	DisActive() = 0;
	virtual void	ObjectUpdate(){}

	TransectorProfile* m_pTransectorProfile;
	shared_ptr<Behavior> m_pBehavior;
	CCSprite* m_pActionSprite;
	bool m_bIsRanged;
};

