#pragma once
#include "cocos2d.h"
#include "DataStructure.h"
#include "PhysicsDefine.h"
#include "IScroll.h"
#include <memory>

USING_NS_CC;
using namespace std;

class CBox2dSprite;

class CSand :
	public IScroll
{
public :
	virtual void Scroll(Vec2 a_vVelocity);

public :
	void Init(CCNode* a_pParent, b2World* a_world, SandData a_data);
	void On();
	void Off();

	CCSprite* getSpritePtr(){ return m_pSprite; }

public:
	CSand();
	~CSand();

private :
	CCSprite* m_pSprite;
	CCTexture2D* m_pOnTexture;
	CCTexture2D* m_pOffTexture;
	shared_ptr<CBox2dSprite> m_pBox2dSprite;
};

