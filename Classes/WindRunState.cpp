#include "WindRunState.h"
#include "ParticleManager.h"
#include "LayerDefine.h"
#include "ScrollManager.h"


CWindRunState::CWindRunState()
{
}


CWindRunState::~CWindRunState()
{
}

bool CWindRunState::Action(CCPoint a_vPosition)
{
	return false;
}

void CWindRunState::Update()
{

}

void CWindRunState::BehaviorInit()
{
	*(bool*)m_pValueMap->at("bIsRun") = true;
	CCSprite* sprite = (CCSprite*)m_pValueMap->at("sprite");
	auto parent = Director::getInstance()->getRunningScene()->getChildByName(BG_LAYER)->getChildByName("background");
	auto particle = CParticleManager::getInstance()->addParticle(parent, "map/map3/object/air2.plist", ccp(sprite->getBoundingBox().getMinX() - 50, sprite->getBoundingBox().getMaxY() + 5) - CScrollManager::getInstance()->getDeltaPosition());
	m_pValueMap->at("particle") = particle;
}