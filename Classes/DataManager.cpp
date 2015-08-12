#include "DataManager.h"

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

void CDataManager::Release()
{
	m_arrBoxData.clear();
	m_arrRailData.clear();
	m_arrPulleyData.clear();
	m_arrGroundData.clear();
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
				x = atoi(_temp.c_str());
				tempData.m_vLeverPosition.x = x;
				break;

			case 3 :
				y = atoi(_temp.c_str());
				tempData.m_vLeverPosition.y = y;
				break;

			case 4:
				if (_temp == "LEFT")
					tempData.m_eStartDirection = e_drLeft;

				else if (_temp == "RIGHT")
					tempData.m_eStartDirection = e_drRight;

				break;

			case 5:
				tempData.m_szRailLeftTextureName = _temp;
				break;

			case 6:
				tempData.m_szRailRightTextureName = _temp;
				break;

			case 7:
				tempData.m_szLeverOnTextureName = _temp;
				break;

			case 8 :
				tempData.m_szLeverOffTextureName = _temp;
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
				tempData.m_szPulleyOnTextureName = _temp;
				break;

			case 7 :
				tempData.m_szPulleyOffTextureName = _temp;
				break;

			case 8:
				tempData.m_szLeverOnTextureName = _temp;
				break;

			case 9 :
				tempData.m_szLeverOffTextureName = _temp;
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

			case 4 :
				tempData.m_szWallTextureName = _temp;
				break;

			case 5 :
				tempData.m_szGlassTextureName = _temp;
				break;

			case 6 :
				tempData.m_szBrokenTextureName = _temp;
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