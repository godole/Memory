#include "StageData.h"
#include "GameData.h"

CStageData::CStageData()
{
	m_nLoadCount = 1;
	m_isDataLoad = false;
}


CStageData::~CStageData()
{
}

void CStageData::init()
{
	m_isDataLoad = true;

	m_pStageClearRequest = new (std::nothrow) HttpRequest();
	m_pStageClearRequest->setRequestType(cocos2d::network::HttpRequest::Type::GET);
	m_pStageClearRequest->setResponseCallback(CC_CALLBACK_2(CStageData::onRequestClearStageData, this));

	m_pPushRequest = new (std::nothrow) HttpRequest();
	m_pPushRequest->setRequestType(cocos2d::network::HttpRequest::Type::GET);
	m_pPushRequest->setResponseCallback(CC_CALLBACK_2(CStageData::onRequestSend, this));

	GetStageClearData(m_nLoadCount);
}

void CStageData::PushUserData(CGameData * a_pUserData)
{
	m_pUserData = a_pUserData;
}

void CStageData::UpdateStageClear
	(int a_nClearStage, std::string a_sPlayTime, int a_nClearNumber)
{
	m_nClearStage	= a_nClearStage;
	m_sPlayTime		= a_sPlayTime;
	m_nClearNumber  = a_nClearNumber;

	PostHttpRequest();
}

void CStageData::PostHttpRequest()
{
	std::string _PostData;

	if (m_isPlayTimePost)
	{
		for (int i = 0; i < 30; i++)
		{
			if (m_nClearNumber == i)
				_PostData += m_sPlayTime;
			else 
				_PostData += m_pUserData->m_nStageMoveCount[i];
		}

		m_sSendUrl =
			"http://www.anioneguild.com/Memory/UpdateStagePlayTime.php?ID=" + m_pUserData->m_sFaceBookID
			+ "&Stage=" + _PostData;
		m_isPlayTimePost = false;
	}
	else if (m_isStageAllRankPost)
	{
		m_nStageClearNumber[m_nClearStage] = m_nStageClearNumber[m_nClearStage] + 1;
		for (int i = 0; i < 10; i++)
		{
			_PostData += m_nStageClearNumber[ ( m_nClearStage / 10 ) * 10 + i];
			if (i <9)
				_PostData += ", ";
		}

		m_sSendUrl =
			"http://www.anioneguild.com/Memory/UpdateStageClear.php?StageNumber=" + 
			StringUtils::format("%d",m_nClearStage / 10) 
			+ "&StageValue=" + _PostData;

		m_isStageAllRankPost = false;
	}
	else if (m_isUserClaerStage)
	{
		_PostData = m_pUserData->m_nAchieveStage = m_nClearStage;
		m_sSendUrl =
			"http://www.anioneguild.com/Memory/UpdateUserData.php?ID=" + m_pUserData->m_sFaceBookID
			+ "&Stage=" + _PostData;

		m_isUserClaerRankPost = false;
	}
	else if (m_isUserRank)
	{
		for (int i = 0; i < 30; i++)
		{
			if (i == m_nClearStage)
				_PostData = m_nStageClearNumber[m_nClearStage];
			else
				_PostData = m_pUserData->m_nStageClearNumber[i];

				_PostData += ", ";
		}

		m_sSendUrl =
			"http://www.anioneguild.com/Memory/UpdateUserClearNumber.php?ID=" + m_pUserData->m_sFaceBookID
			+ "&Stage=" + _PostData;

		m_isUserRank = false;
	}
	else
	{
		return;
	}

	HTTPREQUEST_SEND(m_pPushRequest, m_sSendUrl);
}

void CStageData::GetStageClearData(int a_nLoadStage)
{
	m_sSendUrl = "http://www.anioneguild.com/Memory/GetStageClearNumber.php?StageNumber=" + StringUtils::format("%d",a_nLoadStage);
	HTTPREQUEST_SEND(m_pStageClearRequest, m_sSendUrl);
}

void CStageData::onRequestClearStageData(HttpClient *sender, HttpResponse *response)
{
	if (!response || !response->isSucceed())
	{
		CDataManager::getInstance()->m_bConnectFacebook = false;
		return;
	}

	std::vector<char> *buffer = response->getResponseData();
	std::string _receiveMsg = buffer->data();
	int _nCheckPoint;

	for (int i = 0; i < 10; i++)
	{
		_nCheckPoint = _receiveMsg.find(",");
		m_nStageClearNumber[(m_nLoadCount - 1) * 10 + i] = atoi(_receiveMsg.substr(0, _nCheckPoint).c_str());

		_receiveMsg.erase(0, _nCheckPoint + 2);
	}

	m_nLoadCount++;

	if (m_nLoadCount < 4)
		GetStageClearData(m_nLoadCount);
}

void CStageData::onRequestSend(HttpClient *sender, HttpResponse *response)
{
	if (!response || !response->isSucceed())
	{
		CDataManager::getInstance()->m_bConnectFacebook = false;
		return;
	}

	std::vector<char> *buffer = response->getResponseData();
	std::string _receiveMsg = buffer->data();

	PostHttpRequest();
}