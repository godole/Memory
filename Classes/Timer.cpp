#include "Timer.h"
#include <time.h>
#include "UpdateManager.h"


CTimer::CTimer()
{
	m_lfOldTime = 0;
	m_bIsActive = false;
}


CTimer::~CTimer()
{
}

void CTimer::Update()
{
	if (!m_bIsActive)
		return;

	m_lfNewTime = clock();
}

void CTimer::Start()
{
	m_bIsActive = true;
	//m_lfOldTime = 0;
}

bool CTimer::CompareTime(float a_Time)
{
	m_lfCurrTime = m_lfNewTime - m_lfOldTime;

	if (a_Time <= (m_lfCurrTime / 1000.0))
	{
		m_lfOldTime = m_lfNewTime;
		return true;
	}
	else
		return false;
}