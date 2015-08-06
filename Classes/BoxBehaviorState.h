#pragma once
#include "Timer.h"
#include "Box.h"
#include "Behavior.h"
#include "Update.h"

class CBoxBehaviorState :
	public Behavior
{
public:
	void Init(CBox* a_pBox);
	void setStateToDefault();
	string getIconFileName() override{ return "ui/motion.png"; }
	virtual void Update() = 0;

public :
	CBoxBehaviorState(){}
	~CBoxBehaviorState(){}

protected :
	CBox* m_pBox;
};