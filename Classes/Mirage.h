#pragma once
#include "Things.h"
#include "DataStructure.h"
#include "MirageProfile.h"
#include "PhysicsDefine.h"
#include <memory>

using namespace std;
USING_NS_CC;

class CBox2dSprite;

class CMirage :
	public CThings
{

public :
	void		Init(CCLayer* a_pParentLayer, b2World* a_World, MirageData a_Data);
	void		setStateToDefault();

public :
	void		Scroll(Vec2 a_vScrollVelocity);

public:
	CMirage();
	~CMirage();

private :
	void Active(){}
	void DisActive(){}
	
	shared_ptr<CBox2dSprite> m_pWallBodySprite;
	CCTexture2D* m_pGlassCrashedTexture;
	CCTexture2D* m_pGlassTexture;
	CCSprite* m_pWallSprite;
};

