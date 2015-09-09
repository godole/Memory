#include "WindDefaultState.h"
#include "WindRunState.h"
#include "WindBox.h"
#include "LayerDefine.h"


CWindDefaultState::CWindDefaultState()
{
}


CWindDefaultState::~CWindDefaultState()
{
}

bool CWindDefaultState::Action(CCPoint a_vPosition)
{
	CCSprite* sprite = (CCSprite*)m_pValueMap->at("sprite");

	if (sprite->getBoundingBox().containsPoint(a_vPosition))
	{
		m_pThings->ChangeState(shared_ptr<CWindRunState>(new CWindRunState));
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
	*(bool*)m_pValueMap->at("bIsRun") = false;
	if (m_pValueMap->at("particle") != nullptr)
	{
		auto particle = (CCParticleSystemQuad*)m_pValueMap->at("particle");
		particle->stopSystem();
	}
}