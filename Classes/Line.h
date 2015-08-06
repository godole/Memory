#pragma once
#include "cocos2d.h"
USING_NS_CC;

enum class LineDirection;
class CLine
{
public:
	CLine();
	~CLine();

public:
	void ShowLine();
	
	void LineInit(Layer* a_pParentLayer, LineDirection a_eLineDirection,
		Vec2 a_pPosition,int a_nHeight);
	void setWork(bool a_isWork) { m_isWork = a_isWork; }
	bool getCompleteVisible() const { return m_isComplete; }

private:
	void SetLine();

private:
	LineDirection	m_eLineDirection;
	Sprite *		m_pLine;
	Rect			m_rOriginalRect;
	Rect			m_rNowRect;
	Vec2			m_pPosition;

	int				m_nHeight;

	bool			m_isWork;
	bool			m_isComplete;
};