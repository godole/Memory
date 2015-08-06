#pragma once
#include "cocos2d.h"
USING_NS_CC;

class CStageBox
{
public:
	CStageBox();
	~CStageBox();

	void init(Layer *);
	void touch(Point);

	// 績獣 けいしけい
	Layer * m_pPiece;
	Layer * m_pStages;

	Sprite * m_pPieceLeft;
	Sprite * m_pPieceRight;
	Sprite * m_pPieceDown;

	Sprite * m_pStage[10];

	int m_nStageNum;
	bool m_isCheck;
	bool m_isVisible;
	bool m_isTouch;

};

