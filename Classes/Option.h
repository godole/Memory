#pragma once
#include "StageSelectDefine.h"

enum class ELayerState;
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
	Sprite * m_pAchievement;
	
	bool	 m_isVisible;
	bool	 m_isFading;

	void FadeOptions();
};