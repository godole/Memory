#include "Stage1Background.h"
#include "DataManager.h"
#include "ScrollSprite.h"
#include "ScrollManager.h"
#include "Player.h"
#include "Box2dSprite.h"
#include "ParticleManager.h"

void Stage1Background::LayerInit()
{
	auto background = CCSprite::create("map/map1/background/map_1.png");
	background->setAnchorPoint(ccp(0, 0));
	this->addChild(background, 0);

	m_pLayerData->m_pBackground = shared_ptr<CScrollSprite>(new CScrollSprite());
	m_pLayerData->m_pBackground->Init(background);

	CScrollManager::getInstance()->Insert(m_pLayerData->m_pBackground);

	auto treeTexture = CCSprite::create("map/map1/background/map_1_tree.png");
	treeTexture->setAnchorPoint(ccp(0, 0));
	this->addChild(treeTexture, 2);

	auto tree = shared_ptr<CScrollSprite>(new CScrollSprite);
	tree->Init(treeTexture);

	CScrollManager::getInstance()->Insert(tree);

	CParticleManager::getInstance()->addParticle(background, "map/map1/background/bubble.plist", CCPoint(visibleSize.width / 2, visibleSize.height / 2));

	m_nCloudCount = 4;
	m_fCloudSpeed = 1.0f;

	for (int i = 0; i < m_nCloudCount; i++)
	{
		string filename = StringUtils::format("map/map1/background/stage1_cloud%d.png", i + 1);
		auto cloudTexture = CCSprite::create(filename);
		this->addChild(cloudTexture, 1);
		cloudTexture->setPosition(ccp(random(100, 1500), random(600, 900)));

		auto cloud = shared_ptr<CScrollSprite>(new CScrollSprite);
		cloud->Init(cloudTexture);

		m_arrCloud.push_back(cloud);
		CScrollManager::getInstance()->Insert(cloud);
	}

	scheduleUpdate();
}

void Stage1Background::update(float dt)
{
	for (int i = 0; i < m_nCloudCount; i++)
	{ 
		auto cloud = m_arrCloud[i]->getSpritePtr();
		cloud->setPositionX(cloud->getPositionX() - m_fCloudSpeed);
		if (cloud->getPositionX() <= 0 - cloud->getContentSize().width)
		{
			cloud->setPositionX(visibleSize.width);
		}
	}
}