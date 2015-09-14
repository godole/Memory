#include "Pulley.h"
#include "ScrollManager.h"
#include "LayerDefine.h"
#include "PulleyBehaviorStates.h"
#include "ObjectManager.h"
#include "UpdateManager.h"
#include "Behavior.h"
#include "CTextureFactory.h"
#include "Box2dSprite.h"


CPulley::CPulley()
{
	m_DataProfile.m_fMoveSpeed = 50.0f;
}


CPulley::~CPulley()
{
}

void CPulley::Init(CCLayer* a_pParentLayer, b2World* a_World, PulleyData a_Data)
{
	m_DataProfile.m_drStartDirection = a_Data.m_eStartDirection;
	m_DataProfile.m_vStartPosition = a_Data.m_vPosition; 
	m_DataProfile.m_fStartLength = a_Data.m_fLength;
	m_DataProfile.m_fCurrentLength = a_Data.m_fLength;
	m_DataProfile.m_drCurrentDirection = e_drNULL;

	string objfileroot = "map/map2/object/";

	CCTexture2D* onTexture;
	CCTexture2D* offTexture;
	CCTexture2D* lonTexture;
	CCTexture2D* loffTexture;

	if (a_Data.m_eStartDirection == e_drUp)
	{
		onTexture = CTextureFactory::CreateTexture(objfileroot + "ped_elevator.png");
		offTexture = CTextureFactory::CreateTexture(objfileroot + "ped_elevator_off.png");
	}

	else if (a_Data.m_eStartDirection == e_drDown)
	{
		onTexture = CTextureFactory::CreateTexture(objfileroot + "ped_elevator_down.png");
		offTexture = CTextureFactory::CreateTexture(objfileroot + "ped_elevator_down_off.png");
	}

	lonTexture = CTextureFactory::CreateTexture(objfileroot + "lever_on.png");
	loffTexture = CTextureFactory::CreateTexture(objfileroot + "lever_off.png");

	for (int i = 0; i < a_Data.m_nPulleyCount; i++)
	{
		auto pulleySprite = CCSprite::createWithTexture(offTexture);
		a_pParentLayer->addChild(pulleySprite, OBJECT_ZORDER);

		auto box2dSprite = shared_ptr<CBox2dSprite>(new CBox2dSprite);
		box2dSprite->Init(pulleySprite, a_World, b2BodyType::b2_staticBody, 75, 75);

		m_parrPulleySprite.push_back(box2dSprite);
		CObjectManager::getInstance()->getBox2dSprite()->InsertObject(box2dSprite);
		CObjectManager::getInstance()->getNotBoxArray()->InsertObject(box2dSprite);
	}

	m_pActionSprite = CCSprite::createWithTexture(loffTexture);
	m_pActionSprite->setPosition(a_Data.m_vLeverPosition);
	a_pParentLayer->addChild(m_pActionSprite, OBJECT_ZORDER);

	m_ValueMap["leverSprite"] = m_pActionSprite;
	m_ValueMap["pedOnTexture"] = onTexture;
	m_ValueMap["pedOffTexture"] = offTexture;
	m_ValueMap["leverOnTexture"] = lonTexture;
	m_ValueMap["leverOffTexture"] = loffTexture;
	m_ValueMap["arrPed"] = &m_parrPulleySprite;
	m_ValueMap["pulleyProfile"] = &m_DataProfile;

	m_pBehavior = shared_ptr<CPulleyDefaultState>(new CPulleyDefaultState);
	m_pBehavior->Init(this, &m_ValueMap);
}

void CPulley::Scroll(Vec2 a_vScrollVelocity)
{
	for (int i = 0; i < m_parrPulleySprite.size(); i++)
	{
		m_parrPulleySprite[i]->setPositionBy(a_vScrollVelocity);
	}
	m_pActionSprite->setPosition(m_pActionSprite->getPosition() + a_vScrollVelocity);
}

void CPulley::setStateToDefault()
{
	ChangeState(shared_ptr<CPulleyDefaultState>(new CPulleyDefaultState));
}