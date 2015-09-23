#include "Scene_Stage2.h"
#include "ScrollSprite.h"
#include "ScrollManager.h"
#include "UpdateManager.h"
#include "BackgroundCloud.h"
#include "SimpleAudioEngine.h"
#include "ObjectFactory.h"
#include "Player.h"
#include "Rail.h"
#include "Box2dSprite.h"
#include "LayerDefine.h"
#include "ParticleManager.h"

using namespace CocosDenshion;


Scene_Stage2::Scene_Stage2()
{
}


Scene_Stage2::~Scene_Stage2()
{
}

void Scene_Stage2::BackgroundInit()
{
	auto background = CCSprite::create("map/map2/background/map_2.png");
	background->setAnchorPoint(ccp(0, 0));
	this->addChild(background, BACKGROUND_ZORDER);

	m_pBackground = shared_ptr<CScrollSprite>(new CScrollSprite);
	m_pBackground->Init(background);
	CScrollManager::getInstance()->Insert(m_pBackground);

	auto building = CCSprite::create("map/map2/background/map_2_build.png");
	building->setAnchorPoint(ccp(0, 0));
	this->addChild(building, BACKGROUND_ZORDER);

	m_pBackgroundBuild = shared_ptr<CScrollSprite>(new CScrollSprite);
	m_pBackgroundBuild->Init(building);
	CScrollManager::getInstance()->Insert(m_pBackgroundBuild);

	auto cloudInst = shared_ptr<BackgroundCloud>(new BackgroundCloud);
	cloudInst->Init(0.7, visibleSize.width);

	for (int i = 0; i < 2; i++)
	{
		string filename = StringUtils::format("map/map2/effect/map_2_cloud%d.png", i + 1);
		this->addChild(cloudInst->InsertCloud(filename, ccp(random(100, 1500), random(400, 700))), BACKGROUND_ZORDER);
	}

	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/stage_2.mp3", true);

	CParticleManager::getInstance()->addParticle(m_pScreenParticleNode, "map/map2/effect/rain.plist", ccp(1000, 1000));
}

void Scene_Stage2::ObjectInit()
{
	auto factory = CObjectFactory::getInstance();
	auto mgr = CDataManager::getInstance();
	auto profile = m_pPlayer->getActorProfile();

	for (auto itr = mgr->getRailData()->begin(); itr != mgr->getRailData()->end(); itr++)
	{
		auto rail = factory->CreateRail(this,  m_pWorld, profile, *itr);
		m_arrObject.push_back(rail);
		m_arrRail.push_back(rail);
	}

	for (auto itr = mgr->getPulleyData()->begin(); itr != mgr->getPulleyData()->end(); itr++)
	{
		auto pulley = factory->CreatePulley(this,  m_pWorld, profile, *itr);
		 m_arrObject.push_back(pulley);
	}

	for (auto itr = mgr->getDoorData()->begin(); itr != mgr->getDoorData()->end(); itr++)
	{
		factory->CreateDoor(this,  m_pWorld, *itr);
	}

	for (auto itr = mgr->getSpannerData()->begin(); itr != mgr->getSpannerData()->end(); itr++)
	{
		auto spanner = factory->CreateSpanner(this, profile, *itr);
		 m_arrObject.push_back(spanner);
	}
}

void Scene_Stage2::BackgroundUpdate()
{

}

void Scene_Stage2::ObjectUpdate()
{
	for (auto itr = m_arrRail.begin(); itr != m_arrRail.end(); itr++)
	{
		for (auto itr2 = itr->get()->getRailSpriteArr()->begin(); itr2 != itr->get()->getRailSpriteArr()->end(); itr2++)
		{
			CCRect r;
			r.setRect(itr2->get()->getSpritePtr()->getBoundingBox().getMinX(), itr2->get()->getSpritePtr()->getBoundingBox().getMaxY(),
				itr2->get()->getSpritePtr()->getContentSize().width, itr2->get()->getSpritePtr()->getContentSize().height + 3);

			if ( m_pPlayer->getBodySpritePtr()->getBoundingBox().intersectsRect(r))
			{
				 m_pPlayer->RunRail(itr->get()->getDirection());
				break;
			}
		}
	}
}