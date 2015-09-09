#include "Scene_Stage3.h"
#include "ScrollSprite.h"
#include "ObjectFactory.h"
#include "ObjectManager.h"
#include "Player.h"
#include "WindBox.h"
#include "Water.h"
#include "SimpleAudioEngine.h"
#include "ParticleManager.h"

USING_NS_CC;
using namespace CocosDenshion;


Scene_Stage3::Scene_Stage3()
{
}


Scene_Stage3::~Scene_Stage3()
{
}

void Scene_Stage3::BackgroundInit()
{
	auto backgroundSprite = CCSprite::create("map/map3/background/map_3.png");
	backgroundSprite->setAnchorPoint(ccp(0, 0));
	this->addChild(backgroundSprite, 0, "background");

	m_pBackground = shared_ptr<CScrollSprite>(new CScrollSprite);
	m_pBackground->Init(backgroundSprite);

	CScrollManager::getInstance()->Insert(m_pBackground);

	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/stage_3.mp3", true);

	CParticleManager::getInstance()->addParticle(m_pScreenParticleNode, "map/map3/effect/sandstorm.plist", ccp(960, 540));
}

void Scene_Stage3::ObjectInit()
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
}

void Scene_Stage3::BackgroundUpdate()
{

}

void Scene_Stage3::ObjectUpdate()
{
	
}