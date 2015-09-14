#pragma once
#include "cocos2d.h"
#include "Things.h"
#include "DataStructure.h"
#include "TransectorProfile.h"
#include "b2Structure.h"
#include "PhysicsDefine.h"
#include <map>
#include <string>

USING_NS_CC;

class CBox2dSprite;

class CBox :
	public CThings
{

public :
	void Init(CCLayer* a_ParentLayer, b2World* a_World, BoxData a_Data);
	void setStateToDefault() override;
	void Scroll(Vec2 a_vScrollVelocity);

public:
	CBox();
	~CBox();

private :
	void Active() override{}
	void DisActive() override{}

	std::shared_ptr<CBox2dSprite> m_pBodySprite;
	TransectorProfile* m_pTransProfile;
	CCPoint m_vStartPosition;
};

