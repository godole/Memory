#pragma once
#include "Singleton.h"
#include "ObjectArray.h"
#include "Things.h"
#include "Rail.h"
#include "Sand.h"
#include "Door.h"

class CBox2dSprite;

class CObjectManager :
	public Singleton<CObjectManager>
{
public :
	void Init();
	void Release();

	CObjectArray<CThings>* getObjectArray(){ return m_arrObject.get(); }
	CObjectArray<CRail>* getRailArray(){ return m_arrRail.get(); }
	CObjectArray<CBox2dSprite>* getBox2dSprite(){ return m_arrBox2dSprite.get(); }
	CObjectArray<CSand>* getSandArray(){ return m_arrSand.get(); }
	CObjectArray<CDoor>* getDoorArray(){ return m_arrDoor.get(); }

private:
	shared_ptr<CObjectArray<CThings>> m_arrObject;
	shared_ptr<CObjectArray<CRail>> m_arrRail;
	shared_ptr<CObjectArray<CBox2dSprite>> m_arrBox2dSprite;
	shared_ptr<CObjectArray<CSand>> m_arrSand;
	shared_ptr<CObjectArray<CDoor>> m_arrDoor;
};


#define GET_OBJECT_ARRAY CObjectManager::getInstance()->getObjectArray()
#define GET_RAIL_ARRAY CObjectManager::getInstance()->getRailArray()