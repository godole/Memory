#include "Stage1Background.h"
#include "DataManager.h"
#include "ScrollSprite.h"
#include "ScrollManager.h"
#include "Player.h"
#include "Box2dSprite.h"
#include "ParticleManager.h"
#include "BackgroundCloud.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

void Stage1Background::LayerInit()
{
	auto background = CCSprite::create("map/map1/background/map_1.png");
	background->setAnchorPoint(ccp(0, 0));
	this->addChild(background, 0);

	m_pLayerData->m_pBackground = shared_ptr<CScrollSprite>(new CScrollSprite());
	m_pLayerData->m_pBackground->Init(background);

	CScrollManager::getInstance()->Insert(m_pLayerData->m_pBackground);

	auto treeTexture = CCSprite::create("map/map1/background/map_1_tree_2.png");
	treeTexture->setAnchorPoint(ccp(0, 0));
	this->addChild(treeTexture, 2);

	auto tree = shared_ptr<CScrollSprite>(new CScrollSprite);
	tree->Init(treeTexture);

	CScrollManager::getInstance()->Insert(tree);

	CParticleManager::getInstance()->addParticle(background, "map/map1/background/bubble.plist", CCPoint(visibleSize.width / 2, visibleSize.height / 2));

	auto cloudInst = shared_ptr<BackgroundCloud>(new BackgroundCloud);
	cloudInst->Init(1.0f, visibleSize.width);
	UpdateManager::getInstance()->Insert(cloudInst);

	for (int i = 0; i < 4; i++)
	{
		string filename = StringUtils::format("map/map1/background/stage1_cloud%d.png", i + 1);
		this->addChild(cloudInst->InsertCloud(filename, ccp(random(100, 1500), random(600, 900))), 1);
	}

	MakeTreeEffect("map/map1/effect/map_1_treebox1.png", ccp(300, 400));
	MakeTreeEffect("map/map1/effect/map_1_treebox3.png", ccp(370, 430));
	MakeTreeEffect("map/map1/effect/map_1_treebox4.png", ccp(580, 180));
	MakeTreeEffect("map/map1/effect/map_1_treebox1.png", ccp(900, 350));
	MakeTreeEffect("map/map1/effect/map_1_treebox1.png", ccp(1500, 400));
	MakeTreeEffect("map/map1/effect/map_1_treebox1.png", ccp(1900, 400));

	//CParticleManager::getInstance()->addParticle(treeTexture, "map/map1/effect/tree.plist", ccp(300, 400), 1);

	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/stage_1.mp3", true);
}

void Stage1Background::MakeTreeEffect(string texturename, CCPoint a_vPos)
{
	auto treeEffect = CCSprite::create(texturename);
	float randomTime = random(0.6, 0.9);
	treeEffect->setPosition(a_vPos);
	treeEffect->runAction(CCRepeatForever::create(CCSequence::create((CCFiniteTimeAction*)CCScaleTo::create(randomTime, 0.8), CCScaleTo::create(randomTime, 1.2), NULL)));
	this->addChild(treeEffect, 3);

	auto effect = shared_ptr<CScrollSprite>(new CScrollSprite);
	effect->Init(treeEffect);
	CScrollManager::getInstance()->Insert(effect);
}