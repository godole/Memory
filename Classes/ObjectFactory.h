#pragma once
#include "cocos2d.h"
#include "Singleton.h"
#include "DataStructure.h"
#include "PhysicsDefine.h"
#include "TransectorProfile.h"
#include <memory>
#include <vector>

USING_NS_CC;
using namespace std;

class CThings;
class CBox;
class CMirage;
class CRail;
class CPulley;
class CGround;
class CSand;
class CWater;

class CObjectFactory :
	public Singleton<CObjectFactory>
{
public :
	shared_ptr<CThings> CreateBox(CCLayer* a_Parent, b2World* a_World, TransectorProfile* a_Profile, BoxData data);
	shared_ptr<CThings> CreateMirage(CCLayer* a_Parent, b2World* a_World, TransectorProfile* a_Profile, MirageData data);
	shared_ptr<CRail> CreateRail(CCLayer* a_Parent, b2World* a_World, TransectorProfile* a_Profile, RailData data);
	shared_ptr<CThings> CreatePulley(CCLayer* a_Parent, b2World* a_World, TransectorProfile* a_Profile, PulleyData data);
	shared_ptr<CGround> CreateGround(CCLayer* a_Parent, b2World* a_World, GroundData data);
	shared_ptr<CSand> CreateSand(CCLayer* a_Parent, b2World* a_World, SandData data);
	shared_ptr<CWater> CreateWater(CCLayer* a_Parent, TransectorProfile* a_Profile, WaterData data);

private :
	void CommonThingsInit(shared_ptr<CThings> obj);
};

