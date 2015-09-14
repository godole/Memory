#pragma once
#include "Behavior.h"
#include "Mirage.h"
#include "MirageProfile.h"
#include <memory>

using namespace std;

class CMirageDefaultState;

class CMirageBehaviorState :
	public Behavior
{
public :
	virtual void setStateToDefault();
	virtual string getIconFileName(){ return string("ui/motion_glass.png"); }
	void Init(CMirage* a_pMirage);

public:
	CMirageBehaviorState(){}
	~CMirageBehaviorState(){}

protected :
	CMirage* m_pMirage;
};

