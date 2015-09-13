#pragma once
#include "Things.h"
#include "Update.h"
#include "EDirection.h"
#include "DataStructure.h"
#include "PulleyProfile.h"
#include "PhysicsDefine.h"
#include "b2Structure.h"
#include <memory>
#include <vector>

using namespace std;

class Behavior;

class CPulley :
	public CThings
{
	friend class CPulleyDefaultState;
	friend class CPulleyRunState;

public :
	void		Init(CCLayer* a_pParentLayer,b2World* a_World, PulleyData a_Data);
	void		setStateToDefault();

public :
	void		Scroll(Vec2 a_vScrollVelocity);

public:
	CPulley();
	~CPulley();

private :
	void Active() override{}
	void DisActive() override{}

	vector<shared_ptr<CBox2dSprite>> m_parrPulleySprite;

	PulleyProfile m_DataProfile;
};

