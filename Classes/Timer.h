#pragma once
#include "Update.h"

class CTimer :
	public IUpdate
{
public :	//IUpdate
	virtual void Update();

public:
	CTimer();
	~CTimer();
	
	//단위는 밀리초가 아니라 초
	bool CompareTime(float a_Time);
	void Start();

private :
	long m_lfOldTime;
	long m_lfCurrTime;
	long m_lfNewTime;
	bool m_bIsActive;
};

