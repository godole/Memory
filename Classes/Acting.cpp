#include "Acting.h"
#include "Things.h"
#include "ObjectManager.h"
#include "TransectorProfile.h"
#include "Behavior.h"


CActing::CActing()
{
	m_pCurrentBehavior = nullptr;
	m_nBehaviorCount = 0;

	m_bIsDoing = false;
}

CActing::~CActing()
{
	m_pCurrentBehavior = nullptr;
	m_listBehavior.clear();
	m_listBehaviorIcon.clear();
}

bool CActing::Acting(CCLayer* a_pParentLayer, shared_ptr<Behavior> a_Behavior, CCPoint a_Pos)
{
	if (a_Behavior->Action(a_Pos) && m_nBehaviorCount < 9)
	{
		m_listBehavior.push_back(a_Behavior);
		CreateIcon(a_pParentLayer, a_Behavior->getIconFileName());
		m_nBehaviorCount++;
		if (m_nBehaviorCount > 3)
		{
			RemoveFirstMemory(a_pParentLayer);
		}
		SortIcon();
		return true;
	}

	return false;
}

void CActing::SortIcon()
{
	int i = 0;
	for (auto itr = m_listBehaviorIcon.begin(); itr != m_listBehaviorIcon.end(); itr++, i++)
	{
		(*itr)->setPosition(ccp(120 + 80 * i, 600));
	}
}

void CActing::CreateIcon(CCLayer* a_pParentLayer, string filename)
{
	auto pIcon = CCSprite::create(filename.c_str());
	a_pParentLayer->addChild(pIcon, 3);
	m_listBehaviorIcon.push_back(pIcon);
}

void CActing::RemoveFirstMemory(CCLayer* a_pParentLayer)
{
	auto tempBehavior = m_listBehavior.begin();
	auto tempBehaviorIcon = m_listBehaviorIcon.begin();

	(*tempBehavior)->setStateToDefault();
	m_listBehavior.pop_front();

	a_pParentLayer->removeChild((*tempBehaviorIcon));
	m_listBehaviorIcon.pop_front();
}