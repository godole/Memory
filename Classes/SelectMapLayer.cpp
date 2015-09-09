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

	m_isVisible = true;
}

void CSelectMapLayer::TouchMap(Point a_ptTouchPosition)
{
	if (!m_isVisible)
		return;

	bool check = false;

	for (int i = 0; i < 3; i++)
	{
		if (m_pStagePuzzle[m_nNowShowStage][i]
			->getBoundingBox().containsPoint(a_ptTouchPosition))
		{
			/*m_pFriendList->setSortStageFriendRank
				(m_nNowShowStage * 10 + i);*/
			//check = true;

			Director::sharedDirector()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
			CDataManager::getInstance()->LoadMapData(
				StringUtils::format("map/data/map%d-%d.txt", m_nNowShowStage + 1, i + 1));
			CDataManager::getInstance()->setCurrentStage(m_nNowShowStage + 1, i + 1);
			switch (m_nNowShowStage)
			{
			case 0 :
				CSceneManager::getInstance()->ChangeScene(ESceneType::e_SceneStage1);
				break;
			case 1 :
				CSceneManager::getInstance()->ChangeScene(ESceneType::e_SceneStage2);
				break;
			case 2 :
				CSceneManager::getInstance()->ChangeScene(ESceneType::e_SceneStage3);
				break;
			}
			

			break;
		}
	}
	if (!check)
	{
		//m_pFriendList->setVisibleProfileImage(false);
	}
}