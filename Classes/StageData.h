#pragma once
#include "StageSelectDefine.h"
#include "Singleton.h"

class CGameData;
class CStageData : public Singleton<CStageData>
{
public:
	CStageData();
	~CStageData();

	void init();
	void PushUserData(CGameData * a_pUserData);
	bool getDataLoad() const { return m_isDataLoad; }

	// �������� Ŭ���� ��ȣ
	void UpdateStageClear
		// Ŭ���� ��������		// �÷��� Ÿ��			 // Ŭ���� ��ũ
		(int a_nClearStage, std::string a_sPlayTime, int a_nClearRank);

private:
	void PostHttpRequest();

	void GetStageClearData(int a_nLoadStage);
	void onRequestClearStageData(HttpClient *sender, HttpResponse *response);
	void onRequestSend(HttpClient * sender, HttpResponse * response);

	// Receive Request
	HttpRequest * m_pStageClearRequest;
	
	// Post Request
	HttpRequest * m_pPushRequest;

	CGameData * m_pUserData;
	// ���� Ŭ���� ��ũ
	int m_nUserClearRank[30];

	std::string m_sSendUrl;

	// �������� �ε� ���� init
	bool m_isDataLoad;

	// �������� Ŭ������ ��ȣ
	int m_nStageClearNumber[30];
	int m_nLoadCount;

	// Post Data 

	// �÷��� Ÿ�� ����Ʈ
	bool m_isPlayTimePost;
	// �������� ��ü ��ũ ����Ʈ
	bool m_isStageAllRankPost;
	// ����� Ŭ���� ��ũ ����Ʈ
	bool m_isUserClaerRankPost;
	// ������� �������� Ŭ���� ����
	bool m_isUserClaerStage;
	// ����� ���� ��ũ ���
	bool m_isUserRank;

	int m_nClearStage;
	int m_nClearNumber;
	std::string m_sPlayTime;


};

