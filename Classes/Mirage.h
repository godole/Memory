#pragma once
#include "ThingsWithBody.h"
#include "DataStructure.h"
#include "MirageProfile.h"
#include "PhysicsDefine.h"
#include <memory>

using namespace std;

class CMirageBehaviorState;
class CMirageDefaultState;
class CMirageCrashedState;
class Behavior;

class CMirage :
	public CThingsWithBody
{
	friend class CMirageDefaultState;
	friend class CMirageCrashedState;

public :
	void		Init(CCLayer* a_pParentLayer, b2World* a_World, MirageData a_Data);
	void		ChangeState(shared_ptr<CMirageBehaviorState> a_ptr);
	void		setStateToDefault();
	bool		Action(CCPoint a_vPos);

public :
	void		Scroll(Vec2 a_vScrollVelocity);

public:
	CMirage();
	~CMirage();

private :
	virtual shared_ptr<Behavior> CreateBehavior() override;
	void Active(){}
	void DisActive(){}

	CCSprite* m_pGlassSprite;
	b2Body* m_pBody;
	CCTexture2D* m_pGlassCrashedTexture;
	CCTexture2D* m_pGlassTexture;
	CCSprite* m_pWallSprite;
};

