#include "ParticleManager.h"


CCParticleSystemQuad* CParticleManager::addParticle(CCNode* a_pLayer, string plistName, CCPoint a_Pos, int ZOrder)
{
	auto particle = ParticleSystemQuad::create(plistName);
	particle->setPosition(a_Pos);
	a_pLayer->addChild(particle, ZOrder);

	particle->setPositionType(tPositionType::RELATIVE);

	return particle;
}

void CParticleManager::addParticle(CCNode* a_pLayer, string plistName, CCPoint a_Pos, string childTag, int ZOrder)
{
	auto particle = ParticleSystemQuad::create(plistName);
	particle->setPosition(a_Pos);
	a_pLayer->addChild(particle, ZOrder, childTag);

	particle->setPositionType(tPositionType::RELATIVE);
}