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

class CPulleyBehaviorState;
class CPulleyDefaultState;
class CPulleyRunState;
class Behavior;

class CPulley :
	public CThings
{
	friend class CPulleyDefaultState;
	friend class CPulleyRunState;

public :
	void		Init(CCLayer* a_pParentLayer,b2World* a_World, PulleyData a_Data);
	void		ChangeState(shared_ptr<CPulleyBehaviorState> a_ptr);
	void		setStateToDefault();

public :
	void		Scroll(Vec2 a_vScrollVelocity);

public:
	CPulley();
	~CPulley();

private :
	shared_ptr<Behavior> CreateBehavior() override;
	void Active() override{}
	void DisActive() override{}
	void ObjectUpdate() override;

	shared_ptr<CPulleyBehaviorState> m_pPulleyState;

	vector<shared_ptr<CBox2dSprite>> m_parrPulleySprite;
	CCTexture2D* m_pPulleyOnTexture;
	CCTexture2D* m_pPulleyOffTexture;
	CCSprite* m_pLeverSprite;
	CCTexture2D* m_pLeverOnTexture;
	CCTexture2D* m_pLeverOffTexture;
	CCSprite* m_pActiveSprite;

	EDirection m_drStartDirection;
	EDirection m_drCurrentDirection;

	float		m_fStartLength;
	float		m_fCurrentLength;
	float		m_fMoveSpeed;

	CCPoint		m_vStartPosition;
};

