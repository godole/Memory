#pragma once
#include "StageSelectDefine.h"

class CStageData
{
public:
	CStageData();
	~CStageData();

	void init();

	// �������� Ŭ���� ��ȣ
	void UpdateStageClear(int a_nUpdateStageNumber, int a_nStageNumber);
	void UpdateUserClear(int a_nUpdateClearNumber,int a_nStageNumber);

private:
	void GetStageClearData(int a_nLoadStage);
	void onRequestClearStageData(HttpClient *sender, HttpResponse *response);

	HttpRequest * m_pStageClearRequest;
	std::string m_sSendUrl;

	int m_nStageClearNumber[30];
	int m_nLoadCount;
};

