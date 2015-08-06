#include "Line.h"
#include "ELineDirection.h"
#include "ConstantValue.h"

CLine::CLine()
{
	m_isComplete = false;
}


CLine::~CLine()
{
}

void CLine::ShowLine()
{
	if (m_isComplete)
		return;

	if (m_rOriginalRect.getMaxY() >= m_rNowRect.getMaxY())
	{
		m_rNowRect.setRect(0, 0,
			m_rNowRect.getMaxX(),
			m_rNowRect.getMaxY() + 10);
	}
	else
	{
		m_isComplete = true;
		m_pLine->setOpacity(255);
	}

	m_pLine->setTextureRect(m_rNowRect);

	if (m_pLine->getOpacity() <= 255)
	{
		if (m_pLine->getOpacity() + 10 >= 255)
		{
			m_pLine->setOpacity(255);
		}
		else
		{
			m_pLine->setOpacity(m_pLine->getOpacity() + 10);
		}
	}
}

void CLine::SetLine()
{
	// Original Rect 조절 값
	m_pLine->setTextureRect(Rect(0, 0, LINE_WEIGHT, m_nHeight));
	m_rOriginalRect = m_pLine->getBoundingBox();

	// 변화값을 주기위해 현재 RECT 를 0으로 초기화
	m_pLine->setTextureRect(Rect(0, 0, LINE_WEIGHT, 0));
	m_rNowRect = m_pLine->getBoundingBox();

	m_pLine->setPosition
		(Point(m_pPosition.x, m_pPosition.y));

	switch (m_eLineDirection)
	{
	case LineDirection::Up:
		m_pLine->setAnchorPoint(Point(0.5, 0));
		break;

	case LineDirection::Down:
		m_pLine->setAnchorPoint(Point(0.5, 1));
		break;

	case LineDirection::Left:
		m_pLine->setRotation(270);
		m_pLine->setAnchorPoint(Point(0.5, 0));
		break;

	case LineDirection::Right:
		m_pLine->setRotation(90);
		m_pLine->setAnchorPoint(Point(0.5, 0));
		break;
	}
}

void CLine::LineInit
	(Layer * a_pParentLayer, LineDirection a_eLineDirection,
	Vec2 a_pPosition, int a_nHeight)
{
	m_nHeight			= a_nHeight;
	m_eLineDirection	= a_eLineDirection;
	m_pPosition			= a_pPosition;

	m_pLine = Sprite::create("stageselect/gamemenu_bar.png");
	m_pLine->setOpacity(0);
	a_pParentLayer->addChild(m_pLine);

	SetLine();
}