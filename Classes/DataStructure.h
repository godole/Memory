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
	string m_szRailLeftTextureName;
	string m_szRailRightTextureName;
	string m_szLeverOnTextureName;
	string m_szLeverOffTextureName;
}RailData;

typedef struct _tagPulleyData
{
	Vec2 m_vPosition;
	Vec2 m_vLeverPosition;
	EDirection m_eStartDirection;
	float m_fLength;
	string m_szPulleyOnTextureName;
	string m_szPulleyOffTextureName;
	string m_szLeverOnTextureName;
	string m_szLeverOffTextureName;
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
	string m_szWallTextureName;
	string m_szGlassTextureName;
	string m_szBrokenTextureName;
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