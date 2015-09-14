#pragma once
#include <string>
#include "cocos2d.h"
#include "StageSelectDefine.h"

USING_NS_CC;

class CGameData
{
public:
	bool m_isVisible;				// 표시 여부
	int m_nLoadNumber;				// 위치값 조절을 위한 로드 번호
	int m_nAchieveStage;			// 달성 스테이지
	std::string m_nStageMoveCount[STAGE_NUMBER];	
									// 스테이지 별 플레이 시간
	int m_nStageClearNumber[STAGE_NUMBER];
									// 스테이지 별 클리어 번호

	std::string m_sFaceBookID;		// 페이스북 아이디
	std::string m_sName;			// 사용자의 이름

	Sprite * m_pProfileSprite;		// 프로필 이미지
	Label  * m_pFacebookName;		// 페이스북 이름
	Label  * m_pMoveCount;			// 행동 카운트
};