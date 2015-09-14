#pragma once
#include "Behavior.h"
#include "RailProfile.h"

class CRail;

class CRailBehaviorState :
	public Behavior
{
public :
	void Init(CRail* a_ptr);
	virtual void setStateToDefault();
	virtual string getIconFileName();
	virtual void setRanged(bool bIs){ m_bIsRanged = bIs; }

public:
	CRailBehaviorState(){}
	~CRailBehaviorState(){}

protected :
	CRail* m_pRail;
	bool m_bIsRanged;
};

