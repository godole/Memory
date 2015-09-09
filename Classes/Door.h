#pragma once
#include "Things.h"
#include "cocos2d.h"
#include "PhysicsDefine.h"
#include "DataStructure.h"
#include "IScroll.h"
#include "Update.h"
#include <memory>

class CBox2dSprite;
	  
class CDoor :
	public IScroll,
	public IUpdate
{
public:
	void Init(cocos2d::CCLayer* parentLayer, b2World* world, DoorData data);

	cocos2d::CCSprite* getSpritePtr(){ return m_pFrameSprite; }
	void On();
	void Off();

public :
	void Scroll(cocos2d::Vec2 a_vVelocity);

public :
	virtual void Update() override;

public:
	CDoor();
	~CDoor();

private :
	cocos2d::CCSprite* m_pFrameSprite;
	std::shared_ptr<CBox2dSprite> m_pLeftDoorSprite;
	std::shared_ptr<CBox2dSprite> m_pRightDoorSprite;

	bool m_bIsOpened;
};

