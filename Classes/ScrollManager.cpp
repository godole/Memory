#include "ScrollManager.h"
#include "IScroll.h"


CScrollManager::CScrollManager()
{
}


CScrollManager::~CScrollManager()
{
}

void CScrollManager::Insert(shared_ptr<IScroll> a_pScrl)
{
	m_arrScroll.push_back(a_pScrl);
}

void CScrollManager::Scroll(Vec2 a_vDeltaPos)
{
	for (auto itr = m_arrScroll.begin(); itr != m_arrScroll.end(); itr++)
	{
		itr->get()->Scroll(a_vDeltaPos);
	}
	m_vDeltaPosition += a_vDeltaPos;
}

void CScrollManager::Release()
{
	m_arrScroll.clear();
	m_vDeltaPosition = Vec2::ZERO;
}