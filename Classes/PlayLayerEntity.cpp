#include "PlayLayerEntity.h"

PlayLayerShareData* PlayLayerEntity::m_pLayerData = nullptr;

bool PlayLayerEntity::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	this->setTouchEnabled(true);
	LayerInit();

	return true;
}