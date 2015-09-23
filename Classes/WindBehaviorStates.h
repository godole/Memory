#pragma once
#include "Behavior.h"
#include <map>
#include <memory>

class CThings;

class CWindBehaviorState :
	public Behavior
{
public:
	virtual void Init(CThings* a_pObject, std::map<string, void* >* a_pValueMap) override;
	void setStateToDefault();
	string getIconFileName() override{ return "ui/motion_wind.png"; }

public:
	CWindBehaviorState();
	~CWindBehaviorState();

protected:
	CThings* m_pObject;

	CCSprite* m_pSprite;
	CCParticleSystemQuad* m_pParticle;
	bool* m_pbIsRun;

	std::map<string, void*>* m_pValueMap;
};



class CWindDefaultState :
	public CWindBehaviorState
{
public:
	virtual bool Action(CCPoint a_vPosition);
	virtual void Update();
	virtual void BehaviorInit();

public:
	CWindDefaultState();
	~CWindDefaultState();
};



class CWindRunState :
	public CWindBehaviorState
{
public:
	virtual bool Action(CCPoint a_vPosition);
	virtual void Update();
	virtual void BehaviorInit();

public:
	CWindRunState();
	~CWindRunState();
};

