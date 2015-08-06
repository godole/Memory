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
	
	//������ �и��ʰ� �ƴ϶� ��
	bool CompareTime(float a_Time);
	void Start();

private :
	long m_lfOldTime;
	long m_lfCurrTime;
	long m_lfNewTime;
	bool m_bIsActive;
};

