#include "RailBehaviorStates.h"
#include "Things.h"
#include <memory>

using namespace std;

void CRailBehaviorState::setStateToDefault()
{
	m_pObject->ChangeState(shared_ptr<CRailDefaultState>(new CRailDefaultState));
}

void CRailBehaviorState::Init(CThings* a_pObject, std::map<string, void* >* a_pValueMap)
{
	m_pObject = a_pObject;
	m_pValueMap = a_pValueMap;

	m_pLeverSprite = _VMAP_STATIC_CAST(CCSprite*, "leverSprite");
	m_parPed = _VMAP_STATIC_CAST(vector<shared_ptr<CBox2dSprite>>*, "arrPed");
	m_pData = _VMAP_STATIC_CAST(RailProfile*, "railProfile");

	BehaviorInit();
}


bool CRailDefaultState::Action(CCPoint a_Pos)
{
	if (m_pLeverSprite->getBoundingBox().containsPoint(a_Pos) &&
		!k_bIsDoing &&
		m_pObject->getIsRanged())
	{
		m_pObject->ChangeState(shared_ptr<CRailRunState>(new CRailRunState));
		return true;
	}
	else
		return false;
}

void CRailDefaultState::BehaviorInit()
{
	m_pData->m_eCurrentDirection = m_pData->m_eStartDirection;
	m_pLeverSprite->setTexture(_VMAP_STATIC_CAST(CCTexture2D*, "leverOffTexture"));

	for (int i = 0; i < m_parPed->size(); i++)
	{
		auto sprite = m_parPed->at(i)->getSpritePtr();
		if (m_pData->m_eStartDirection == EDirection::e_drLeft)
			sprite->setTexture(_VMAP_STATIC_CAST(CCTexture2D*, "pedLeftTexture"));

		if (m_pData->m_eStartDirection == EDirection::e_drRight)
			sprite->setTexture(_VMAP_STATIC_CAST(CCTexture2D*, "pedRightTexture"));
	}
}



bool CRailRunState::Action(CCPoint a_Pos)
{
	return false;
}

void CRailRunState::BehaviorInit()
{
	if (m_pData->m_eCurrentDirection == EDirection::e_drLeft)
	{
		m_pData->m_eCurrentDirection = EDirection::e_drRight;
		for (int i = 0; i < m_parPed->size(); i++)
		{
			auto sprite = (*m_parPed)[i]->getSpritePtr();
			sprite->setTexture(_VMAP_STATIC_CAST(CCTexture2D*, "pedRightTexture"));
		}
	}

	else if (m_pData->m_eCurrentDirection == EDirection::e_drRight)
	{
		m_pData->m_eCurrentDirection = EDirection::e_drLeft;
		for (int i = 0; i < m_parPed->size(); i++)
		{
			auto sprite = (*m_parPed)[i]->getSpritePtr();
			sprite->setTexture(_VMAP_STATIC_CAST(CCTexture2D*, "pedLeftTexture"));
		}
	}

	m_pLeverSprite->setTexture(_VMAP_STATIC_CAST(CCTexture2D*, "leverOnTexture"));
}