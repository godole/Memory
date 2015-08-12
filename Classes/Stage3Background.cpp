#include "Stage3Background.h"
#include "ScrollSprite.h"
#include "ScrollManager.h"


void Stage3Background::LayerInit()
{
	auto backgroundSprite = CCSprite::create("map/map3/background/map_3.png");
	backgroundSprite->setAnchorPoint(ccp(0, 0));
	this->addChild(backgroundSprite, 0);

	shared_ptr<CScrollSprite> background = shared_ptr<CScrollSprite>(new CScrollSprite);
	background->Init(backgroundSprite);

	CScrollManager::getInstance()->Insert(background);

	m_pLayerData->m_pBackground = background;
}