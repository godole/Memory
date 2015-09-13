#pragma once
#include "cocos2d.h"
#include "EDirection.h"

typedef struct PulleyProfile
{
	EDirection m_drStartDirection;
	EDirection m_drCurrentDirection;

	float		m_fStartLength;
	float		m_fCurrentLength;
	float		m_fMoveSpeed;

	cocos2d::CCPoint	m_vStartPosition;
};