#include "Pulley.h"
#include "ScrollManager.h"
#include "LayerDefine.h"
#include "PulleyBehaviorState.h"
#include "PulleyDefaultState.h"
#include "PulleyRunState.h"
#include "ObjectManager.h"
#include "UpdateManager.h"
#include "Behavior.h"
#include "CTextureFactory.h"


CPulley::CPulley()
{
	m_fMoveSpeed = 50.0f;
}


CPulley::~CPulley()
{
}

void CPulley::Init(CCLayer* a_pParentLayer, b2World* a_World, PulleyData a_Data)
{
	m_drStartDirection = a_Data.m_eStartDirection;
	m_vStartPosition = a_Data.m_vPosition; 
	m_fStartLength = a_Data.m_fLength;
	m_fCurrentLength = a_Data.m_fLength;
	m_drCurrentDirection = e_drNULL;

	string objfileroot = "map/map2/object/";

	if (a_Data.m_eStartDirection == e_drUp)
	{
		m_pPulleyOnTexture = CTextureFactory::CreateTexture(objfileroot + "ped_elevator.png");
		m_pPulleyOffTexture = CTextureFactory::CreateTexture(objfileroot + "ped_elevator_off.png");
	}

	else if (a_Data.m_eStartDirection == e_drDown)
	{
		m_pPulleyOnTexture = CTextureFactory::CreateTexture(objfileroot + "ped_elevator_down.png");
		m_pPulleyOffTexture = CTextureFactory::CreateTexture(objfileroot + "ped_elevator_down_off.png");
	}

	m_pLeverOnTexture = CTextureFactory::CreateTexture(objfileroot + "lever_on.png");
	m_pLeverOffTexture = CTextureFactory::CreateTexture(objfileroot + "lever_off.png");

	for (int i = 0; i < a_Data.m_nPulleyCount; i++)
	{
		auto pulleySprite = CCSprite::createWithTexture(m_pPulleyOffTexture);
		a_pParentLayer->addChild(pulleySprite, OBJECT_ZORDER);

		auto box2dSprite = shared_ptr<CBox2dSprite>(new CBox2dSprite);
		box2dSprite->Init(pulleySprite, a_World, b2BodyType::b2_staticBody, 45, 45);

		m_parrPulleySprite.push_back(box2dSprite);
		CObjectManager::getInstance()->getBox2dSprite()->InsertObject(box2dSprite);
	}

	m_pLeverSprite = CCSprite::createWithTexture(m_pLeverOffTexture);
	m_pLeverSprite->setPosition(a_Data.m_vLeverPosition);
	a_pParentLayer->addChild(m_pLeverSprite, OBJECT_ZORDER);

	m_pBehavior = CreateBehavior();

	m_pActionSprite = m_pLeverSprite;
}

void CPulley::Scroll(Vec2 a_vScrollVelocity)
{
	for (int i = 0; i < m_parrPulleySprite.size(); i++)
	{
		m_parrPulleySprite[i]->setPositionBy(a_vScrollVelocity);
	}
	m_pLeverSprite->setPosition(m_pLeverSprite->getPosition() + a_vScrollVelocity);
}

void CPulley::ChangeState(shared_ptr<CPulleyBehaviorState> a_ptr)
{
	a_ptr->Init(this);

	m_pBehavior = a_ptr;
	m_pPulleyState = a_ptr;
}

void CPulley::setStateToDefault()
{
	ChangeState(shared_ptr<CPulleyDefaultState>(new CPulleyDefaultState));
}

shared_ptr<Behavior> CPulley::CreateBehavior()
{
	m_pPulleyState = shared_ptr<CPulleyDefaultState>(new CPulleyDefaultState);

	m_pPulleyState->Init(this);

	return m_pPulleyState;
}

void CPulley::ObjectUpdate()
{
	m_pPulleyState->Update();
}