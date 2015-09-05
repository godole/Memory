#pragma once
#include <string>
#include "cocos2d.h"
#include "Define.h"

USING_NS_CC;

class CGameData
{
public:
	bool m_isVisible;				// ǥ�� ����
	int m_nLoadNumber;				// ��ġ�� ������ ���� �ε� ��ȣ
	int m_nAchieveStage;			// �޼� ��������
	int m_nStageMoveCount[STAGE_NUMBER];	
									// �������� �� �ൿ ī��Ʈ
	std::string m_sFaceBookID;		// ���̽��� ���̵�
	std::string m_sName;			// ������� �̸�

	Sprite * m_pProfileSprite;		// ������ �̹���
	Label  * m_pFacebookName;		// ���̽��� �̸�
};