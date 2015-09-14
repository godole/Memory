#pragma once
#include "Behavior.h"
#include <map>
#include <memory>

class CWindBox;

class CWindBehaviorState :
	public Behavior
{
public :
	void Init(CWindBox* a_pThings, std::map<string, void*>* a_pvalueMap);
	void setStateToDefault();
	string getIconFileName() override{ return "ui/motion_wind.png"; }
	virtual void Update() = 0;

public:
	CWindBehaviorState();
	~CWindBehaviorState();

protected :
	CWindBox* m_pThings;
	std::map<string, void*>* m_pValueMap;
};

