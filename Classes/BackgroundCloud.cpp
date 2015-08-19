#include "BackgroundCloud.h"
#include "ScrollSprite.h"
#include "ScrollManager.h"

USING_NS_CC;

BackgroundCloud::BackgroundCloud()
{
	m_fSpeed = 0;
	m_nMaxWidth = 0;
}


BackgroundCloud::~BackgroundCloud()
{
}

void BackgroundCloud::Init(float a_fSpeed, int a_nMaxWidth)
{
	m_fSpeed = a_fSpeed;
	m_nMaxWidth = a_nMaxWidth;
}

CCSprite* BackgroundCloud::InsertCloud(std::string filename, cocos2d::CCPoint a_Pos)
{
	auto cloudTexture = CCSprite::create(filename);
	cloudTexture->setPosition(ccp(random(100, 1500), random(600, 900)));

	auto cloud = shared_ptr<CScrollSprite>(new CScrollSprite);
	cloud->Init(cloudTexture);

	m_arrCloud.push_back(cloud);
	CScrollManager::getInstance()->Insert(cloud);

	return cloudTexture;
}

void BackgroundCloud::Update()
{
	for (int i = 0; i < m_arrCloud.size(); i++)
	{
		auto cloud = m_arrCloud[i]->getSpritePtr();
		cloud->setPositionX(cloud->getPositionX() - m_fSpeed);
		if (cloud->getPositionX() <= 0 - cloud->getContentSize().width)
		{
			cloud->setPositionX(cloud->getContentSize().width + m_nMaxWidth + CScrollManager::getInstance()->getDeltaPosition().x);
		}
	}
}