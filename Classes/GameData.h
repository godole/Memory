#pragma once
#include <string>
#include "cocos2d.h"
#include "StageSelectDefine.h"

USING_NS_CC;

class CGameData
{
public:
	bool m_isVisible;				// ǥ�� ����
	int m_nLoadNumber;				// ��ġ�� ������ ���� �ε� ��ȣ
	int m_nAchieveStage;			// �޼� ��������
	std::string m_nStageMoveCount[STAGE_NUMBER];	
									// �������� �� �÷��� �ð�
	int m_nStageClearNumber[STAGE_NUMBER];
									// �������� �� Ŭ���� ��ȣ

	std::string m_sFaceBookID;		// ���̽��� ���̵�
	std::string m_sName;			// ������� �̸�

	Sprite * m_pProfileSprite;		// ������ �̹���
	Label  * m_pFacebookName;		// ���̽��� �̸�
	Label  * m_pMoveCount;			// �ൿ ī��Ʈ
};