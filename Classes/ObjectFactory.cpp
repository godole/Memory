#include "ObjectFactory.h"
#include "DataManager.h"
#include "Things.h"
#include "Box.h"
#include "Pulley.h"
#include "Mirage.h"
#include "Rail.h"
#include "Ground.h"
#include "Sand.h"
#include "Water.h"

shared_ptr<CThings> CObjectFactory::CreateBox(CCLayer* a_Parent, b2World* a_World, TransectorProfile* a_Profile, BoxData data)
{
	shared_ptr<CBox>temp = shared_ptr<CBox>(new CBox);
	temp->setTransectorProfile(a_Profile);
	temp->Init(a_Parent, a_World, data);

	CommonThingsInit(temp);

	return temp;
}

shared_ptr<CThings> CObjectFactory::CreateMirage(CCLayer* a_Parent, b2World* a_World, TransectorProfile* a_Profile, MirageData data)
{
	shared_ptr<CMirage>temp = shared_ptr<CMirage>(new CMirage);
	temp->setTransectorProfile(a_Profile);
	temp->Init(a_Parent, a_World, data);

	CommonThingsInit(temp);

	return temp;
}

shared_ptr<CRail> CObjectFactory::CreateRail(CCLayer* a_Parent, b2World* a_World, TransectorProfile* a_Profile, RailData data)
{
	shared_ptr<CRail>temp = shared_ptr<CRail>(new CRail);
	temp->setTransectorProfile(a_Profile);
	temp->Init(a_Parent, a_World, data);

	CommonThingsInit(temp);

	return temp;
}

shared_ptr<CThings> CObjectFactory::CreatePulley(CCLayer* a_Parent, b2World* a_World, TransectorProfile* a_Profile, PulleyData data)
{
	shared_ptr<CPulley>temp = shared_ptr<CPulley>(new CPulley);
	temp->setTransectorProfile(a_Profile);
	temp->Init(a_Parent, a_World, data);

	CommonThingsInit(temp);

	return temp;
}

void CObjectFactory::CommonThingsInit(shared_ptr<CThings> obj)
{
	CScrollManager::getInstance()->Insert(obj);
	UpdateManager::getInstance()->Insert(obj);
}

shared_ptr<CGround> CObjectFactory::CreateGround(CCLayer* a_Parent, b2World* a_World, GroundData data)
{
	shared_ptr<CGround> temp = shared_ptr<CGround>(new CGround);
	temp->Init(a_Parent, a_World, data);

	CScrollManager::getInstance()->Insert(temp);

	return temp;
}

shared_ptr<CSand> CObjectFactory::CreateSand(CCLayer* a_Parent, b2World* a_World, SandData data)
{
	shared_ptr<CSand> temp = shared_ptr<CSand>(new CSand);
	temp->Init(a_Parent, a_World, data);

	CScrollManager::getInstance()->Insert(temp);

	return temp;
}

shared_ptr<CWater> CObjectFactory::CreateWater(CCLayer* a_Parent, TransectorProfile* a_Profile, WaterData data)
{
	shared_ptr<CWater> temp = shared_ptr<CWater>(new CWater);
	temp->Init(a_Parent, a_Profile, data);

	CommonThingsInit(temp);

	return temp;
}