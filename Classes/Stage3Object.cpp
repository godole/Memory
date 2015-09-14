#include "Stage3Object.h"
#include "Box.h"
#include "Mirage.h"
#include "Water.h"
#include "Sand.h"
#include "DataManager.h"
#include "ObjectFactory.h"
#include "ObjectManager.h"
#include "WindBox.h"


void Stage3Object::LayerInit()
{
	auto factory = CObjectFactory::getInstance();
	auto mgr = CDataManager::getInstance();
	auto profile = m_pLayerData->m_pPlayer->getActorProfile();

	for (auto itr = mgr->getBoxData()->begin(); itr != mgr->getBoxData()->end(); itr++)
	{
		auto box = factory->CreateBox(this, m_pLayerData->m_pWorld, profile, *itr);
		m_pLayerData->m_arrObject.push_back(box);
	}

	for (auto itr = mgr->getMirageData()->begin(); itr != mgr->getMirageData()->end(); itr++)
	{
		auto mirage = factory->CreateMirage(this, m_pLayerData->m_pWorld, profile, *itr);
		m_pLayerData->m_arrObject.push_back(mirage);
	}

	for (auto itr = mgr->getWaterData()->begin(); itr != mgr->getWaterData()->end(); itr++)
	{
		auto water = factory->CreateWater(this, profile, *itr);
		m_pLayerData->m_arrObject.push_back(water);
	}

	for (auto itr = mgr->getSandData()->begin(); itr != mgr->getSandData()->end(); itr++)
	{
		auto sand = factory->CreateSand(this, m_pLayerData->m_pWorld, *itr);
		CObjectManager::getInstance()->getSandArray()->InsertObject(sand);
	}

	for (auto itr = mgr->getWindBoxData()->begin(); itr != mgr->getWindBoxData()->end(); itr++)
	{
		auto windBox = factory->CreateWindBox(this, m_pLayerData->m_pWorld, profile, *itr);
		m_pLayerData->m_arrObject.push_back(windBox);
		m_arrWindBox.push_back(windBox);
	}

	for (auto itr = mgr->getGroundData()->begin(); itr != mgr->getGroundData()->end(); itr++)
	{
		factory->CreateGround(this, m_pLayerData->m_pWorld, *itr);
	}

	scheduleUpdate();
}

void Stage3Object::update(float dt)
{
	for (auto itr = m_arrWindBox.begin(); itr != m_arrWindBox.end(); ++itr)
	{
		(*itr)->MakeFly(m_pLayerData->m_pPlayer.get());
	}
}