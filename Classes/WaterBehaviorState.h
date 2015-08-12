#pragma once
#include "Behavior.h"
#include "Water.h"

class CWaterBehaviorState :
	public Behavior
{
public :
	void Init(CWater* a_pWater);
	void setStateToDefault();
	string getIconFileName() override{ return "ui/motion.png"; }
	virtual void Update() = 0;

public:
	CWaterBehaviorState();
	~CWaterBehaviorState();

protected :
	CWater* m_pWater;
};

