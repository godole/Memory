#include "StageBox.h"
#include "SelectMapLayer.h"

CStageBox::CStageBox()
{
	m_isSelectMapLayer = false;
	m_isEndedTouch = true;
	m_isCanTouch = true;
	m_nNowStageNumber = 1;
	m_nPieceAutoMoving = 1;
}


CStageBox::~CStageBox()
{
}

void CStageBox::init(Layer * a_pParentLayer)
{
	m_pStageBoxLayer = Layer::create();
	a_pParentLayer->addChild(m_pStageBoxLayer);

	//// Select Map Layer
	m_pSelectMapLayer = std::shared_ptr<CSelectMapLayer>(new CSelectMapLayer);
	m_pSelectMapLayer->init(m_pStageBoxLayer);

	//// Map Piece
	for (int i = 0; i < 3; i++)
	{
		m_pBoxPiece[i][0] = Sprite::create("stageselect/piece_left.png");
		m_pBoxPiece[i][1] = Sprite::create("stageselect/piece_right.png");
		m_pBoxPiece[i][2] = Sprite::create("stageselect/piece_down.png");

		m_pBoxPiece[i][0]->setAnchorPoint(Point(1, 0));
		m_pBoxPiece[i][1]->setAnchorPoint(Point(0, 0));
		m_pBoxPiece[i][2]->setAnchorPoint(Point(0.5, 1));

		m_pBoxPiece[i][0]->setPosition(Point(185 + i * 450, 210));
		m_pBoxPiece[i][1]->setPosition(Point(195 + i * 450, 210));

		if (i != 1)
			m_pBoxPiece[i][2]->setPosition(Point(190 + i * 450, 275));
		else
			m_pBoxPiece[i][2]->setPosition(Point(190 + i * 450, 340));

		for (int k = 0; k < 3; k++)
		{
			m_pStageBoxLayer->addChild(m_pBoxPiece[i][k]);
		}
	}

	for (int k = 0; k < 3; k++)
	{
		m_pBoxPiece[0][k]->setScale(0.5);
		m_pBoxPiece[2][k]->setScale(0.5);
	}

	// BackStageMain
	m_pBackStageMain = MenuItemImage::create(
		"a.png",
		"b.png",
		std::bind([=]{
		VisibleMap(false);
	}));

	m_pBackStageMain->setVisible(false);
	m_pBackStageMain->setScale(2.0f);
	m_pBackStageMain->setPosition(Point(50, 50));

	auto _pButton = Menu::create(m_pBackStageMain, NULL);
	_pButton->setPosition(Vec2::ZERO);
	m_pStageBoxLayer->addChild(_pButton);

}

void CStageBox::PiecePositionScaling()
{
	float Stage[3];
	Stage[0] = m_pBoxPiece[0][0]->getPositionX() - 185;
	Stage[1] = fabsf(m_pBoxPiece[1][0]->getPositionX() - 635);
	Stage[2] = -(m_pBoxPiece[2][0]->getPositionX() - 1085);

	// Piece Move & Scale
	for (int k = 0; k < 3; k++)
	{
		m_pBoxPiece[0][k]->setScale(0.5 +
			0.00111111111 * Stage[0]);

		m_pBoxPiece[1][k]->setScale(1.0 -
			0.00111111111 * Stage[1]);

		m_pBoxPiece[2][k]->setScale(0.5 +
			0.00111111111 * Stage[2]);
	}

	m_pBoxPiece[0][2]->setPositionY(275 +
		0.1444444444 * Stage[0]);

	m_pBoxPiece[1][2]->setPositionY(340 -
		0.1444444444 * Stage[1]);

	m_pBoxPiece[2][2]->setPositionY(275 +
		0.1444444444 * Stage[2]);
}

void CStageBox::PieceAutoMove()
{
	float  CheckPositionX[3];

	CheckPositionX[0] = fabsf(635 - m_pBoxPiece[0][0]->getPositionX());
	CheckPositionX[1] = fabsf(635 - m_pBoxPiece[1][0]->getPositionX());
	CheckPositionX[2] = fabsf(635 - m_pBoxPiece[2][0]->getPositionX());

	if (CheckPositionX[0] < CheckPositionX[1])
	{
		if (CheckPositionX[0] < CheckPositionX[2])
			m_nNowStageNumber = 0;
		else
			m_nNowStageNumber = 2;
	}
	else
	{
		if (CheckPositionX[1] < CheckPositionX[2])
			m_nNowStageNumber = 1;
		else
			m_nNowStageNumber = 2;
	}

	switch (m_nNowStageNumber)
	{
	case 0:
		if (m_pBoxPiece[0][0]->getPositionX() < 635)
		{
			m_isCanTouch = false;
			PieceMove(5);
		}
		else
		{
			m_isCanTouch = true;
		}
		break;
	case 1:
		if (m_pBoxPiece[1][0]->getPositionX() < 635)
		{
			m_isCanTouch = false;
			PieceMove(5);
		}
		else if (m_pBoxPiece[1][0]->getPositionX() > 635)
		{
			m_isCanTouch = false;
			PieceMove(-5);
		}
		else
		{
			m_isCanTouch = true;
		}

		break;
	case 2:
		if (m_pBoxPiece[2][0]->getPositionX() > 635)
		{
			PieceMove(-5);
			m_isCanTouch = false;
		}
		else
		{
			m_isCanTouch = true;
		}
		break;
	default:
		break;
	}
}

void CStageBox::Update()
{
	if (!m_isSelectMapLayer)
	{
		PiecePositionScaling();

		if (m_isEndedTouch)
			PieceAutoMove();
	}

}

void CStageBox::PieceMove(float a_fMove)
{
	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			m_pBoxPiece[i][k]->setPosition(Point(
				m_pBoxPiece[i][k]->getPosition().x + a_fMove,
				m_pBoxPiece[i][k]->getPosition().y));
		}
	}
}

void CStageBox::StageTouchBegan(Point a_ptTouchPosition)
{
	m_isEndedTouch = false;

	if (!m_isSelectMapLayer && m_isCanTouch)
	{
		for (int i = 0; i < 3; i++)
		{
			if (m_pBoxPiece[m_nNowStageNumber][i]->getBoundingBox().containsPoint(a_ptTouchPosition))
			{
				VisibleMap(true);
				break;
			}
			else
				m_ptBeganTouchPosition = a_ptTouchPosition;
		}
	}
	else
	{
		if (m_pSelectMapLayer->getVisible())
			m_pSelectMapLayer->TouchMap(a_ptTouchPosition);
	}
}

void CStageBox::StageTouchMoved(Point a_ptTouchPosition)
{
	if (m_isSelectMapLayer)
		return;

	if (m_ptBeganTouchPosition.x - a_ptTouchPosition.x > 0 &&
		m_pBoxPiece[2][0]->getScale() < 1)
	{
		PieceMove(-15);
	}
	else if (m_ptBeganTouchPosition.x - a_ptTouchPosition.x <= 0 &&
		m_pBoxPiece[0][0]->getScale() < 1)
	{
		PieceMove(15);
	}

	m_ptBeganTouchPosition = a_ptTouchPosition;
}

void CStageBox::StageTouchEnded(Point a_ptTouchPosition)
{
	m_isEndedTouch = true;
}

void CStageBox::VisibleMap(bool a_isVisible)
{
	for (int i = 0; i < 3; i++)
	{
		if (i == m_nNowStageNumber)
			continue;

		for (int k = 0; k < 3; k++)
			m_pBoxPiece[i][k]->setVisible(!a_isVisible);
	}

	auto _DownActionFunc = [=] {
		m_pBackStageMain->setVisible(a_isVisible);
		m_pSelectMapLayer->FadeStageMaps(m_nNowStageNumber, a_isVisible);
	};

	if (a_isVisible)
	{
		auto move_1 = MoveTo::create(1.0f, Point(0, 720));
		auto move_2 = MoveTo::create(1.0f, Point(1280, 720));
		auto move_3 = MoveTo::create(1.0f, Point(640, 0));

		m_pPieceMove[0] = EaseInOut::create(move_1,6);
		m_pPieceMove[1] = EaseInOut::create(move_2,6);
		m_pPieceMove[2] = EaseInOut::create(move_3,6);

		m_pPieceDownAction = Sequence::create(m_pPieceMove[2],
			DelayTime::create(0.02),                                        
			CallFunc::create(std::bind(_DownActionFunc)), NULL); 
		m_isSelectMapLayer = true;
	}
	else
	{
		auto move_1 = MoveTo::create(1.0f, Point(635, 210));
		auto move_2 = MoveTo::create(1.0f, Point(645, 210));
		auto move_3 = MoveTo::create(1.0f, Point(640, 340));

		m_pPieceMove[0] = EaseInOut::create(move_1,6);
		m_pPieceMove[1] = EaseInOut::create(move_2,6);
		m_pPieceMove[2] = EaseInOut::create(move_3,6);

		m_pBackStageMain->setVisible(false);
		m_pPieceDownAction = Sequence::create(m_pPieceMove[2],
			CallFunc::create(std::bind([=]{m_isSelectMapLayer = false; })), NULL);

		m_pSelectMapLayer->FadeStageMaps(1, a_isVisible);
	}

	for (int i = 0; i < 2; i++)
		m_pBoxPiece[m_nNowStageNumber][i]->runAction(m_pPieceMove[i]);
	m_pBoxPiece[m_nNowStageNumber][2]->runAction(m_pPieceDownAction);
}