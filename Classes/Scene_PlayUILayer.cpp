#include "Scene_PlayUILayer.h"
#include "CTextureFactory.h"

void Scene_PlayUILayer::LayerInit()
{
	m_pLeftButtonOn = CTextureFactory::CreateTexture("ui/left_on.png");
	m_pLeftButtonOff = CTextureFactory::CreateTexture("ui/left_off.png");
	m_pRightButtonOn = CTextureFactory::CreateTexture("ui/right_on.png");
	m_pRightButtonOff = CTextureFactory::CreateTexture("ui/right_off.png");
	m_pJumpButtonOn = CTextureFactory::CreateTexture("ui/jump_on.png");
	m_pJumpButtonOff = CTextureFactory::CreateTexture("ui/jump_off.png");

	m_pLeftMoveButton = CCSprite::createWithTexture(m_pLeftButtonOff);
	m_pLeftMoveButton->setPosition(Vec2(100, 80));
	this->addChild(m_pLeftMoveButton);

	m_pRightMoveButton = CCSprite::createWithTexture(m_pRightButtonOff);
	m_pRightMoveButton->setPosition(Vec2(185, 80));
	this->addChild(m_pRightMoveButton);

	m_pJumpButton = CCSprite::createWithTexture(m_pJumpButtonOff);
	m_pJumpButton->setPosition(Vec2(1100, 80));
	this->addChild(m_pJumpButton);

	m_pFilmSprite = CCSprite::create("ui/film.png");
	m_pFilmSprite->setPosition(ccp(200, 600));
	this->addChild(m_pFilmSprite);

	settingTouchDispatcher();
}

void Scene_PlayUILayer::onTouchesBegan(const vector<Touch*>&touches, Event* event)
{
	for (auto itr = touches.begin(); itr != touches.end(); itr++)
	{
		CCPoint touchPos = (*itr)->getLocation();

		if (m_pLeftMoveButton->boundingBox().containsPoint(touchPos))
		{
			m_pLeftMoveButton->setTexture(m_pLeftButtonOn);
			m_pLayerData->m_bIsLeftButtonTouched = true;
			m_pLayerData->m_pPlayer->PlayMoveSound();
		}

		if (m_pRightMoveButton->boundingBox().containsPoint(touchPos))
		{
			m_pRightMoveButton->setTexture(m_pRightButtonOn);
			m_pLayerData->m_bIsRightButtonTouched = true;
			m_pLayerData->m_pPlayer->PlayMoveSound();
		}

		if (m_pJumpButton->boundingBox().containsPoint(touchPos))
		{
			m_pLayerData->m_pPlayer->Jump();
			m_pJumpButton->setTexture(m_pJumpButtonOn);
			m_pLayerData->m_bIsJumpButtonTouched = true;
		}
	}
}

void Scene_PlayUILayer::onTouchesMoved(const vector<Touch*>&touches, Event* event)
{
	for (auto itr = touches.begin(); itr != touches.end(); itr++)
	{
		CCPoint touchPos = (*itr)->getLocation();

		if (m_pLeftMoveButton->boundingBox().containsPoint(touchPos))
		{
			m_pLeftMoveButton->setTexture(m_pLeftButtonOn);
			m_pLayerData->m_bIsLeftButtonTouched = true;
			m_pLayerData->m_pPlayer->PlayMoveSound();
		}
		else
		{
			m_pLeftMoveButton->setTexture(m_pLeftButtonOff);
			m_pLayerData->m_pPlayer->Stop();
			m_pLayerData->m_bIsLeftButtonTouched = false;
		}

		if (m_pRightMoveButton->boundingBox().containsPoint(touchPos))
		{
			m_pRightMoveButton->setTexture(m_pRightButtonOn);
			m_pLayerData->m_bIsRightButtonTouched = true;
			m_pLayerData->m_pPlayer->PlayMoveSound();
		}
		else
		{
			m_pRightMoveButton->setTexture(m_pRightButtonOff);
			m_pLayerData->m_pPlayer->Stop();
			m_pLayerData->m_bIsRightButtonTouched = false;
		}

		if (m_pJumpButton->boundingBox().containsPoint(touchPos))
		{
			m_pLayerData->m_pPlayer->Jump();
			m_pJumpButton->setTexture(m_pJumpButtonOn);
			m_pLayerData->m_bIsJumpButtonTouched = true;
		}
		else
		{
			m_pLayerData->m_bIsJumpButtonTouched = false;
			m_pJumpButton->setTexture(m_pJumpButtonOff);
		}
	}
}

void Scene_PlayUILayer::onTouchesEnded(const vector<Touch*>&touches, Event* event)
{
	for (auto itr = touches.begin(); itr != touches.end(); itr++)
	{
		CCPoint touchPos = (*itr)->getLocation();

		if (m_pLeftMoveButton->boundingBox().containsPoint(touchPos))
		{
			m_pLeftMoveButton->setTexture(m_pLeftButtonOff);
			m_pLayerData->m_pPlayer->Stop();
			m_pLayerData->m_bIsLeftButtonTouched = false;
		}

		if (m_pRightMoveButton->boundingBox().containsPoint(touchPos))
		{
			m_pRightMoveButton->setTexture(m_pRightButtonOff);
			m_pLayerData->m_pPlayer->Stop();
			m_pLayerData->m_bIsRightButtonTouched = false;
		}

		if (m_pJumpButton->boundingBox().containsPoint(touchPos))
		{
			m_pLayerData->m_bIsJumpButtonTouched = false;
			m_pJumpButton->setTexture(m_pJumpButtonOff);
		}
	}
}

void Scene_PlayUILayer::onTouchesCancelled(const vector<Touch*>&touches, Event* event)
{

}

void Scene_PlayUILayer::settingTouchDispatcher()
{
	auto listener = EventListenerTouchAllAtOnce::create();

	listener->onTouchesBegan = CC_CALLBACK_2(Scene_PlayUILayer::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(Scene_PlayUILayer::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(Scene_PlayUILayer::onTouchesEnded, this);
	listener->onTouchesCancelled = CC_CALLBACK_2(Scene_PlayUILayer::onTouchesCancelled, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}