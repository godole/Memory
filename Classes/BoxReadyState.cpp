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

	auto boxSprite = static_cast<CCSprite*>((*m_pValueMap)["readySprite"]);
	if (boxSprite->getBoundingBox().containsPoint(a_TouchPos))
	{
		k_bIsDoing = false;
		m_pBox->setBodyPositionTo(boxSprite->getPosition());
		auto parent = Director::getInstance()->getRunningScene()->getChildByName(OBJ_LAYER);
		parent->removeChild(boxSprite);
		CParticleManager::getInstance()->addParticle(parent, "object/box_put_effect.plist", boxSprite->getPosition(), 4);
		m_pBox->ChangeState(shared_ptr<CBoxBehaviorState>(new CBoxAfterState));
	}

	else if (IsPutable(boxSprite, a_TouchPos, setPos))
	{
		boxSprite->setPosition(setPos);
	}

	return false;
}

void CBoxReadyState::Update()
{

}

void CBoxReadyState::BehaviorInit()
{

}