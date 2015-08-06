#include "ScrollSprite.h"
#include "ScrollManager.h"


CScrollSprite::CScrollSprite()
{
	m_pSprite = nullptr;
}


CScrollSprite::~CScrollSprite()
{
}

void CScrollSprite::Init(CCSprite* a_pSprite)
{ 
	m_pSprite = a_pSprite; 
}

void CScrollSprite::Scroll(Vec2 a_vScrollVelocity)
{
	if (m_pSprite != nullptr)
	{
		m_pSprite->setPosition(m_pSprite->getPosition() + a_vScrollVelocity);
	}
}
