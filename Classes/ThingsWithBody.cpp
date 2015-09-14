#include "ThingsWithBody.h"
#include "Box2dSprite.h"


CThingsWithBody::CThingsWithBody()
{
}


CThingsWithBody::~CThingsWithBody()
{
}


void CThingsWithBody::setBodyPositionTo(CCPoint a_vPos)
{
	m_pBodySprite->setPositionTo(a_vPos);
}

void CThingsWithBody::setBodyPositionBy(CCPoint a_vPos)
{
	m_pBodySprite->setPositionBy(a_vPos);
}