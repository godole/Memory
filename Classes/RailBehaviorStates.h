#pragma once
#include "Behavior.h"
#include "RailProfile.h"

class CThings;

class CRailBehaviorState :
	public Behavior
{
public:
	virtual void Init(CThings* a_pObject, std::map<string, void* >* a_pValueMap) override;
	virtual void setStateToDefault();
	virtual string getIconFileName(){ return "ui/motion_rail.png"; }
	virtual void Update(){}

public:
	CRailBehaviorState(){}
	~CRailBehaviorState(){}

protected:
	CThings* m_pObject;
	std::map<string, void* >* m_pValueMap;
	CCSprite* m_pLeverSprite;
	vector<shared_ptr<CBox2dSprite>>* m_parPed;
	RailProfile* m_pData;
};


class CRailDefaultState :
	public CRailBehaviorState
{
public:
	virtual bool Action(CCPoint a_Pos) override;

public:
	CRailDefaultState(){}
	~CRailDefaultState(){}

private:
	virtual void BehaviorInit() override;
};


class CRailRunState :
	public CRailBehaviorState
{
public:
	virtual bool Action(CCPoint a_Pos) override;

public:
	CRailRunState(){}
	~CRailRunState(){}

private:
	void BehaviorInit();
};

