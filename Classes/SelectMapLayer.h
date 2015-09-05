#pragma once
#include "cocos2d.h"
#include <memory>
USING_NS_CC;

class FriendList;
class CSelectMapLayer
{
public:
	CSelectMapLayer();
	~CSelectMapLayer();

	void init(Layer *);
	void FadeStageMaps(int a_nStageNumber,bool a_bVisible);
	void TouchMap(Point);

	bool getVisible() const { return m_isVisible; }

private:
	std::shared_ptr<FriendList> m_pFriendList;
	Sprite * m_pStagePuzzle[3][10];

	int m_nNowShowStage;
	bool m_isVisible;
};