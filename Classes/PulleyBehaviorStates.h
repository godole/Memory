#pragma once
#include "cocos2d.h"
#include "Behavior.h"
#include "Update.h"
#include "PulleyProfile.h"

USING_NS_CC;

class CThings;
class CBox2dSprite;

class CPulleyBehaviorState :
	public Behavior
{
public:
	virtual void Init(CThings* a_pObject, std::map<string, void* >* a_pValueMap) override;
	virtual void setStateToDefault();
	virtual string getIconFileName();
	virtual void Update() override{}

public:
	CPulleyBehaviorState(){}
	~CPulleyBehaviorState(){}

protected:
	CThings* m_pObject;
	std::map<string, void* >* m_pValueMap;
	CCSprite* m_pLeverSprite;
	vector<shared_ptr<CBox2dSprite>>* m_parPed;
	PulleyProfile* m_pData;
};




class CPulleyDefaultState :
	public CPulleyBehaviorState
{
public:
	bool Action(CCPoint a_vPos) override;
	void Update(){}

public:
	CPulleyDefaultState(){}
	~CPulleyDefaultState(){}

private:
	void BehaviorInit() override;
};



class CPulleyRunState :
	public CPulleyBehaviorState
{
public:
	bool Action(CCPoint a_vPos);
	void Update();

public:
	CPulleyRunState(){}
	~CPulleyRunState(){}

private:
	void BehaviorInit();
};

