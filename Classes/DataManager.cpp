#include "DataManager.h"
#include "json\document.h"
#include "json\prettywriter.h"
#include "json\filestream.h"
#include "json\stringbuffer.h"

using namespace cocos2d;
using namespace rapidjson;

void CDataManager::LoadMapData(string filename)
{
	string fString = filename;
	string szData;
	FileUtils* Utils = FileUtils::sharedFileUtils();

	ssize_t fileSize;
	char* stream = (char*)Utils->getFileData(filename, "r", &fileSize);
	szData = string(stream);

	int nCharIndex = 0;

	for (int i = 0; i < szData.size(); i++)
	{
		if (szData[i] == '\n')
		{
			string temp = szData.substr(i - nCharIndex, nCharIndex);
			if (temp.find("BOX") != std::string::npos)
			{
				m_arrBoxData.push_back(_GetBoxData(temp));
			}

			if (temp.find("RAIL") != std::string::npos)
			{
				m_arrRailData.push_back(_GetRailData(temp));
			}

			if (temp.find("PULLEY") != std::string::npos)
			{
				m_arrPulleyData.push_back(_GetPulleyData(temp));
			}

			if (temp.find("GROUND") != std::string::npos)
			{
				m_arrGroundData.push_back(_GetGroundData(temp));
			}

			if (temp.find("BG") != std::string::npos)
			{
				m_szBackgroundTextureName = _GetBackgroundTextureName(temp);
			}

			if (temp.find("NEXTSTAGE") != string::npos)
			{
				m_szNextStageFileName = _GetNextSceneFileName(temp);
			}

			if (temp.find("DESTINATION") != string::npos)
			{
				m_DestinationData = _GetDestinationData(temp);
			}

			if (temp.find("MIRAGE") != string::npos)
			{
				m_arrMirageData.push_back(_GetMirageData(temp));
			}

			if (temp.find("WATER") != string::npos)
			{
				m_arrWaterData.push_back(_GetWaterData(temp));
			}

			if (temp.find("SAND") != string::npos)
			{
				m_arrSandData.push_back(_GetSandData(temp));
			}

			if (temp.find("WIND") != string::npos)
			{
				m_arrWindBoxData.push_back(_GetWindBoxData(temp));
			}

			if (temp.find("PED") != string::npos)
			{
				m_arrPedData.push_back(_GetPedData(temp));
			}

			if (temp.find("DOOR") != string::npos)
			{
				m_arrDoorData.push_back(_GetDoorData(temp));
			}

			if (temp.find("SPANNER") != string::npos)
			{
				m_arrSpannerData.push_back(_GetSpannerData(temp));
			}

			if (temp.find("BCOUNT") != string::npos)
			{
				m_MapBehaviorCount = _GetBehaviorCount(temp);
			}
			nCharIndex = 0;
		}
		nCharIndex++;
	}

}

void CDataManager::LoadNextMapData()
{
	Release();
	LoadMapData(m_szNextStageFileName);
}

void CDataManager::LoadPlayerData()
{
	FileUtils* Utils = FileUtils::sharedFileUtils();
	string fString = FileUtils::sharedFileUtils()->getWritablePath() + "player_data.json";
	string szData;

	ssize_t fileSize;
	const char* stream = (char*)Utils->getFileData(fString, "rb", &fileSize);

	if (stream == NULL)
		for (int i = 0; i < 3; i++)
			for (int j = 1; j <= 10; ++j)
				m_PlayerData.m_StageCount[i][j] = 0;
	else
	{
		string data = string((const char*)stream, fileSize);
		CC_SAFE_DELETE_ARRAY(stream);

		Document doc;

		if (doc.Parse<0>(data.c_str()).HasParseError())
			CCLOG(doc.GetParseError());
		else
		{
			for (int i = 0; i < 10; ++i)
			{
				m_PlayerData.m_StageCount[0][i + 1] = doc["Stage1"][SizeType(i)].GetInt();
				m_PlayerData.m_StageCount[1][i + 1] = doc["Stage2"][SizeType(i)].GetInt();
				m_PlayerData.m_StageCount[2][i + 1] = doc["Stage3"][SizeType(i)].GetInt();
			}
		}
	}
}

void CDataManager::SavePlayerData(int a_nScore)
{
	m_PlayerData.m_StageCount[m_CurrentStage.first][m_CurrentStage.second] = a_nScore;

	//json 오브젝트 생성
	Document doc;

	doc.SetObject();

	rapidjson::Value stages[] = { (rapidjson::kArrayType), (rapidjson::kArrayType), (rapidjson::kArrayType) };

	for (int i = 0; i < 3; i++)
	{
		for (int j = 1; j <= 10; ++j)
		{
			rapidjson::Value value(rapidjson::kNumberType);
			value.SetInt(m_PlayerData.m_StageCount[i][j]);
			stages[i].PushBack(value, doc.GetAllocator());
		}
	}
	
	doc.AddMember("Stage1", stages[0], doc.GetAllocator());
	doc.AddMember("Stage2", stages[1], doc.GetAllocator());
	doc.AddMember("Stage3", stages[2], doc.GetAllocator());

	//파일 저장
	string path = CCFileUtils::sharedFileUtils()->getWritablePath();
	string filename = path + "player_data.json";

	rapidjson::GenericStringBuffer<UTF8<>> buffer;
	rapidjson::PrettyWriter<rapidjson::GenericStringBuffer<UTF8<>>> writer(buffer);
	doc.Accept(writer);

	CCLOG("%s", buffer.GetString());
	CCLOG("%s", filename.c_str());

	FILE* f = fopen(filename.c_str(), "wb");
	fputs(buffer.GetString(), f);
	fclose(f);
}

void CDataManager::Release()
{
	m_arrBoxData.clear();
	m_arrRailData.clear();
	m_arrPulleyData.clear();
	m_arrGroundData.clear();
	m_arrMirageData.clear();
	m_arrSandData.clear();
	m_arrWaterData.clear();
	m_arrPedData.clear();
	m_arrWindBoxData.clear();
	m_szBackgroundTextureName = "";
}

BoxData	CDataManager::_GetBoxData(string str)
{
	BoxData tempData;
	string tempStr = str;
	string _temp;
	int index = 0;
	int indexCount = 0;

	tempStr.erase(0, 5);

	for (int j = 0; j < tempStr.size(); j++)
	{
		if (tempStr[j] == ' ')
		{
			float x = 0, y = 0;
			_temp = tempStr.substr(j - indexCount, indexCount);

			switch (index)
			{
			case 0 :
				x = atoi(_temp.c_str());
				tempData.m_vStartPosition.x = x;
				break;

			case 1 :
				y = atoi(_temp.c_str());
				tempData.m_vStartPosition.y = y;
				break;
				
			case 2:
				tempData.m_szTextureName = _temp;
				break;
			}
			index++;
			indexCount = 0;
		}

		else
			indexCount++;
	}

	//CCLog("%f, %f", tempData.m_vStartPosition.x, tempData.m_vStartPosition.y);

	return tempData;
}

RailData	CDataManager::_GetRailData(string str)
{
	RailData tempData;
	string tempStr = str;
	string _temp;
	int index = 0;
	int indexCount = 0;

	tempStr.erase(0, 6);

	for (int j = 0; j < tempStr.size(); j++)
	{
		if (tempStr[j] == ' ')
		{
 			_temp = tempStr.substr(j - indexCount, indexCount);

			switch (index)
			{
			case 0:
				tempData.m_vPosition.x = atoi(_temp.c_str());
				break;

			case 1:
				tempData.m_vPosition.y = atoi(_temp.c_str());
				break;

			case 2:
				tempData.m_vLeverPosition.x = atoi(_temp.c_str());
				break;

			case 3 :
				tempData.m_vLeverPosition.y = atoi(_temp.c_str());
				break;

			case 4:
				if (_temp == "LEFT")
					tempData.m_eStartDirection = e_drLeft;

				else if (_temp == "RIGHT")
					tempData.m_eStartDirection = e_drRight;

				break;

			case 5 :
				tempData.m_nRailCount = atoi(_temp.c_str());
				break;

			}
			index++;
			indexCount = 0;
		}

		else
			indexCount++;
	}

	//CCLog("P : %f,%f LP : %f,%f DR : %d", tempData.m_vPosition.x, tempData.m_vPosition.y, tempData.m_vLeverPosition.x, tempData.m_vLeverPosition.y, tempData.m_eStartDirection);

	return tempData;
}

PulleyData	CDataManager::_GetPulleyData(string str)
{
	PulleyData tempData;
	string tempStr = str;
	string _temp;
	int index = 0;
	int indexCount = 0;

	tempStr.erase(0, 8);

	for (int j = 0; j < tempStr.size(); j++)
	{
		if (tempStr[j] == ' ')
		{
			float x = 0, y = 0, length = 0;
			_temp = tempStr.substr(j - indexCount, indexCount);

			switch (index)
			{
			case 0 :
				x = atoi(_temp.c_str());
				tempData.m_vPosition.x = x;
				break;

			case 1 :
				y = atoi(_temp.c_str());
				tempData.m_vPosition.y = y;
				break;

			case 2 :
				x = atoi(_temp.c_str());
				tempData.m_vLeverPosition.x = x;
				break;

			case 3 :
				y = atoi(_temp.c_str());
				tempData.m_vLeverPosition.y = y;
				break;

			case 4 :
				length = atoi(_temp.c_str());
				tempData.m_fLength = length;
				break;

			case 5:
				if (_temp == "UP")
					tempData.m_eStartDirection = e_drUp;

				else if (_temp == "DOWN")
					tempData.m_eStartDirection = e_drDown;

				break; 

			case 6 :
				tempData.m_nPulleyCount = atoi(_temp.c_str());
				break;

			}
			index++;
			indexCount = 0;
		}

		else
			indexCount++;
	}

	//CCLog("P : %f,%f LP : %f,%f LT : %f DR : %d", tempData.m_vPosition.x, tempData.m_vPosition.y, tempData.m_vLeverPosition.x, tempData.m_vLeverPosition.y,tempData.m_fLength, tempData.m_eStartDirection);

	return tempData;
}

GroundData CDataManager::_GetGroundData(string str)
{
	GroundData tempData;
	string tempStr = str;
	string _temp;
	int index = 0;
	int indexCount = 0;

	tempStr.erase(0, 8);

	for (int j = 0; j < tempStr.size(); j++)
	{
		if (tempStr[j] == ' ')
		{
			float x = 0, y = 0;
			_temp = tempStr.substr(j - indexCount, indexCount);

			switch (index)
			{
			case 0 :
				x = atoi(_temp.c_str());
				tempData.m_vPosition.x = x;
				break;

			case 1 :
				y = atoi(_temp.c_str());
				tempData.m_vPosition.y = y;
				break;

			case 2:
				tempData.m_szTextureName = _temp;
				break;
			}
			index++;
			indexCount = 0;
		}

		else
			indexCount++;
	}

	//CCLog("%f, %f, %s", tempData.m_vPosition.x, tempData.m_vPosition.y, tempData.m_szTextureName.c_str());

	return tempData;
}

PedData CDataManager::_GetPedData(string str)
{
	PedData tempData;
	string tempStr = str;
	string _temp;
	int index = 0;
	int indexCount = 0;

	tempStr.erase(0, 5);

	for (int j = 0; j < tempStr.size(); j++)
	{
		if (tempStr[j] == ' ')
		{
			float x = 0, y = 0;
			_temp = tempStr.substr(j - indexCount, indexCount);

			switch (index)
			{
			case 0:
				x = atoi(_temp.c_str());
				tempData.m_vPosition.x = x;
				break;

			case 1:
				y = atoi(_temp.c_str());
				tempData.m_vPosition.y = y;
				break;

			case 2:
				tempData.m_szTextureName = _temp;
				break;
			}
			index++;
			indexCount = 0;
		}

		else
			indexCount++;
	}

	//CCLog("%f, %f, %s", tempData.m_vPosition.x, tempData.m_vPosition.y, tempData.m_szTextureName.c_str());

	return tempData;
}

DestinationData CDataManager::_GetDestinationData(string str)
{
	DestinationData tempData;
	string tempStr = str;
	string _temp;
	int index = 0;
	int indexCount = 0;

	tempStr.erase(0, 13);

	for (int j = 0; j < tempStr.size(); j++)
	{
		if (tempStr[j] == ' ')
		{
			float x = 0, y = 0;
			_temp = tempStr.substr(j - indexCount, indexCount);

			switch (index)
			{
			case 0 :
				x = atoi(_temp.c_str());
				tempData.m_vPosition.x = x;
				break;

			case 1 :
				y = atoi(_temp.c_str());
				tempData.m_vPosition.y = y;
				break;

			case 2:
				tempData.m_szTextureName = _temp;
				break;
			}

			index++;
			indexCount = 0;
		}

		else
			indexCount++;
	}

	//CCLog("%f, %f, %s", tempData.m_vPosition.x, tempData.m_vPosition.y, tempData.m_szTextureName.c_str());

	return tempData;
}

string CDataManager::_GetBackgroundTextureName(string str)
{
	string tempstr = str;

	tempstr.erase(0, 4);
	tempstr.pop_back();
	tempstr.pop_back();

	return tempstr;
}

string CDataManager::_GetNextSceneFileName(string str)
{
	string tempstr = str;

	tempstr.erase(0, 11);
	tempstr.pop_back();
	tempstr.pop_back();

	return tempstr;
}

MirageData CDataManager::_GetMirageData(string str)
{
	MirageData tempData;
	string tempStr = str;
	string _temp;
	int index = 0;
	int indexCount = 0;

	tempStr.erase(0, 8);

	for (int j = 0; j < tempStr.size(); j++)
	{
		if (tempStr[j] == ' ')
		{
			float x = 0, y = 0;
			_temp = tempStr.substr(j - indexCount, indexCount);

			switch (index)
			{
			case 0 :
				x = atoi(_temp.c_str());
				tempData.m_vWallPosition.x = x;
				break;

			case 1 :
				y = atoi(_temp.c_str());
				tempData.m_vWallPosition.y = y;
				break;

			case 2 :
				x = atoi(_temp.c_str());
				tempData.m_vGlassPosition.x = x;
				break;

			case 3 :
				y = atoi(_temp.c_str());
				tempData.m_vGlassPosition.y = y;

				break;
			}
			index++;
			indexCount = 0;
		}

		else
			indexCount++;
	}


	//CCLog("P : %f,%f LP : %f,%f DR : %d", tempData.m_vPosition.x, tempData.m_vPosition.y, tempData.m_vLeverPosition.x, tempData.m_vLeverPosition.y, tempData.m_eStartDirection);

	return tempData;
}

WaterData CDataManager::_GetWaterData(string str)
{
	WaterData tempData;
	string tempStr = str;
	string _temp;
	int index = 0;
	int indexCount = 0;

	tempStr.erase(0, 7);

	for (int j = 0; j < tempStr.size(); j++)
	{
		if (tempStr[j] == ' ')
		{
			float x = 0, y = 0;
			_temp = tempStr.substr(j - indexCount, indexCount);

			switch (index)
			{
			case 0:
				x = atoi(_temp.c_str());
				tempData.m_vPosition.x = x;
				break;

			case 1:
				y = atoi(_temp.c_str());
				tempData.m_vPosition.y = y;
				break;
			}
			index++;
			indexCount = 0;
		}

		else
			indexCount++;
	}

	//CCLog("%f, %f, %s", tempData.m_vPosition.x, tempData.m_vPosition.y, tempData.m_szTextureName.c_str());

	return tempData;
}

SandData CDataManager::_GetSandData(string str)
{
	SandData tempData;
	string tempStr = str;
	string _temp;
	int index = 0;
	int indexCount = 0;

	tempStr.erase(0, 6);

	for (int j = 0; j < tempStr.size(); j++)
	{
		if (tempStr[j] == ' ')
		{
			float x = 0, y = 0;
			_temp = tempStr.substr(j - indexCount, indexCount);

			switch (index)
			{
			case 0:
				x = atoi(_temp.c_str());
				tempData.m_vPosition.x = x;
				break;

			case 1:
				y = atoi(_temp.c_str());
				tempData.m_vPosition.y = y;
				break;
			}
			index++;
			indexCount = 0;
		}

		else
			indexCount++;
	}

	//CCLog("%f, %f, %s", tempData.m_vPosition.x, tempData.m_vPosition.y, tempData.m_szTextureName.c_str());

	return tempData;
}

WindBoxData CDataManager::_GetWindBoxData(string str)
{
	WindBoxData tempData;
	string tempStr = str;
	string _temp;
	int index = 0;
	int indexCount = 0;

	tempStr.erase(0, 6);

	for (int j = 0; j < tempStr.size(); j++)
	{
		if (tempStr[j] == ' ')
		{
			float x = 0, y = 0;
			_temp = tempStr.substr(j - indexCount, indexCount);

			switch (index)
			{
			case 0:
				x = atoi(_temp.c_str());
				tempData.m_vPosition.x = x;
				break;

			case 1:
				y = atoi(_temp.c_str());
				tempData.m_vPosition.y = y;
				break;
			}
			index++;
			indexCount = 0;
		}

		else
			indexCount++;
	}

	return tempData;
}

DoorData CDataManager::_GetDoorData(string str)
{
	DoorData tempData;
	string tempStr = str;
	string _temp;
	int index = 0;
	int indexCount = 0;

	tempStr.erase(0, 6);

	for (int j = 0; j < tempStr.size(); j++)
	{
		if (tempStr[j] == ' ')
		{
			float x = 0, y = 0;
			_temp = tempStr.substr(j - indexCount, indexCount);

			switch (index)
			{
			case 0:
				x = atoi(_temp.c_str());
				tempData.m_vPosition.x = x;
				break;

			case 1:
				y = atoi(_temp.c_str());
				tempData.m_vPosition.y = y;
				break;
			}
			index++;
			indexCount = 0;
		}

		else
			indexCount++;
	}

	//CCLog("%f, %f, %s", tempData.m_vPosition.x, tempData.m_vPosition.y, tempData.m_szTextureName.c_str());

	return tempData;
}

SpannerData CDataManager::_GetSpannerData(string str)
{
	SpannerData tempData;
	string tempStr = str;
	string _temp;
	int index = 0;
	int indexCount = 0;

	tempStr.erase(0, 9);

	for (int j = 0; j < tempStr.size(); j++)
	{
		if (tempStr[j] == ' ')
		{
			float x = 0, y = 0;
			_temp = tempStr.substr(j - indexCount, indexCount);

			switch (index)
			{
			case 0:
				x = atoi(_temp.c_str());
				tempData.m_vPosition.x = x;
				break;

			case 1:
				y = atoi(_temp.c_str());
				tempData.m_vPosition.y = y;
				break;
			}
			index++;
			indexCount = 0;
		}

		else
			indexCount++;
	}

	//CCLog("%f, %f, %s", tempData.m_vPosition.x, tempData.m_vPosition.y, tempData.m_szTextureName.c_str());

	return tempData;
}

BehaviorCount CDataManager::_GetBehaviorCount(string str)
{
	BehaviorCount tempData;
	string tempStr = str;
	string _temp;
	int index = 0;
	int indexCount = 0;

	tempStr.erase(0, 8);

	for (int j = 0; j < tempStr.size(); j++)
	{
		if (tempStr[j] == ' ')
		{
			float x = 0, y = 0;
			_temp = tempStr.substr(j - indexCount, indexCount);

			switch (index)
			{
			case 0:
				tempData.m_nMaxCount = atoi(_temp.c_str());
				break;

			case 1:
				tempData.m_nSecondScore = atoi(_temp.c_str());
				break;

			case 2:
				tempData.m_nFirstScore = atoi(_temp.c_str());
				break;
			}
			index++;
			indexCount = 0;
		}

		else
			indexCount++;
	}

	//CCLog("%f, %f, %s", tempData.m_vPosition.x, tempData.m_vPosition.y, tempData.m_szTextureName.c_str());

	return tempData;
}

void CDataManager::setCurrentStage(int a_nStage, int a_nMap)
{ 
	m_CurrentStage.first = a_nStage;
	m_CurrentStage.second = a_nMap;
}

int	CDataManager::getStageScoreSum(int a_nStage)
{
	int sumScore = 0;

	for (int i = 1; i <= 10; i++)
		sumScore += m_PlayerData.m_StageCount[a_nStage][i];

	return sumScore;
}