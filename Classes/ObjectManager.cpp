#include "ObjectManager.h"
#include "Box2dSprite.h"


void CObjectManager::Init()
{
	m_arrObject = shared_ptr<CObjectArray<CThings>>(new CObjectArray<CThings>);
	m_arrRail = shared_ptr<CObjectArray<CRail>>(new CObjectArray<CRail>);
	m_arrBox2dSprite = shared_ptr<CObjectArray<CBox2dSprite>>(new CObjectArray < CBox2dSprite>);
	m_arrNotBox = shared_ptr<CObjectArray<CBox2dSprite>>(new CObjectArray < CBox2dSprite>);
	m_arrSand = shared_ptr<CObjectArray<CSand>>(new CObjectArray<CSand>);
	m_arrDoor = shared_ptr<CObjectArray<CDoor>>(new CObjectArray<CDoor>);
}

void CObjectManager::Release()
{
	m_arrObject->Release();
	m_arrRail->Release();
	m_arrBox2dSprite->Release();
	m_arrSand->Release();
	m_arrDoor->Release();
}