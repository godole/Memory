#include "Behavior.h"
#include "Update.h"
#include "PhysicsDefine.h"
#include "TransectorProfile.h"
#include <map>
#include <string>

class CThings;
class CBox2dSprite;


/*
 *******BoxBehaviorState
*/
class CBoxBehaviorState :
	public Behavior
{
public:
	virtual void Init(CThings* a_pObject, std::map<string, void* >* a_pValueMap) override;
	void setStateToDefault();
	string getIconFileName() override{ return "ui/motion.png"; }
	virtual void Update() {}

public:
	CBoxBehaviorState(){}
	~CBoxBehaviorState(){}

protected:
	bool IsPutable(TransectorProfile* profile, CCSprite* sprite, CCPoint touchPos, CCPoint& avaliablePos);

	CThings* m_pObject;
	std::map<string, void* >* m_pValueMap;
	CCSprite* m_pBoxSprite;
	CBox2dSprite* m_pBoxBodySprite;
	TransectorProfile* m_pPlayerProfile;
};


/*
*******BoxBehaviorState********
*/
class CBoxDefaultState :
	public CBoxBehaviorState
{
public:
	virtual bool Action(Vec2 a_TouchPos);
	virtual void Update() override{}

public:
	CBoxDefaultState(){}
	~CBoxDefaultState(){}

private:
	virtual void BehaviorInit() override;
};



/*
*******BoxBehaviorState********
*/
class CBoxHoldOnState :
	public CBoxBehaviorState
{
public:
	virtual bool Action(Vec2 a_TouchPos);
	virtual void Update();

public:
	CBoxHoldOnState(){}
	~CBoxHoldOnState(){}

private:
	virtual void BehaviorInit() override;
};



/*
*******BoxBehaviorState********
*/
class CBoxReadyState :
	public CBoxBehaviorState
{
public:
	virtual bool Action(Vec2 a_TouchPos);
	virtual void Update();

public:
	CBoxReadyState(){}
	~CBoxReadyState(){}

private:
	virtual void BehaviorInit() override;
};


/*
*******BoxBehaviorState********
*/
class CBoxAfterState :
	public CBoxBehaviorState
{
public:
	bool Action(Vec2 a_TouchPos);

public:
	CBoxAfterState(){}
	~CBoxAfterState(){}

private:
	void BehaviorInit() override;
};

