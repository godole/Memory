#pragma once
#include "Behavior.h"
#include <memory>

USING_NS_CC;
using namespace std;

class CThings;
class CBox2dSprite;

class CMirageBehaviorState :
	public Behavior
{
public:
	virtual void Init(CThings* a_pObject, std::map<string, void* >* a_pValueMap) override;
	virtual void setStateToDefault();
	virtual string getIconFileName(){ return string("ui/motion_glass.png"); }
	virtual void Update(){}

public:
	CMirageBehaviorState(){}
	~CMirageBehaviorState(){}

protected:
	CThings* m_pObject;
	std::map<string, void* >* m_pValueMap;
	CCSprite* m_pGlassSprite;
	CCSprite* m_pWallSprite;
	CBox2dSprite* m_pWallBodySprite;
};



class CMirageDefaultState :
	public CMirageBehaviorState
{
public:
	bool Action(CCPoint a_Pos) override;

public:
	CMirageDefaultState(){}
	~CMirageDefaultState() {}

private:
	virtual void BehaviorInit() override;

};




class CMirageCrashedState :
	public CMirageBehaviorState
{
public:
	bool Action(CCPoint a_Pos);

public:
	CMirageCrashedState(){}
	~CMirageCrashedState(){}

private:
	virtual void BehaviorInit() override;
};

