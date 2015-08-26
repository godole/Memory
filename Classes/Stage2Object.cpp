#include "Stage2Object.h"
#include "ObjectFactory.h"
#include "DataManager.h"
#include "UpdateManager.h"
#include "Box2dSprite.h"


void Stage2Object::LayerInit()
{
	auto factory = CObjectFactory::getInstance();
	auto mgr = CDataManager::getInstance();
	auto profile = m_pLayerData->m_pPlayer->getActorProfile();

	for (auto itr = mgr->getBoxData()->begin(); itr != mgr->getBoxData()->end(); itr++)
	{
		auto box = factory->CreateBox(this, m_pLayerData->m_pWorld, profile, *itr);
		m_pLayerData->m_arrObject.push_back(box);
	}

	for (auto itr = mgr->getRailData()->begin(); itr != mgr->getRailData()->end(); itr++)
	{
		auto rail = factory->CreateRail(this, m_pLayerData->m_pWorld, profile, *itr);
		m_pLayerData->m_arrObject.push_back(rail);
		m_arrRail.push_back(rail);
	}

	for (auto itr = mgr->getPulleyData()->begin(); itr != mgr->getPulleyData()->end(); itr++)
	{
		auto pulley = factory->CreatePulley(this, m_pLayerData->m_pWorld, profile, *itr);
		m_pLayerData->m_arrObject.push_back(pulley);
	}

	for (auto itr = mgr->getGroundData()->begin(); itr != mgr->getGroundData()->end(); itr++)
	{
		factory->CreateGround(this, m_pLayerData->m_pWorld, *itr);
	}

	scheduleUpdate();
}

void Stage2Object::update(float dt)
{
	for (auto itr = m_arrRail.begin(); itr != m_arrRail.end(); itr++)
	{
		for (auto itr2 = itr->get()->getRailSpriteArr()->begin(); itr2 != itr->get()->getRailSpriteArr()->end(); itr2++)
		{
			CCRect r;
			r.setRect(itr2->get()->getSpritePtr()->getBoundingBox().getMinX(), itr2->get()->getSpritePtr()->getBoundingBox().getMaxY(),
				itr2->get()->getSpritePtr()->getContentSize().width, itr2->get()->getSpritePtr()->getContentSize().height + 3);

			if (m_pLayerData->m_pPlayer->getBodySpritePtr()->getBoundingBox().intersectsRect(r))
			{
				m_pLayerData->m_pPlayer->RunRail(itr->get()->getDirection());
				break;
			}
		}
	}
}