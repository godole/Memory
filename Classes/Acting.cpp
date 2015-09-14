#include "Acting.h"
#include "Things.h"
#include "ObjectManager.h"
#include "TransectorProfile.h"
#include "ParticleManager.h"
#include "Behavior.h"


CActing::CActing(int a_nMaxCount) :
m_nMaxBehaviorCount(a_nMaxCount)
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

void CActing::Init(CCLayer* a_pParentLayer)
{
	m_pParentLayer = a_pParentLayer;
}

bool CActing::Acting(shared_ptr<Behavior> a_Behavior, CCPoint a_Pos)
{
	if (m_nBehaviorCount > m_nMaxBehaviorCount && !Behavior::k_bIsDoing)
		return false;

	if (a_Behavior->Action(a_Pos))
	{
		m_listBehavior.push_back(a_Behavior);
		CreateIcon(a_Behavior->getIconFileName());
		m_nBehaviorCount++;
		if (m_nBehaviorCount > 3)
		{
			RemoveFirstMemory();
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
		(*itr)->runAction(CCSequence::create((CCFiniteTimeAction*)
			CCDelayTime::create(1.0), 
			CCMoveTo::create(0.5, ccp(170 + 85 * i, 650)), 
			NULL));
	}
}

void CActing::CreateIcon(string filename)
{
	auto pIcon = CCSprite::create(filename.c_str());
	pIcon->setPosition(ccp(150 + 80 * 3, 650));
	//CParticleManager::getInstance()->addParticle(pIcon, "ui/add_icon.plist", ccp(pIcon->getContentSize().width / 2, pIcon->getContentSize().height / 2),1);
	m_pParentLayer->addChild(pIcon, 3);
	m_listBehaviorIcon.push_back(pIcon);
}

void CActing::RemoveFirstMemory()
{
	auto tempBehavior = m_listBehavior.begin();
	auto tempBehaviorIcon = m_listBehaviorIcon.begin();

	(*tempBehavior)->setStateToDefault();
	m_listBehavior.pop_front();

	m_pParentLayer->removeChild((*tempBehaviorIcon));
	m_listBehaviorIcon.pop_front();
}

void CActing::RemoveAllMemory()
{
	auto arr = CObjectManager::getInstance()->getObjectArray()->getObjectArray();
	for (auto itr = arr.begin(); itr != arr.end(); itr++)
	{
		(*itr)->setStateToDefault();
	}
	m_listBehavior.clear();

	for (auto itr = m_listBehaviorIcon.begin(); itr != m_listBehaviorIcon.end(); itr++)
	{
		m_pParentLayer->removeChild((*itr));
	}
	m_listBehaviorIcon.clear();
}

void CActing::setStateToDefault()
{
	RemoveAllMemory();
	m_nBehaviorCount = 0;
	m_bIsDoing = false;
}