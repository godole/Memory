#include "Things.h"
#include "Behavior.h"
#include "Box2dSprite.h"


CThings::CThings()
{
	m_bIsRanged = true;
}


CThings::~CThings()
{
}

bool CThings::Action(CCPoint a_vPos)
{
	return m_pBehavior->Action(a_vPos);
}

void CThings::Update()
{
	m_pBehavior->Update();
	if (m_pTransectorProfile->m_TransectRange.containsPoint(m_pActionSprite->getPosition()))
	{
		m_bIsRanged = true;
		Active();
	}
	else
	{
		m_bIsRanged = false;
		DisActive();
	}

	ObjectUpdate();
}

void CThings::ChangeState(shared_ptr<Behavior> a_Ptr)
{
	m_pBehavior = a_Ptr;
	a_Ptr->Init(this, &m_ValueMap);
}