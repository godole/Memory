#include "StageData.h"


CStageData::CStageData()
{
	m_nLoadCount = 1;
}


CStageData::~CStageData()
{
}

void CStageData::init()
{
	m_pStageClearRequest = new (std::nothrow) HttpRequest();
	m_pStageClearRequest->setRequestType(cocos2d::network::HttpRequest::Type::GET);
	m_pStageClearRequest->setResponseCallback(CC_CALLBACK_2(CStageData::onRequestClearStageData, this));

	GetStageClearData(m_nLoadCount);
}

void CStageData::UpdateStageClear(int a_nUpdateStageNumber ,int a_nStageNumber)
{
	// 스테이지 업데이트
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