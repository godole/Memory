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

	// 스테이지 클리어 번호
	void UpdateStageClear
		// 클리어 스테이지		// 플레이 타임			 // 클리어 랭크
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
	// 유저 클리어 랭크
	int m_nUserClearRank[30];

	std::string m_sSendUrl;

	// 데이터의 로드 여부 init
	bool m_isDataLoad;

	// 스테이지 클리어한 번호
	int m_nStageClearNumber[30];
	int m_nLoadCount;

	// Post Data 

	// 플레이 타임 포스트
	bool m_isPlayTimePost;
	// 스테이지 전체 랭크 포스트
	bool m_isStageAllRankPost;
	// 사용자 클리어 랭크 포스트
	bool m_isUserClaerRankPost;
	// 사용자의 스테이지 클리어 갱신
	bool m_isUserClaerStage;
	// 사용자 개인 랭크 등록
	bool m_isUserRank;

	int m_nClearStage;
	int m_nClearNumber;
	std::string m_sPlayTime;


};

