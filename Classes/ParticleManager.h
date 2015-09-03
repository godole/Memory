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
	CCParticleSystemQuad* addParticle(CCNode* a_pLayer, string plistName, CCPoint a_Pos, int ZOrder = 0);
	void addParticle(CCNode* a_pLayer, string plistName, CCPoint a_Pos, string childTag, int ZOrder = 0);
};

