#include "WindBehaviorStates.h"
#include "Things.h"
#include "LayerDefine.h"
#include "ParticleManager.h"

using namespace std;
using namespace cocos2d;


CWindBehaviorState::CWindBehaviorState()
{
}


CWindBehaviorState::~CWindBehaviorState()
{
}

void CWindBehaviorState::Init(CThings* a_pObject, std::map<string, void* >* a_pValueMap)
{
	m_pObject = a_pObject;
	m_pValueMap = a_pValueMap;

	m_pSprite = _VMAP_STATIC_CAST(CCSprite*, "sprite");
	m_pbIsRun = _VMAP_STATIC_CAST(bool*, "bIsRun");
	m_pParticle = _VMAP_STATIC_CAST(CCParticleSystemQuad*, "particle");

	BehaviorInit();
}

void CWindBehaviorState::setStateToDefault()
{
	m_pObject->ChangeState(shared_ptr<CWindBehaviorState>(new CWindDefaultState));
}




CWindDefaultState::CWindDefaultState()
{
}


CWindDefaultState::~CWindDefaultState()
{
}

bool CWindDefaultState::Action(CCPoint a_vPosition)
{
	if (m_pSprite->getBoundingBox().containsPoint(a_vPosition))
	{
		m_pObject->ChangeState(shared_ptr<CWindRunState>(new CWindRunState));
		return true;
	}
	else
		return false;
}

void CWindDefaultState::Update()
{

}

void CWindDefaultState::BehaviorInit()
{
	*m_pbIsRun = false;

	if (m_pParticle != nullptr)
		m_pParticle->stopSystem();
}



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
	*m_pbIsRun = false;
	auto parent = Director::getInstance()->getRunningScene()->getChildByTag(MAIN_LAYER)->getChildByTag(CHAR_PARTICLE_NODE);
	auto particle = CParticleManager::getInstance()->addParticle(parent, "map/map1/object/air2.plist", ccp(m_pSprite->getBoundingBox().getMidX(), m_pSprite->getBoundingBox().getMaxY() + 5) - CScrollManager::getInstance()->getDeltaPosition());
	(*m_pValueMap)["particle"] = particle;
}