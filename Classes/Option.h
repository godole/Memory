#pragma once
#include "cocos2d.h"
#include "ELayerState.h"

USING_NS_CC;

class COption
{
public:
	COption();
	~COption();

	void init(Layer *);
	void TouchBegan(Point);
	ELayerState getLayerState() const { return m_eLayerState; }

private:
	ELayerState m_eLayerState;
	Sprite * m_pMain;
	
	Sprite * m_pStageSelect;
	Sprite * m_pOption;
	
	bool	 m_isVisible;
	bool	 m_isFading;

	void FadingOptions();
};

