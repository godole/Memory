#pragma once
#include "cocos2d.h"
#include "PhysicsDefine.h"
#include "b2Structure.h"
#include <string>

using namespace std;
USING_NS_CC;

class CBox2dSprite
{
public :
	void Init(CCSprite* a_Sprite, b2World* a_World, b2BodyType type, CCPoint a_vAnchor = CCPoint(CCPoint::ANCHOR_MIDDLE));
	void Init(CCSprite* a_Sprite, b2World* a_World, b2BodyType type, float width, float height, CCPoint a_vAnchor = CCPoint(CCPoint::ANCHOR_MIDDLE));
	void Init(CCSprite* a_Sprite, string jsonData, b2World* a_World, b2BodyType type);
	
	CCSprite* getSpritePtr(){ return m_pSprite; }
	b2Structure getBodyStructure(){ return m_b2Structure; }

	void setPositionTo(CCPoint a_vPos);
	void setPositionBy(CCPoint a_vPos);

	CCRect getBoundingBox();

public:
	CBox2dSprite();
	~CBox2dSprite();

private :
	CCSprite* m_pSprite;
	b2Structure m_b2Structure;
	CCPoint m_vAnchorPoint;

	float m_fWidth;
	float m_fHeight;
};

