#include "BoxHoldOnState.h"
#include "BoxReadyState.h"
#include "ObjectManager.h"
#include "Box2dSprite.h"
#include "UpdateManager.h"
#include "ScrollManager.h"
#include "ParticleManager.h"
#include "LayerDefine.h"
#include <memory>

bool CBoxHoldOnState::Action(Vec2 a_TouchPos)
{
	CCPoint setPos;
	bool bIsEnable = IsPutable(m_pBox->m_pBoxSprite, a_TouchPos, setPos);

	if (bIsEnable)
	{
		//treeEffect->runAction(CCRepeatForever::create(CCSequence::create((CCFiniteTimeAction*)CCScaleTo::create(randomTime, 0.8), CCScaleTo::create(randomTime, 1.2), NULL)));
//		auto filename = static_cast<string*>((*m_pValueMap)["spriteName"]);
		auto sprite = CCSprite::create("map/map1/object/box_ob.png");
		auto parent = Director::getInstance()->getRunningScene()->getChildByName(OBJ_LAYER);
		parent->addChild(sprite);
		(*m_pValueMap)["readySprite"] = sprite;
		sprite->setPosition(setPos);
		m_pBox->ChangeState(shared_ptr<CBoxBehaviorState>(new CBoxReadyState));
	}

	auto parent = Director::sharedDirector()->getRunningScene()->getChildByTag(2);

	return false;
}

void CBoxHoldOnState::Update()
{
	m_pBox->setBodyPositionTo(*m_pBox->m_pTransProfile->m_vpHoldingPosition);
}

void CBoxHoldOnState::BehaviorInit()
{
	m_pBox->m_pBody->SetActive(false);
	m_pBox->m_pBoxSprite->setZOrder(3);
}