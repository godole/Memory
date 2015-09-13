#include "Stage1Object.h"
#include "ObjectFactory.h"
#include "DataManager.h" 
#include "UpdateManager.h"
#include "Things.h"
#include "Rail.h"

void Stage1Object::LayerInit()
{
	auto factory = CObjectFactory::getInstance();
	auto mgr = CDataManager::getInstance();
	auto profile = m_pLayerData->m_pPlayer->getActorProfile();

	for (auto itr = mgr->getBoxData()->begin(); itr != mgr->getBoxData()->end(); itr++)
	{
		auto box = factory->CreateBox(this, m_pLayerData->m_pWorld, profile, *itr);
		m_pLayerData->m_arrObject.push_back(box);
	}

	for (auto itr = mgr->getGroundData()->begin(); itr != mgr->getGroundData()->end(); itr++)
	{
		factory->CreateGround(this, m_pLayerData->m_pWorld, *itr);
	}
}