#pragma once
#include "cocos2d.h"
#include "IScroll.h"

USING_NS_CC;

class CScrollSprite :
	public IScroll
{
public :
	void	Scroll(Vec2 a_vScrollVelocity) override;

public :
	void		Init(CCSprite* a_pSprite);
	CCSprite*	getSpritePtr(){ return m_pSprite; }

public:
	CScrollSprite();
	~CScrollSprite();

private :
	CCSprite* m_pSprite;
};

