#include "Stage2Background.h"
#include "ScrollSprite.h"
#include "ScrollManager.h"
#include "BackgroundCloud.h"
#include "UpdateManager.h"
#include <memory>

using namespace std;


void Stage2Background::LayerInit()
{
	auto background = CCSprite::create("map/map2/background/map_2.png");
	background->setAnchorPoint(ccp(0, 0));
	this->addChild(background, 0);

	m_pLayerData->m_pBackground = shared_ptr<CScrollSprite>(new CScrollSprite);
	m_pLayerData->m_pBackground->Init(background);
	CScrollManager::getInstance()->Insert(m_pLayerData->m_pBackground);

	auto building = CCSprite::create("map/map2/background/map_2_build.png");
	building->setAnchorPoint(ccp(0, 0));
	this->addChild(building, 2);

	m_pBackgroundBuild = shared_ptr<CScrollSprite>(new CScrollSprite);
	m_pBackgroundBuild->Init(building);
	CScrollManager::getInstance()->Insert(m_pBackgroundBuild);

	auto cloudInst = shared_ptr<BackgroundCloud>(new BackgroundCloud);
	UpdateManager::getInstance()->Insert(cloudInst);
	cloudInst->Init(0.7, visibleSize.width);
	
	for (int i = 0; i < 2; i++)
	{
		string filename = StringUtils::format("map/map2/effect/map_2_cloud%d.png", i + 1);
		this->addChild(cloudInst->InsertCloud(filename, ccp(random(100, 1500), random(600, 900))), 1);
	}
}