#include "Scene_PlayBGLayer.h"
#include "DataManager.h"
#include "ScrollSprite.h"
#include "ScrollManager.h"
#include "Player.h"
#include "Box2dSprite.h"

void Scene_PlayBGLayer::LayerInit()
{
	auto background = CCSprite::create(CDataManager::getInstance()->getBackgroundTextureName());
	background->setAnchorPoint(ccp(0, 0));
	this->addChild(background, 0);

	m_pBackground = shared_ptr<CScrollSprite>(new CScrollSprite());
	m_pBackground->Init(background);

	CScrollManager::getInstance()->Insert(m_pBackground);

	m_pZeroWall = CreateWall("object/20.png", ccp(0, 100));
	m_pMaxWall = CreateWall("object/20.png", ccp(2560, 100));
}

void Scene_PlayBGLayer::update(float dt)
{
	Vec2 cv = visibleSize / 2;
	Vec2 sv = cv - m_pLayerData->m_pPlayer->getPosition();
	sv = sv / 9;

	if (m_pBackground->getSpritePtr()->getPositionX() + sv.x > 0)
	{
		sv.x = -m_pBackground->getSpritePtr()->getPositionX();
	}

	if (m_pBackground->getSpritePtr()->getPositionX() + m_pBackground->getSpritePtr()->getContentSize().width + sv.x < visibleSize.width)
	{
		sv.x = visibleSize.width - m_pBackground->getSpritePtr()->getBoundingBox().getMaxX();
	}

	if (m_pBackground->getSpritePtr()->getPositionY() + sv.y > 0)
	{
		sv.y = -m_pBackground->getSpritePtr()->getPositionY();
	}

	m_pZeroWall->setPositionBy(sv);
	m_pMaxWall->setPositionBy(sv);
	CScrollManager::getInstance()->Scroll(sv);
}

CBox2dSprite* Scene_PlayBGLayer::CreateWall(string filename, CCPoint pos)
{
	auto pWall1 = CCSprite::create(filename);
	pWall1->setPosition(pos);
	this->addChild(pWall1);

	auto wall = new CBox2dSprite;
	wall->Init(pWall1, m_pLayerData->m_pWorld, b2BodyType::b2_staticBody, ccp(0.5, 0));

	return wall;
}