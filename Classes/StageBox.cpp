#include "StageBox.h"
#include "Scene_Play.h"
#include "DataManager.h"
#include "SceneManager.h"

CStageBox::CStageBox()
{
}


CStageBox::~CStageBox()
{
}

void CStageBox::init(Layer * a_pParentLayer)
{
	m_pPiece = Layer::create();
	m_pStages = Layer::create();

	m_pStages->setVisible(false);

	a_pParentLayer->addChild(m_pPiece);
	a_pParentLayer->addChild(m_pStages);

	m_pPieceLeft = Sprite::create("stageselect/piece.png");
	m_pPieceRight = Sprite::create("stageselect/piece.png");
	m_pPieceDown = Sprite::create("stageselect/piece.png");

	m_pPieceRight->setPosition(Point(772, 430));

	m_pPieceDown->setRotation(120);
	m_pPieceDown->setPosition(Point(650, 200));

	m_pPieceLeft->setFlippedX(true);
	m_pPieceLeft->setPosition(Point(512, 420));

	m_pPiece->addChild(m_pPieceRight);
	m_pPiece->addChild(m_pPieceLeft);
	m_pPiece->addChild(m_pPieceDown);

	m_isVisible = false;
	m_isCheck = false;
	m_isTouch = true;

	for (int i = 0; i < 10; i++)
	{
		m_pStage[i] = Sprite::create(StringUtils::format("number/number_%d.png", i + 1));
		m_pStage[i]->setPosition(Point(450 + (i%5) * 100, 400 - (i / 5) * 100));
		m_pStages->addChild(m_pStage[i]);
	}
}

void CStageBox::touch(Point a_pPoint)
{
	MoveTo * Action;
	CallFunc * Call;
	Sequence * Seq;

	if (!m_isVisible)
	{
		if (m_isTouch)
		{
			if (m_pPieceDown->getBoundingBox().containsPoint(a_pPoint))
			{
				m_isTouch = false;
				Action = MoveTo::create(1.0, Point(0, 400));
				Call = CallFunc::create(std::bind([=]{
					m_nStageNum = 0;
					m_pStages->setVisible(true);
					m_isVisible = true;
				}));
				Seq = Sequence::create(Action, Call, NULL);

				m_pPiece->runAction(Seq);
			}
			else if (m_pPieceLeft->getBoundingBox().containsPoint(a_pPoint))
			{
				m_isTouch = false;
				Action = MoveTo::create(1.0, Point(500, -200));
				Call = CallFunc::create(std::bind([=]{
					m_nStageNum = 1;
					m_pStages->setVisible(true);
					m_isVisible = true;

				}));
				Seq = Sequence::create(Action, Call, NULL);

				m_pPiece->runAction(Seq);
			}
			else if (m_pPieceRight->getBoundingBox().containsPoint(a_pPoint))
			{
				m_isTouch = false;
				Action = MoveTo::create(1.0, Point(-500, 200));
				Call = CallFunc::create(std::bind([=]{
					m_nStageNum = 2;
					m_pStages->setVisible(true);
					m_isVisible = true;

				}));
				Seq = Sequence::create(Action, Call, NULL);

				m_pPiece->runAction(Seq);
			}
		}
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			if (m_pStage[i]->getBoundingBox().containsPoint(a_pPoint))
			{
				if (m_nStageNum == 0)
				{
					if (i < 2)
					{
						CDataManager::getInstance()->LoadMapData(
							StringUtils::format("map/data/map1-%d.txt", i + 1));
						CSceneManager::getInstance()->ChangeScene(ESceneType::e_ScenePlay);
					}
					else
						continue;
				}
				else if (m_nStageNum == 1)
				{
					if (i < 2)
					{
						CDataManager::getInstance()->LoadMapData(
							StringUtils::format("map/data/map2-%d.txt", i + 1));
						CSceneManager::getInstance()->ChangeScene(ESceneType::e_ScenePlay);
					}
					else
						continue;
				}
				else if (m_nStageNum == 2)
				{
					if (i < 2)
					{
						CDataManager::getInstance()->LoadMapData(
							StringUtils::format("map/data/map3-%d.txt", i + 1));
						CSceneManager::getInstance()->ChangeScene(ESceneType::e_ScenePlay);
					}
					else
						continue;
				}
				m_isCheck = true;
			}
		}
		if (!m_isCheck)
		{
			m_pStages->setVisible(false);
			if (m_nStageNum == 0)
			{
				Action = MoveTo::create(1.0, Point(0, 0));
				Call = CallFunc::create(std::bind([=]{
					m_nStageNum = 0;
					m_isVisible = false;
					m_isTouch = true;
				}));
			}
			else if (m_nStageNum == 1)
			{
				Action = MoveTo::create(1.0, Point(0, 0));
				Call = CallFunc::create(std::bind([=]{
					m_nStageNum = 1;
					m_isVisible = false;
					m_isTouch = true;
				}));
			}
			else if (m_nStageNum == 2)
			{
				Action = MoveTo::create(1.0, Point(0, 0));
				Call = CallFunc::create(std::bind([=]{
					m_nStageNum = 2;
					m_isVisible = false;
					m_isTouch = true;
				}));
			}
			Seq = Sequence::create(Action, Call, NULL);
			m_pPiece->runAction(Seq);
		}
	}
}