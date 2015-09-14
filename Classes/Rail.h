#pragma once
#include "cocos2d.h"
#include "Things.h"
#include "EDirection.h"
#include "DataStructure.h"
#include "b2Structure.h"
#include "PhysicsDefine.h"
#include "RailProfile.h"
#include <memory>
#include <vector>

USING_NS_CC;
using namespace std;

class CRail :
	public CThings
{
public :
	void Scroll(Vec2 a_vScrollVelocity) override;

public :
	void Init(CCLayer* a_ParentLayer, b2World* a_World, RailData a_Data);
	bool Action(CCPoint a_vPos);
	void setStateToDefault(){}
	vector<shared_ptr<CBox2dSprite>>* getRailSpriteArr(){ return &m_parrRailSprite; }
	EDirection getDirection(){ return m_DataProfile.m_eCurrentDirection; }

public:
	CRail();
	~CRail();

private:
	void Active() override{}
	void DisActive() override{}
	
	vector<shared_ptr<CBox2dSprite>>	m_parrRailSprite;
	RailProfile m_DataProfile;
};

