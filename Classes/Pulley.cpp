#include "Pulley.h"
#include "ScrollManager.h"
#include "LayerDefine.h"
#include "PulleyBehaviorState.h"
#include "PulleyDefaultState.h"
#include "PulleyRunState.h"
#include "ObjectManager.h"
#include "UpdateManager.h"
#include "Behavior.h"


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

	auto onimage = new CCImage;
	onimage->initWithImageFile(a_Data.m_szPulleyOnTextureName);
	m_pPulleyOnTexture = new CCTexture2D;
	m_pPulleyOnTexture->initWithImage(onimage);

	auto offimage = new CCImage;
	offimage->initWithImageFile(a_Data.m_szPulleyOffTextureName);
	m_pPulleyOffTexture = new CCTexture2D;
	m_pPulleyOffTexture->initWithImage(offimage);

	auto leveron = new CCImage;
	leveron->initWithImageFile(a_Data.m_szLeverOnTextureName);
	m_pLeverOnTexture = new CCTexture2D;
	m_pLeverOnTexture->initWithImage(leveron);

	auto leveroff = new CCImage;
	leveroff->initWithImageFile(a_Data.m_szLeverOffTextureName);
	m_pLeverOffTexture = new CCTexture2D;
	m_pLeverOffTexture->initWithImage(leveroff);

	auto pulleySprite = CCSprite::createWithTexture(m_pPulleyOffTexture);
	a_pParentLayer->addChild(pulleySprite, OBJECT_ZORDER);

	m_pPulleySprite = pulleySprite;

	m_pBodySprite = shared_ptr<CBox2dSprite>(new CBox2dSprite);
	m_pBodySprite->Init(pulleySprite, a_World, b2BodyType::b2_staticBody);

	CObjectManager::getInstance()->getBox2dSprite()->InsertObject(m_pBodySprite);

	m_pBody = m_pBodySprite->getBodyStructure().body;

	m_pLeverSprite = CCSprite::createWithTexture(m_pLeverOffTexture);
	m_pLeverSprite->setPosition(a_Data.m_vLeverPosition);
	a_pParentLayer->addChild(m_pLeverSprite, OBJECT_ZORDER);

	m_pBehavior = CreateBehavior();

	m_pActionSprite = m_pLeverSprite;
}

void CPulley::Scroll(Vec2 a_vScrollVelocity)
{
	setBodyPositionBy(a_vScrollVelocity);
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