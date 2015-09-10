#include "BoxReadyState.h"
#include "LayerDefine.h"
#include "ParticleManager.h"
#include "BoxAfterState.h"


CBoxReadyState::CBoxReadyState()
{
}


CBoxReadyState::~CBoxReadyState()
{
}

bool CBoxReadyState::Action(Vec2 a_TouchPos)
{
	//treeEffect->runAction(CCRepeatForever::create(CCSequence::create((CCFiniteTimeAction*)CCScaleTo::create(randomTime, 0.8), CCScaleTo::create(randomTime, 1.2), NULL)));
	CCPoint setPos;
	bool bIsEnable = IsPutable(static_cast<TransectorProfile*>((*m_pValueMap)["profile"]), static_cast<CCSprite*>((*m_pValueMap)["bodySprite"]), a_TouchPos, setPos);

	auto sprite = static_cast<CCSprite*>((*m_pValueMap)["readySprite"]);
	if (sprite->getBoundingBox().containsPoint(a_TouchPos) && bIsEnable)
	{
		k_bIsDoing = false;
		m_pBox->setBodyPositionTo(sprite->getPosition());
		auto parent = Director::getInstance()->getRunningScene()->getChildByTag( MAIN_LAYER)->getChildByTag(OBJ_PARTICLE_NODE);
		CParticleManager::getInstance()->addParticle(parent, "object/box_put_effect.plist", sprite->getPosition(), PARTICLE_ZORDER);
		auto spriteParent = Director::getInstance()->getRunningScene()->getChildByTag(MAIN_LAYER);
		spriteParent->removeChild(sprite);
		(*m_pValueMap)["readySprite"] = nullptr;
		m_pBox->ChangeState(shared_ptr<CBoxBehaviorState>(new CBoxAfterState));
	}

	else if (bIsEnable)
	{
		sprite->setPosition(setPos);
	}

	return false;
}

void CBoxReadyState::Update()
{
	CCPoint holdPos = *(CCPoint*)(*m_pValueMap)["holdPosition"];
	m_pBox->setBodyPositionTo(holdPos);
}

void CBoxReadyState::BehaviorInit()
{

}