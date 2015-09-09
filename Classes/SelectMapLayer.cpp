#include "SelectMapLayer.h"
#include "UpdateManager.h"
#include "SceneManager.h"
#include "DataManager.h"
#include "FriendList.h"

CSelectMapLayer::CSelectMapLayer()
{
	m_isVisible = false;
}


CSelectMapLayer::~CSelectMapLayer()
{
}

void CSelectMapLayer::init(Layer * a_pParentLayer)
{
	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			m_pStagePuzzle[i][k] = Sprite::create(StringUtils::format("number/number_%d.png", k + 1));
			m_pStagePuzzle[i][k]->setVisible(false);
			m_pStagePuzzle[i][k]->setPosition(Point(450 + (k % 5) * 100, 400 - (k / 5) * 100));
			a_pParentLayer->addChild(m_pStagePuzzle[i][k]);
		}
	}

	m_pSortClearPeoples = Sprite::create("stageselect/clearpeople.png");
	m_pSortClearPeoples->setVisible(false);
	m_pSortClearPeoples->setColor(Color3B::GRAY);
	m_pSortClearPeoples->setAnchorPoint(Point(0, 0));
	m_pSortClearPeoples->setPosition(Point(100, 530));
	a_pParentLayer->addChild(m_pSortClearPeoples);

	m_pSortMoveCountPeoples = Sprite::create("stageselect/movecountpeople.png");
	m_pSortMoveCountPeoples->setVisible(false);
	m_pSortMoveCountPeoples->setColor(Color3B::GRAY);
	m_pSortMoveCountPeoples->setAnchorPoint(Point(0, 0));
	m_pSortMoveCountPeoples->setPosition(Point(350, 530));
	a_pParentLayer->addChild(m_pSortMoveCountPeoples);

	m_pGameStartButton = MenuItemImage::create(
		"stageselect/gamestart.png",
		"stageselect/gamestart.png",
		std::bind([=]{
		CDataManager::getInstance()->LoadMapData(
			StringUtils::format("map/data/map3-2.txt"));
		CSceneManager::getInstance()->ChangeScene(ESceneType::e_SceneStage1);
	}));

	// Close Button
	m_pCloseButton = MenuItemImage::create(
		"stageselect/close.png",
		"stageselect/close.png",
		std::bind([=]{
		m_pFriendList->setVisibleProfileImage(false);
		setVisible(false);
	}));

	m_pGameStartButton->setVisible(false);
	m_pGameStartButton->setPosition(Point(900, 70));

	m_pCloseButton->setVisible(false);
	m_pCloseButton->setPosition(Point(1100, 500));

	auto _pButton = Menu::create(m_pGameStartButton, m_pCloseButton, NULL);
	_pButton->setPosition(Vec2::ZERO);
	a_pParentLayer->addChild(_pButton, 3);

	// Friend List
	m_pFriendList = std::shared_ptr<FriendList>(new FriendList);
	m_pFriendList->init(a_pParentLayer);
	m_pFriendList->GetDataFromJNI();

	UpdateManager::getInstance()->Insert(m_pFriendList);
}

void CSelectMapLayer::FadeStageMaps(int a_nStageNumber, bool a_bVisible)
{
	m_nNowShowStage = a_nStageNumber;

	for (int i = 0; i < 10; i++)
		m_pStagePuzzle[a_nStageNumber][i]->setVisible(a_bVisible);

	m_pFriendList->setVisibleProfileImage(false);
	setVisible(false);

	m_isVisible = true;
}

void CSelectMapLayer::TouchMap(Point a_ptTouchPosition)
{
	if (!m_isVisible)
		return;

	bool check = false;

	for (int i = 0; i < 2; i++)
	{
		if (m_pStagePuzzle[m_nNowShowStage][i]
			->getBoundingBox().containsPoint(a_ptTouchPosition))
		{
			if (!CDataManager::getInstance()->m_bConnectFacebook)
			{
				CDataManager::getInstance()->LoadMapData(
					StringUtils::format("map/data/map3-2.txt"));
				CSceneManager::getInstance()->ChangeScene(ESceneType::e_SceneStage1);
			}
			else
			{
				m_pFriendList->setSortStageFriendRank
					((m_nNowShowStage + 1) * 10 + i);
				check = true;

				setVisible(true);
			}

			break;
		}
	}

	if (m_pSortClearPeoples->getBoundingBox().containsPoint(a_ptTouchPosition))
		m_pFriendList->setSortIndex(ESortIndex::eClearSort);
	else if (m_pSortMoveCountPeoples->getBoundingBox().containsPoint(a_ptTouchPosition))
		m_pFriendList->setSortIndex(ESortIndex::eMoveCountSort);
}

void CSelectMapLayer::setVisible(bool a_bVis)
{
	m_pCloseButton->setVisible(a_bVis);
	m_pGameStartButton->setVisible(a_bVis);
	m_pSortClearPeoples->setVisible(a_bVis);
	m_pSortMoveCountPeoples->setVisible(a_bVis);
}