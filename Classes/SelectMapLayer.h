#pragma once
#include "StageSelectDefine.h"

class FriendList;
class CSelectMapLayer
{
public:
	CSelectMapLayer();
	~CSelectMapLayer();

	void init(Layer *);
	void FadeStageMaps(int a_nStageNumber,bool a_bVisible);
	void TouchMap(Point);

	void setVisible(bool);
	bool getVisible() const { return m_isVisible; }

private:
	std::shared_ptr<FriendList> m_pFriendList;
	MenuItemImage * m_pGameStartButton;
	MenuItemImage * m_pCloseButton;

	Sprite * m_pSortClearPeoples;
	Sprite * m_pSortMoveCountPeoples;

	Sprite * m_pStagePuzzle[3][10];

	int m_nNowShowStage;

	bool m_isVisible;
};