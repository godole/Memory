#pragma once
#include "Singleton.h"
#include "ObjectArray.h"
#include "Things.h"
#include "Rail.h"

class CBox2dSprite;

class CObjectManager :
	public Singleton<CObjectManager>
{
public :
	void Init();

	CObjectArray<CThings>* getObjectArray(){ return m_arrObject.get(); }
	CObjectArray<CRail>* getRailArray(){ return m_arrRail.get(); }
	CObjectArray<CBox2dSprite>* getBox2dSprite(){ return m_arrBox2dSprite.get(); }

private:
	shared_ptr<CObjectArray<CThings>> m_arrObject;
	shared_ptr<CObjectArray<CRail>> m_arrRail;
	shared_ptr<CObjectArray<CBox2dSprite>> m_arrBox2dSprite;
};


#define GET_OBJECT_ARRAY CObjectManager::getInstance()->getObjectArray()
#define GET_RAIL_ARRAY CObjectManager::getInstance()->getRailArray()