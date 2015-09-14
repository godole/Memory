#pragma once
#include "Behavior.h"
#include "Update.h"

class CPulley;

class CPulleyBehaviorState :
	public Behavior
{
public :
	virtual void setStateToDefault();
	virtual string getIconFileName();
	virtual void Update() = 0;
	void Init(CPulley* a_pPulley);

public:
	CPulleyBehaviorState(){}
	~CPulleyBehaviorState(){}

protected:
	CPulley* m_pPulley;
};

