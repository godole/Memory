#pragma once
#include "StageSelectDefine.h"
#include "Update.h"

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
	void StageTouchEnded(Point) { m_isEndedTouch = true; }

	std::shared_ptr<CSelectMapLayer> getSelectMapLayer() { return m_pSelectMapLayer; }

private:
	void VisibleMap(bool);
	void PieceMove(float);
	void PieceAutoMove();
	void PiecePositionScaling();

private:
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
	bool m_isSelectMapTouch;
	bool m_isSelectMapLayer;
};