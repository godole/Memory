#include "Scene_Stage1.h"
#include "LayerDefine.h"
#include "SimpleAudioEngine.h"
#include "ParticleManager.h"
#include "BackgroundCloud.h"
#include "ObjectFactory.h"
#include "ScrollSprite.h"
#include "WindBox.h"
#include "Player.h"

using namespace CocosDenshion;
USING_NS_CC;


Scene_Stage1::Scene_Stage1()
{
}


Scene_Stage1::~Scene_Stage1()
{
}

void Scene_Stage1::BackgroundInit()
{
	auto background = CCSprite::create("map/map1/background/map_1.png");
	background->setAnchorPoint(ccp(0, 0));
	this->addChild(background, BACKGROUND_ZORDER);

	m_pBackground = shared_ptr<CScrollSprite>(new CScrollSprite());
	m_pBackground->Init(background);
	CScrollManager::getInstance()->Insert(m_pBackground);

	m_pBackgroundCloud = new BackgroundCloud;
	m_pBackgroundCloud->Init(1.0f, visibleSize.width);

	for (int i = 0; i < 4; i++)
	{
		string filename = StringUtils::format("map/map1/background/stage1_cloud%d.png", i + 1);
		this->addChild(m_pBackgroundCloud->InsertCloud(filename, ccp(random(100, 1500), random(600, 900))), BACKGROUND_ZORDER);
	}

	CParticleManager::getInstance()->addParticle(background, "map/map1/background/bubble.plist", CCPoint(visibleSize.width / 2, visibleSize.height / 2), BACKGROUND_ZORDER);

	auto treeTexture = CCSprite::create("map/map1/background/map_1_tree.png");
	treeTexture->setAnchorPoint(ccp(0, 0));
	this->addChild(treeTexture, BACKGROUND_ZORDER);

	auto tree = shared_ptr<CScrollSprite>(new CScrollSprite);
	tree->Init(treeTexture);
	CScrollManager::getInstance()->Insert(tree);

	MakeTreeEffect("map/map1/effect/map_1_treebox1.png", ccp(300, 400));
	MakeTreeEffect("map/map1/effect/map_1_treebox3.png", ccp(370, 430));
	MakeTreeEffect("map/map1/effect/map_1_treebox4.png", ccp(580, 180));
	MakeTreeEffect("map/map1/effect/map_1_treebox1.png", ccp(900, 350));
	MakeTreeEffect("map/map1/effect/map_1_treebox1.png", ccp(1500, 400));
	MakeTreeEffect("map/map1/effect/map_1_treebox1.png", ccp(1900, 400));

	//CParticleManager::getInstance()->addParticle(treeTexture, "map/map1/effect/tree.plist", ccp(300, 400), 1);

	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/stage_1.mp3", true);
}

void Scene_Stage1::ObjectInit()
{
	auto factory = CObjectFactory::getInstance();
	auto mgr = CDataManager::getInstance();
	auto profile = m_pPlayer->getActorProfile();

	for (auto itr = mgr->getWindBoxData()->begin(); itr != mgr->getWindBoxData()->end(); itr++)
	{
		auto windBox = factory->CreateWindBox(this, m_pWorld, profile, *itr);
		m_arrObject.push_back(windBox);
		m_arrWindBox.push_back(windBox);
	}
}

void Scene_Stage1::BackgroundUpdate()
{
	
}

void Scene_Stage1::ObjectUpdate()
{
	for (auto itr = m_arrWindBox.begin(); itr != m_arrWindBox.end(); ++itr)
	{
		(*itr)->MakeFly(m_pPlayer.get());
	}
}

void Scene_Stage1::MakeTreeEffect(string texturename, CCPoint a_vPos)
{
	auto treeEffect = CCSprite::create(texturename);
	float randomTime = random(0.6, 0.9);
	treeEffect->setPosition(a_vPos);
	treeEffect->runAction(CCRepeatForever::create(CCSequence::create((CCFiniteTimeAction*)CCScaleTo::create(randomTime, 0.8), CCScaleTo::create(randomTime, 1.2), NULL)));
	this->addChild(treeEffect, BACKGROUND_ZORDER);

	auto effect = shared_ptr<CScrollSprite>(new CScrollSprite);
	effect->Init(treeEffect);
	CScrollManager::getInstance()->Insert(effect);
}