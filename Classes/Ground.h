#pragma once
#include "Update.h"
#include "cocos2d.h"
#include "IScroll.h"
#include "DataStructure.h"
#include "PhysicsDefine.h"
#include <memory>

USING_NS_CC;

using namespace std;

class CBox2dSprite;

class CGround :
	public IScroll
{
public :
	virtual void	Scroll(Vec2 a_vScrollVelocity) override;

public :
	void Init(CCLayer* a_pParentLayer, b2World* a_World, GroundData a_data);
	void setPositionTo(CCPoint a_Pos);
	void setPositionBy(CCPoint a_Pos);

public:
	CGround();
	~CGround();

private :
	shared_ptr<CBox2dSprite> m_pBodySprite;
};

