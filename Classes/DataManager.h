#pragma once
#include "cocos2d.h"
#include "Singleton.h"
#include "EDirection.h"
#include "DataStructure.h"
#include <vector>
#include <utility>

USING_NS_CC;
using namespace std;



class CDataManager :
	public Singleton<CDataManager>
{
public :
	void				LoadMapData(string filename);
	void				LoadPlayerData();
	void				SavePlayerData(int a_nScore);
	void				LoadNextMapData();
	void				Release();

	vector<BoxData>*	getBoxData(){ return &m_arrBoxData; }
	vector<RailData>*	getRailData(){ return &m_arrRailData; }
	vector<PulleyData>*	getPulleyData(){ return &m_arrPulleyData; }
	vector<GroundData>*	getGroundData(){ return &m_arrGroundData; }
	vector<MirageData>*	getMirageData(){ return &m_arrMirageData; }
	vector<WaterData>*	getWaterData(){ return &m_arrWaterData; }
	vector<SandData>*	getSandData(){ return &m_arrSandData; }
	vector<WindBoxData>* getWindBoxData(){ return &m_arrWindBoxData; }
	vector<PedData>*	getPedData(){ return&m_arrPedData; }
	vector<DoorData>*	getDoorData(){ return &m_arrDoorData; }
	vector<SpannerData>* getSpannerData(){ return &m_arrSpannerData; }
	const BehaviorCount& getMapBehaviorCount(){ return m_MapBehaviorCount; }
	DestinationData*	getDestinationData(){ return &m_DestinationData; }
	string				getBackgroundTextureName(){ return m_szBackgroundTextureName; }
	string				getNextStageFileName(){ return m_szNextStageFileName; }

	void				setCurrentStage(int a_nStage, int a_nMap);

	int					getStageScoreSum(int a_nStage);
	int					getCurrentStageScoreSum(){ return getStageScoreSum(m_CurrentStage.first); }

private :
	vector<BoxData>			m_arrBoxData;
	vector<RailData>		m_arrRailData;
	vector<PulleyData>		m_arrPulleyData;
	vector<GroundData>		m_arrGroundData;
	vector<MirageData>		m_arrMirageData;
	vector<SandData>		m_arrSandData;
	vector<WaterData>		m_arrWaterData;
	vector<PedData>			m_arrPedData;
	vector<WindBoxData>		m_arrWindBoxData;
	vector<DoorData>		m_arrDoorData;
	vector<SpannerData>		m_arrSpannerData;
	DestinationData			m_DestinationData;
	string					m_szBackgroundTextureName;
	string					m_szNextStageFileName;
	PlayerData				m_PlayerData;
	BehaviorCount			m_MapBehaviorCount;

	BoxData					_GetBoxData(string str);
	RailData				_GetRailData(string str);
	PulleyData				_GetPulleyData(string str);
	GroundData				_GetGroundData(string str);
	MirageData				_GetMirageData(string str);
	DestinationData			_GetDestinationData(string str);
	WaterData				_GetWaterData(string str);
	SandData				_GetSandData(string str);
	PedData					_GetPedData(string str);
	WindBoxData				_GetWindBoxData(string str);
	DoorData				_GetDoorData(string str);
	SpannerData				_GetSpannerData(string str);
	BehaviorCount			_GetBehaviorCount(string str);

	string					_GetBackgroundTextureName(string str);
	string					_GetNextSceneFileName(string str);

	pair<int, int>			m_CurrentStage;
};

