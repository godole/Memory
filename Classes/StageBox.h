#pragma once
#include "cocos2d.h"
#include "Update.h"

USING_NS_CC;

class CSelectMapLayer;
class CStageBox : 
	public IUpdate
{
public:
	CStageBox();
	~CStageBox();

	void init(Layer *);
	void Update() override;

	void StageTouchBegan(Point);
	void StageTouchMoved(Point);
	void StageTouchEnded(Point);
private:
	void VisibleMap(bool);
	void PieceMove(float);
	void PieceAutoMove();
	void PiecePositionScaling();

	// 
	std::shared_ptr<CSelectMapLayer> m_pSelectMapLayer;
	Layer * m_pStageBoxLayer;

	// BOX STAGE - LEFT - RIGHT - DOWN
	Sprite * m_pBoxPiece[3][3];
	EaseInOut  * m_pPieceMove[3];
	Sequence * m_pPieceDownAction;

	MenuItemImage * m_pBackStageMain;

	Point m_ptBeganTouchPosition;

	//
	int  m_nNowStageNumber;
	int  m_nPieceAutoMoving;

	bool m_isCanTouch;
	bool m_isEndedTouch;
	bool m_isSelectMapLayer;

};