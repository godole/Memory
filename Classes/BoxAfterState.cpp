#include "BoxAfterState.h"
#include "BoxDefaultState.h"
#include "ParticleManager.h"
#include "LayerDefine.h"
#include "cocos2d.h"
#include "ScrollManager.h"

using namespace cocos2d;

bool CBoxAfterState::Action(Vec2 a_TouchPos)
{
	return false;
}

void CBoxAfterState::Update()
{

}

void CBoxAfterState::BehaviorInit()
{
	m_pBox->m_pBody->SetActive(true);
}