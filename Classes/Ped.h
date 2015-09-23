#pragma once
#include "cocos2d.h"
#include "IScroll.h"
#include "PhysicsDefine.h"
#include "DataStructure.h"
#include <memory>

class CBox2dSprite;

class CPed :
	public IScroll
{ 
public :
	void Init(cocos2d::CCLayer* parentLayer, b2World* world, PedData data);

public :
	virtual void Scroll(cocos2d::Vec2 a_vVelocity);

public:
	CPed();
	~CPed();

private :
	std::shared_ptr<CBox2dSprite> m_pBox2dSprite;
};

