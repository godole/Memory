#pragma once
#include "Timer.h"
#include "Box.h"
#include "Behavior.h"
#include "Update.h"
#include <map>
#include <string>

class CBoxBehaviorState :
	public Behavior
{
public:
	void Init(CBox* a_pBox, std::map<string, void* >* a_pValueMap);
	void setStateToDefault();
	string getIconFileName() override{ return "ui/motion.png"; }
	virtual void Update() = 0;

public :
	CBoxBehaviorState(){}
	~CBoxBehaviorState(){}

protected :
	bool IsPutable(TransectorProfile* profile, CCSprite* sprite, CCPoint touchPos, CCPoint& avaliablePos);

	CBox* m_pBox;
	std::map<string, void* >* m_pValueMap;
};