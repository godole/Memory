#include "Scene_ObjTest.h"
#include "ScrollSprite.h"
#include "ObjectFactory.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Water.h"
#include "WindBox.h"
#include "SimpleAudioEngine.h"
#include "ParticleManager.h"

USING_NS_CC;
using namespace CocosDenshion;


Scene_ObjTest::Scene_ObjTest()
{
}


Scene_ObjTest::~Scene_ObjTest()
{
}

void Scene_ObjTest::BackgroundInit()
{
	auto backgroundSprite = CCSprite::create("map/test/map_3.png");
	backgroundSprite->setAnchorPoint(ccp(0, 0));
	this->addChild(backgroundSprite, 0, "background");

	m_pBackground = shared_ptr<CScrollSprite>(new CScrollSprite);
	m_pBackground->Init(backgroundSprite);

	CScrollManager::getInstance()->Insert(m_pBackground);

	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/stage_3.mp3", true);

	CParticleManager::getInstance()->addParticle(m_pScreenParticleNode, "map/map3/effect/sandstorm.plist", ccp(960, 540));
}

void Scene_ObjTest::ObjectInit()
{
	auto factory = CObjectFactory::getInstance();
	auto mgr = CDataManager::getInstance();
	auto profile = m_pPlayer->getActorProfile();

	for (auto itr = mgr->getMirageData()->begin(); itr != mgr->getMirageData()->end(); itr++)
	{
		auto mirage = factory->CreateMirage(this, m_pWorld, profile, *itr);
		m_arrObject.push_back(mirage);
	}

	for (auto itr = mgr->getWaterData()->begin(); itr != mgr->getWaterData()->end(); itr++)
	{
		auto water = factory->CreateWater(this, profile, *itr);
		m_arrObject.push_back(water);
	}

	for (auto itr = mgr->getSandData()->begin(); itr != mgr->getSandData()->end(); itr++)
	{
		auto sand = factory->CreateSand(this, m_pWorld, *itr);
		CObjectManager::getInstance()->getSandArray()->InsertObject(sand);
	}

	for (auto itr = mgr->getWindBoxData()->begin(); itr != mgr->getWindBoxData()->end(); itr++)
	{
		auto windBox = factory->CreateWindBox(this, m_pWorld, profile, *itr);
		m_arrObject.push_back(windBox);
		m_arrWindBox.push_back(windBox);
	}

	for (auto itr = mgr->getRailData()->begin(); itr != mgr->getRailData()->end(); itr++)
	{
		auto rail = factory->CreateRail(this, m_pWorld, profile, *itr);
		m_arrObject.push_back(rail);
		m_arrRail.push_back(rail);
	}

	for (auto itr = mgr->getPulleyData()->begin(); itr != mgr->getPulleyData()->end(); itr++)
	{
		auto pulley = factory->CreatePulley(this, m_pWorld, profile, *itr);
		m_arrObject.push_back(pulley);
	}

	for (auto itr = mgr->getDoorData()->begin(); itr != mgr->getDoorData()->end(); itr++)
	{
		factory->CreateDoor(this, m_pWorld, *itr);
	}

	for (auto itr = mgr->getSpannerData()->begin(); itr != mgr->getSpannerData()->end(); itr++)
	{
		auto spanner = factory->CreateSpanner(this, profile, *itr);
		m_arrObject.push_back(spanner);
	}
}

void Scene_ObjTest::BackgroundUpdate()
{

}

void Scene_ObjTest::ObjectUpdate()
{
	for (auto itr = m_arrRail.begin(); itr != m_arrRail.end(); itr++)
	{
		for (auto itr2 = itr->get()->getRailSpriteArr()->begin(); itr2 != itr->get()->getRailSpriteArr()->end(); itr2++)
		{
			CCRect r;
			r.setRect(itr2->get()->getSpritePtr()->getBoundingBox().getMinX(), itr2->get()->getSpritePtr()->getBoundingBox().getMaxY(),
				itr2->get()->getSpritePtr()->getContentSize().width, itr2->get()->getSpritePtr()->getContentSize().height + 3);

			if (m_pPlayer->getBodySpritePtr()->getBoundingBox().intersectsRect(r))
			{
				m_pPlayer->RunRail(itr->get()->getDirection());
				break;
			}
		}
	}

	for (auto itr = m_arrWindBox.begin(); itr != m_arrWindBox.end(); ++itr)
	{
		(*itr)->MakeFly(m_pPlayer.get());
	}
}