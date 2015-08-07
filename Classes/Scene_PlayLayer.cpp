#include "Scene_PlayLayer.h"

PlayLayerShareData* Scene_PlayLayer::m_pLayerData = nullptr;

bool Scene_PlayLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	this->setTouchEnabled(true);
	LayerInit();
}