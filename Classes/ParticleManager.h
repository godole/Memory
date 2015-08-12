#pragma once
#include "cocos2d.h"
#include "Singleton.h"
#include <string>

USING_NS_CC;
using namespace std;

class CParticleManager :
	public Singleton<CParticleManager>
{
public:
	void addParticle(CCNode* a_pLayer, string plistName, CCPoint a_Pos, int ZOrder = 0);
};

