#include "ObjectManager.h"
#include "Box2dSprite.h"


void CObjectManager::Init()
{
	m_arrObject = shared_ptr<CObjectArray<CThings>>(new CObjectArray<CThings>);
	m_arrRail = shared_ptr<CObjectArray<CRail>>(new CObjectArray<CRail>);
	m_arrBox2dSprite = shared_ptr<CObjectArray<CBox2dSprite>>(new CObjectArray < CBox2dSprite>);
}