#include "BoxBehaviorStates.h"
#include "ObjectManager.h"
#include "Box2dSprite.h"
#include "ParticleManager.h"
#include "LayerDefine.h"
#include "Things.h"



void CBoxBehaviorState::Init(CThings* a_pObject, std::map<string, void* >* a_pValueMap)
{
	m_pObject = a_pObject;
	m_pValueMap = a_pValueMap;

	m_pBoxSprite = _VMAP_STATIC_CAST(CCSprite*, "sprite");
	m_pBoxBodySprite = _VMAP_STATIC_CAST(CBox2dSprite*, "bodySprite");
	m_pPlayerProfile = _VMAP_STATIC_CAST(TransectorProfile*, "profile");

	BehaviorInit();
}

void CBoxBehaviorState::setStateToDefault()
{
	m_pObject->ChangeState(shared_ptr<CBoxBehaviorState>(new CBoxDefaultState));
}

bool CBoxBehaviorState::IsPutable(TransectorProfile* profile, CCSprite* sprite, CCPoint touchPos, CCPoint& avaliablePos)
{
	auto arr = CObjectManager::getInstance()->getNotBoxArray();
	CCPoint setPos;
	bool bIsEnable = true;
	CCRect rect;

	for (int i = 0; i <= 20; i++)
	{
		for (int j = 0; j <= 20; j++)
		{
			CCRect r;
			r.setRect(i * 100 + CScrollManager::getInstance()->getDeltaPosition().x, j * 100 + CScrollManager::getInstance()->getDeltaPosition().y, 100, 100);

			if (r.containsPoint(touchPos))
			{
				setPos = ccp(r.getMidX(), r.getMidY());
				rect = r;
			}
		}
	}

	for (int i = 0; i < arr->getSize(); i++)
	{
		auto anothersprite = arr->getObjectAt(i);

		if (anothersprite->getSpritePtr() == sprite)
			continue;

		if (rect.intersectsRect(anothersprite->getBoundingBox()))
			bIsEnable = false;
	}

	if (!profile->m_TransectRange.containsPoint(touchPos))
		bIsEnable = false;

	avaliablePos = setPos;
	return bIsEnable;
}



bool CBoxDefaultState::Action(Vec2 a_TouchPos)
{
	if (!k_bIsDoing &&
		m_pBoxSprite->getBoundingBox().containsPoint(a_TouchPos) &&
		m_pObject->getIsRanged())
	{
		m_pObject->ChangeState(std::shared_ptr<CBoxBehaviorState>(new CBoxHoldOnState));
		k_bIsDoing = true;
		return true;
	}
	else
		return false;
}


void CBoxDefaultState::BehaviorInit()
{
	CCPoint* startPos = _VMAP_STATIC_CAST(CCPoint*, "startPosition");
	m_pBoxBodySprite->getBodyStructure().body->SetActive(true);
	m_pBoxBodySprite->setPositionTo(*startPos + CScrollManager::getInstance()->getDeltaPosition());
	m_pBoxSprite->setZOrder(OBJECT_ZORDER);
	if ((*m_pValueMap)["readySprite"] != nullptr)
	{
		auto parent = Director::getInstance()->getRunningScene()->getChildByTag(MAIN_LAYER);
		parent->removeChild(_VMAP_STATIC_CAST(CCSprite*, "readySprite"));
		(*m_pValueMap)["readySprite"] = nullptr;
	}
}


bool CBoxHoldOnState::Action(Vec2 a_TouchPos)
{
	CCPoint setPos;
	bool bIsEnable = IsPutable(m_pPlayerProfile, m_pBoxSprite, a_TouchPos, setPos);

	if (bIsEnable)
	{
		//treeEffect->runAction(CCRepeatForever::create(CCSequence::create((CCFiniteTimeAction*)CCScaleTo::create(randomTime, 0.8), CCScaleTo::create(randomTime, 1.2), NULL)));
		auto filename = _VMAP_STATIC_CAST(string*, "spriteName");
		auto sprite = CCSprite::create(*filename);
		auto parent = Director::getInstance()->getRunningScene()->getChildByTag(MAIN_LAYER);
		parent->addChild(sprite);
		(*m_pValueMap)["readySprite"] = sprite;
		sprite->setPosition(setPos);
		m_pObject->ChangeState(shared_ptr<CBoxBehaviorState>(new CBoxReadyState));
	}

	auto parent = Director::sharedDirector()->getRunningScene()->getChildByTag(2);

	return false;
}

void CBoxHoldOnState::Update()
{
	m_pBoxBodySprite->setPositionTo(*m_pPlayerProfile->m_vpHoldingPosition);
}

void CBoxHoldOnState::BehaviorInit()
{
	m_pBoxBodySprite->getBodyStructure().body->SetActive(false);
	m_pBoxSprite->setZOrder(BOX_HOLD_ZORDER);
}




bool CBoxReadyState::Action(Vec2 a_TouchPos)
{
	//treeEffect->runAction(CCRepeatForever::create(CCSequence::create((CCFiniteTimeAction*)CCScaleTo::create(randomTime, 0.8), CCScaleTo::create(randomTime, 1.2), NULL)));
	CCPoint setPos;
	bool bIsEnable = IsPutable(m_pPlayerProfile, m_pBoxSprite, a_TouchPos, setPos);

	auto sprite = _VMAP_STATIC_CAST(CCSprite*, "readySprite");
	if (sprite->getBoundingBox().containsPoint(a_TouchPos) && bIsEnable)
	{
		k_bIsDoing = false;
		m_pBoxBodySprite->setPositionTo(sprite->getPosition());
		auto parent = Director::getInstance()->getRunningScene()->getChildByTag(MAIN_LAYER)->getChildByTag(OBJ_PARTICLE_NODE);
		CParticleManager::getInstance()->addParticle(parent, "object/box_put_effect.plist", sprite->getPosition() - CScrollManager::getInstance()->getDeltaPosition(), PARTICLE_ZORDER);
		auto spriteParent = Director::getInstance()->getRunningScene()->getChildByTag(MAIN_LAYER);
		spriteParent->removeChild(sprite);
		(*m_pValueMap)["readySprite"] = nullptr;
		m_pObject->ChangeState(shared_ptr<CBoxBehaviorState>(new CBoxAfterState));
	}

	else if (bIsEnable)
	{
		sprite->setPosition(setPos);
	}

	return false;
}

void CBoxReadyState::Update()
{
	m_pBoxBodySprite->setPositionTo(*m_pPlayerProfile->m_vpHoldingPosition);
}

void CBoxReadyState::BehaviorInit()
{

}



bool CBoxAfterState::Action(Vec2 a_TouchPos)
{
	return false;
}

void CBoxAfterState::BehaviorInit()
{
	m_pBoxBodySprite->getBodyStructure().body->SetActive(true);
}