#include "Stage2Background.h"
#include "ScrollSprite.h"
#include "ScrollManager.h"
#include <memory>

using namespace std;


void Stage2Background::LayerInit()
{
	auto background = CCSprite::create("map/map2/background/map_2_full.png");
	background->setAnchorPoint(ccp(0, 0));
	this->addChild(background, 0);

	m_pLayerData->m_pBackground = shared_ptr<CScrollSprite>(new CScrollSprite);
	m_pLayerData->m_pBackground->Init(background);
	CScrollManager::getInstance()->Insert(m_pLayerData->m_pBackground);
}