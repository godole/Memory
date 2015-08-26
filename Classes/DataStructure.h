#pragma once
#include "cocos2d.h"
#include "EDirection.h"


USING_NS_CC;
using namespace std;

typedef struct _tagBoxData
{
	Vec2 m_vStartPosition;
	string m_szTextureName;
}BoxData;

typedef struct _tagRailData
{
	Vec2 m_vPosition;
	Vec2 m_vLeverPosition;
	EDirection m_eStartDirection;
	int m_nRailCount;
}RailData;

typedef struct _tagPulleyData
{
	Vec2 m_vPosition;
	Vec2 m_vLeverPosition;
	EDirection m_eStartDirection;
	float m_fLength;
	int m_nPulleyCount;
}PulleyData;

typedef struct _tagGroundData
{
	Vec2 m_vPosition;
	string m_szTextureName;
}GroundData;

typedef struct _tagMirageData
{
	Vec2 m_vWallPosition;
	Vec2 m_vGlassPosition;
}MirageData;

typedef struct _tagObjectData
{
	Vec2 m_vPosition;
	string m_szTextureName;
}ObjectData;

typedef struct _tagDestination
{
	Vec2 m_vPosition;
	string m_szTextureName;
}DestinationData;

typedef struct _tagWater
{
	Vec2 m_vPosition;
}WaterData;

typedef struct _tagSand
{
	Vec2 m_vPosition; 
}SandData;

typedef struct _tagPlayerData
{
	string m_szName;
	int m_nStage1Count;
	int m_nStage2Count;
	int m_nStage3Count;
}PlayerData;

typedef struct _tagWindBoxData
{
	CCPoint m_vPosition;
}WindBoxData;

typedef struct _tagPedData
{
	CCPoint m_vPosition;
	string m_szTextureName;
}PedData;