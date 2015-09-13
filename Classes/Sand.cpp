#include "Sand.h"
#include "Box2dSprite.h"
#include "CTextureFactory.h"
#include "ObjectManager.h"
#include "LayerDefine.h"


CSand::CSand()
{
}


CSand::~CSand()
{
}

void CSand::Init(CCNode* a_pParent, b2World* a_world, SandData a_data)
{
	m_pOnTexture = CTextureFactory::CreateTexture("map/map3/object/sendbox_water.png");
	m_pOffTexture = CTextureFactory::CreateTexture("map/map3/object/sendbox.png");
	m_pSprite = CCSprite::createWithTexture(m_pOffTexture);

	a_pParent->addChild(m_pSprite, OBJECT_ZORDER);

	m_pBox2dSprite = shared_ptr<CBox2dSprite>(new CBox2dSprite);
	m_pBox2dSprite->Init(m_pSprite, a_world, b2BodyType::b2_staticBody, 80, 80);
	m_pBox2dSprite->setPositionTo(a_data.m_vPosition);
	m_pBox2dSprite->getBodyStructure().body->SetActive(false);

	CObjectManager::getInstance()->getBox2dSprite()->InsertObject(m_pBox2dSprite);
	CObjectManager::getInstance()->getNotBoxArray()->InsertObject(m_pBox2dSprite);
}

void CSand::On()
{
	m_pSprite->setTexture(m_pOnTexture);
	m_pBox2dSprite->getBodyStructure().body->SetActive(true);
}

void CSand::Off()
{
	m_pSprite->setTexture(m_pOffTexture);
	m_pBox2dSprite->getBodyStructure().body->SetActive(false);
}

void CSand::Scroll(Vec2 a_vVelocity)
{
	m_pBox2dSprite->setPositionBy(a_vVelocity);
}