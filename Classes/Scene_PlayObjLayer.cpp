#include "Scene_PlayObjLayer.h"
#include "ObjectFactory.h"
#include "DataManager.h" 
#include "Things.h"
#include "Rail.h"

void Scene_PlayObjLayer::LayerInit()
{
	auto factory = CObjectFactory::getInstance();
	auto mgr = CDataManager::getInstance();
	auto profile = m_pLayerData->m_pPlayer->getActorProfile();

	for (auto itr = mgr->getBoxData()->begin(); itr != mgr->getBoxData()->end(); itr++)
	{
		auto box = factory->CreateBox(this, m_pLayerData->m_pWorld, profile, *itr);
		m_arrObject.push_back(box);
	}

	for (auto itr = mgr->getRailData()->begin(); itr != mgr->getRailData()->end(); itr++)
	{
		auto rail = factory->CreateRail(this, m_pLayerData->m_pWorld, profile, *itr);
		m_arrObject.push_back(rail);
		m_arrRail.push_back(rail);
	}

	for (auto itr = mgr->getPulleyData()->begin(); itr != mgr->getPulleyData()->end(); itr++)
	{
		auto pulley = factory->CreatePulley(this, m_pLayerData->m_pWorld, profile, *itr);
		m_arrObject.push_back(pulley);
	}

	for (auto itr = mgr->getMirageData()->begin(); itr != mgr->getMirageData()->end(); itr++)
	{
		auto mirage = factory->CreateMirage(this, m_pLayerData->m_pWorld, profile, *itr);
		m_arrObject.push_back(mirage);
	}

	for (auto itr = mgr->getGroundData()->begin(); itr != mgr->getGroundData()->end(); itr++)
	{
		factory->CreateGround(this, m_pLayerData->m_pWorld, *itr);
	}

	auto pTempSprite = CCSprite::create(mgr->getDestinationData()->m_szTextureName);
	pTempSprite->setPosition(mgr->getDestinationData()->m_vPosition);
	pTempSprite->setAnchorPoint(ccp(0.5, 0));
	this->addChild(pTempSprite);

	m_pLayerData->m_pDestination = shared_ptr<CScrollSprite>(new CScrollSprite);
	m_pLayerData->m_pDestination->Init(pTempSprite);
	CScrollManager::getInstance()->Insert(m_pLayerData->m_pDestination);

	settingTouchDispatcher();
}

bool Scene_PlayObjLayer::onTouchBegan(Touch* touch, Event* event)
{
	CCPoint touchPos = touch->getLocation();
	for (int i = 0; i < m_arrObject.size(); i++)
	{
		if (m_pLayerData->m_pPlayer->Action(this, m_arrObject[i]->getBehaviorPtr(), touchPos))
			break;
	}

	return true;
}

void Scene_PlayObjLayer::onTouchMoved(Touch* touches, Event* event)
{

}

void Scene_PlayObjLayer::onTouchEnded(Touch* touches, Event* event)
{

}

void Scene_PlayObjLayer::settingTouchDispatcher()
{
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);

	touchListener->onTouchBegan = CC_CALLBACK_2(Scene_PlayObjLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(Scene_PlayObjLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Scene_PlayObjLayer::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void Scene_PlayObjLayer::update(float dt)
{
	for (auto itr = m_arrRail.begin(); itr != m_arrRail.end(); itr++)
	{
		CCRect r;
		r.setRect(itr->get()->getSpritePtr()->getBoundingBox().getMinX(), itr->get()->getSpritePtr()->getBoundingBox().getMaxY(),
			itr->get()->getSpritePtr()->getContentSize().width, itr->get()->getSpritePtr()->getContentSize().height + 3);

		if (m_pLayerData->m_pPlayer->getBodySpritePtr()->getBoundingBox().intersectsRect(r))
		{
			m_pLayerData->m_pPlayer->RunRail(itr->get()->getDirection());
		}
	}
}