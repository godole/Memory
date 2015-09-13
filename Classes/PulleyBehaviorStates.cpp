#include "PulleyBehaviorStates.h"
#include "EDirection.h"
#include "PhysicsDefine.h"
#include "Things.h"
#include "Box2dSprite.h"
#include "ScrollManager.h"
#include "ObjectManager.h"
#include "LayerDefine.h"


void CPulleyBehaviorState::Init(CThings* a_pObject, std::map<string, void* >* a_pValueMap)
{
	m_pObject = a_pObject;
	m_pValueMap = a_pValueMap;

	m_pLeverSprite = _VMAP_STATIC_CAST(CCSprite*, "leverSprite");
	m_parPed = _VMAP_STATIC_CAST(vector<shared_ptr<CBox2dSprite>>*, "arrPed");
	m_pData = _VMAP_STATIC_CAST(PulleyProfile*, "pulleyProfile");

	BehaviorInit();
}

void CPulleyBehaviorState::setStateToDefault()
{
	m_pObject->ChangeState(shared_ptr<CPulleyBehaviorState>(new CPulleyDefaultState));
}

string CPulleyBehaviorState::getIconFileName()
{
	return string("ui/motion_ele.png");
}



void CPulleyDefaultState::BehaviorInit()
{
	m_pData->m_drCurrentDirection = EDirection::e_drNULL;
	m_pData->m_fCurrentLength = m_pData->m_fStartLength;
	m_pLeverSprite->setTexture(_VMAP_STATIC_CAST(CCTexture2D*, "leverOffTexture"));

	for (int i = 0; i < m_parPed->size(); i++)
	{
		m_parPed->at(i)->getSpritePtr()->setTexture(_VMAP_STATIC_CAST(CCTexture2D*, "pedOffTexture"));
		m_parPed->at(i)->setPositionTo(ccp(m_pData->m_vStartPosition.x +
			m_parPed->at(i)->getSpritePtr()->getContentSize().width * i, m_pData->m_vStartPosition.y) +
			CScrollManager::getInstance()->getDeltaPosition());
		m_parPed->at(i)->getBodyStructure().body->SetType(b2BodyType::b2_staticBody);
	}
}

bool CPulleyDefaultState::Action(CCPoint a_vPos)
{
	if (m_pLeverSprite->getBoundingBox().containsPoint(a_vPos) &&
		!k_bIsDoing &&
		m_pObject->getIsRanged())
	{
		m_pObject->ChangeState(shared_ptr<CPulleyBehaviorState>(new CPulleyRunState));
		return true;
	}
	else
		return false;
}


bool CPulleyRunState::Action(CCPoint a_vPos)
{
	return false;
}

void CPulleyRunState::Update()
{
	bool bIsRunable = true;
	auto charSprite = Director::getInstance()->getRunningScene()->getChildByTag(MAIN_LAYER)->getChildByTag(CHAR_NODE);
	auto boxarr = CObjectManager::getInstance()->getBox2dSprite()->getObjectArray();
	CCRect r;
	r.setRect(m_parPed->at(0).get()->getSpritePtr()->getBoundingBox().getMinX(), m_parPed->at(0).get()->getSpritePtr()->getBoundingBox().getMinY(),
		m_parPed->size() * 75, 125);
	CCRect r2;
	r2.setRect(charSprite->getPositionX() - 45, charSprite->getPositionY() , 80, 70);

	for (auto itr1 = boxarr.begin(); itr1 != boxarr.end(); ++itr1)
	{
		for (auto itr2 = m_parPed->begin(); itr2 != m_parPed->end(); ++itr2)
		{
			if (itr1->get() == itr2->get())
				itr1 = boxarr.erase(itr1);
		}
	}

	for (auto itr = boxarr.begin(); itr != boxarr.end(); ++itr)
	{
		if (itr->get()->getBoundingBox().intersectsRect(r) ||
			(itr->get()->getBoundingBox().intersectsRect(r2) &&
			r.intersectsRect(r2)))
			bIsRunable = false;
	}

	if (m_pData->m_fCurrentLength < 0 ||
		!bIsRunable)
	{
		for (int i = 0; i < m_parPed->size(); i++)
		{
			m_parPed->at(i)->getBodyStructure().body->SetLinearVelocity(ChangeVecTob2Vec2(Vec2::ZERO));
		}
	}
	else
		m_pData->m_fCurrentLength -= m_pData->m_fMoveSpeed / PTM_RATIO;
}

void CPulleyRunState::BehaviorInit()
{
	m_pData->m_drCurrentDirection = m_pData->m_drStartDirection;
	m_pLeverSprite->setTexture(_VMAP_STATIC_CAST(CCTexture2D*, "leverOnTexture"));

	for (int i = 0; i < m_parPed->size(); i++)
	{
		auto pulleySprite = m_parPed->at(i);
		auto body = pulleySprite->getBodyStructure().body;
		pulleySprite->getSpritePtr()->setTexture(_VMAP_STATIC_CAST(CCTexture2D*, "pedOnTexture"));
		body->SetType(b2BodyType::b2_dynamicBody);
		body->SetGravityScale(0);

		b2MassData massdata;
		massdata.mass = 100000;
		massdata.center = body->GetWorldCenter();
		body->SetMassData(&massdata);

		if (m_pData->m_drCurrentDirection == EDirection::e_drUp)
		{
			body->SetLinearVelocity(ChangeVecTob2Vec2(Vec2(0, m_pData->m_fMoveSpeed)));
		}

		else if (m_pData->m_drCurrentDirection == EDirection::e_drDown)
		{
			body->SetLinearVelocity(ChangeVecTob2Vec2(Vec2(0, -m_pData->m_fMoveSpeed)));
		}
	}
}