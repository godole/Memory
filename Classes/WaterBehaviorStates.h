#pragma once
#include "Behavior.h"
#include "Water.h"
#include "TransectorProfile.h"
#include <memory>

class CThings;
class CSand;

class CWaterBehaviorState :
	public Behavior
{
public:
	virtual void Init(CThings* a_pObject, std::map<string, void* >* a_pValueMap) override;
	void setStateToDefault();
	string getIconFileName() override{ return "ui/motion_water.png"; }

public:
	CWaterBehaviorState();
	~CWaterBehaviorState();

protected:
	CThings* m_pObject;
	std::map<string, void* >* m_pValueMap;

	TransectorProfile* m_pPlayerProfile;
	CCSprite* m_pWaterBlockSprite;
	CCSprite* m_pBottleSprite;
	CSand* m_pSand;
};



class CWaterDefaultState :
	public CWaterBehaviorState
{
public:
	virtual bool Action(Vec2 a_TouchPos);
	virtual void Update() override{}

public:
	CWaterDefaultState();
	~CWaterDefaultState();

private:
	virtual void BehaviorInit() override;
};



class CWaterHoldingState :
	public CWaterBehaviorState
{
public:
	virtual bool Action(Vec2 a_TouchPos);
	virtual void Update();

public:
	CWaterHoldingState();
	~CWaterHoldingState();

private:
	virtual void BehaviorInit() override;
};



class CWaterAfterState :
	public CWaterBehaviorState
{
public:
	virtual bool Action(Vec2 a_TouchPos);
	virtual void Update(){}

public:
	CWaterAfterState();
	~CWaterAfterState();

private:
	virtual void BehaviorInit() override;
};

