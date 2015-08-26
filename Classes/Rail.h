#pragma once
#include "cocos2d.h"
#include "Things.h"
#include "EDirection.h"
#include "DataStructure.h"
#include "b2Structure.h"
#include "PhysicsDefine.h"
#include <memory>
#include <vector>

USING_NS_CC;
using namespace std;

class CRailBehaviorState;
class CRailDefaultState;
class CRailRunState;
class Behavior;

class CRail :
	public CThings
{
	friend class CRailDefaultState;
	friend class CRailRunState;

public :
	void Scroll(Vec2 a_vScrollVelocity) override;

public :
	void Init(CCLayer* a_ParentLayer, b2World* a_World, RailData a_Data);
	bool Action(CCPoint a_vPos);
	void setStateToDefault(){}
	vector<shared_ptr<CBox2dSprite>>* getRailSpriteArr(){ return &m_parrRailSprite; }
	EDirection getDirection(){ return m_eCurrentDirection; }
	void ChangeState(shared_ptr<CRailBehaviorState> a_ptr);

public:
	CRail();
	~CRail();

private:
	shared_ptr<Behavior> CreateBehavior() override;
	void Active() override{}
	void DisActive() override{}

	CCSprite*	m_pLeverSprite;
	vector<shared_ptr<CBox2dSprite>>	m_parrRailSprite;
	CCTexture2D* m_pRailLeftTexture;
	CCTexture2D* m_pRailRightTexture;
	CCTexture2D* m_pLeverOnTexture;
	CCTexture2D* m_pLeverOffTexture;
	EDirection	m_eCurrentDirection;
	EDirection	m_eStartDirection;
};

