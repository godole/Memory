#include "Door.h"
#include "LayerDefine.h"
#include "Box2dSprite.h"
#include "LayerDefine.h"

using namespace cocos2d;
using namespace std;


CDoor::CDoor()
{
	m_bIsOpened = false;
}


CDoor::~CDoor()
{
}

void CDoor::Init(cocos2d::CCLayer* parentLayer, b2World* world, DoorData data)
{
	auto leftSprite = CCSprite::create("map/map2/object/door_left.png");
	leftSprite->setAnchorPoint(ccp(1.0, 0.0));
	parentLayer->addChild(leftSprite, OBJECT_ZORDER);
	m_pLeftDoorSprite = shared_ptr<CBox2dSprite>(new CBox2dSprite);
	m_pLeftDoorSprite->Init(leftSprite, world, b2BodyType::b2_staticBody, ccp(1.0, 0));
	m_pLeftDoorSprite->setPositionTo(data.m_vPosition);

	auto rightSprite = CCSprite::create("map/map2/object/door_right.png");
	rightSprite->setAnchorPoint(ccp(0.0, 0.0));
	parentLayer->addChild(rightSprite, CHARACTER_ZORDER + 1);
	m_pRightDoorSprite = shared_ptr<CBox2dSprite>(new CBox2dSprite);
	m_pRightDoorSprite->Init(rightSprite, world, b2BodyType::b2_staticBody, ccp(0.0, 0.0));
	m_pRightDoorSprite->setPositionTo(data.m_vPosition);

	m_pFrameSprite = CCSprite::create("map/map2/object/door_round.png");
	m_pFrameSprite->setAnchorPoint(ccp(0.5, 0.0));
	m_pFrameSprite->setPosition(data.m_vPosition);
	parentLayer->addChild(m_pFrameSprite, OBJECT_ZORDER);
}

void CDoor::Scroll(cocos2d::Vec2 a_vVelocity)
{
	m_pFrameSprite->setPosition(m_pFrameSprite->getPosition() + a_vVelocity);
	m_pLeftDoorSprite->setPositionBy(a_vVelocity);
	m_pRightDoorSprite->setPositionBy(a_vVelocity);
}

void CDoor::On()
{
	m_pRightDoorSprite->getSpritePtr()->setVisible(false);
	m_pRightDoorSprite->getBodyStructure().body->SetActive(false);

	m_pLeftDoorSprite->getSpritePtr()->setVisible(false);
	m_pLeftDoorSprite->getBodyStructure().body->SetActive(false);

	m_bIsOpened = true;
}

void CDoor::Off()
{
	m_pRightDoorSprite->getSpritePtr()->setVisible(true);
	m_pRightDoorSprite->getBodyStructure().body->SetActive(true);

	m_pLeftDoorSprite->getSpritePtr()->setVisible(true);
	m_pLeftDoorSprite->getBodyStructure().body->SetActive(true);

	m_bIsOpened = false;
}

void CDoor::Update()
{
	if (m_bIsOpened)
		return;

	auto player = Director::sharedDirector()->getRunningScene()->getChildByTag(MAIN_LAYER);

	if (player != NULL)
	{
		auto playerSprite = player->getChildByTag(CHAR_NODE);
		if (playerSprite->getPositionX() > m_pFrameSprite->getPositionX())
		{
			m_pRightDoorSprite->getBodyStructure().body->SetActive(false);
			m_pLeftDoorSprite->getBodyStructure().body->SetActive(true);
		}

		else
		{
			m_pRightDoorSprite->getBodyStructure().body->SetActive(true);
			m_pLeftDoorSprite->getBodyStructure().body->SetActive(false);
		}
	}
}