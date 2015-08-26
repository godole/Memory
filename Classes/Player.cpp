#include "Player.h"
#include "LayerDefine.h"
#include "Acting.h"
#include "SimpleAudioEngine.h"
#include "ObjectManager.h"
#include "Box2dSprite.h"
#include "Behavior.h"
#include "ParticleManager.h"
#include "ScrollManager.h"

using namespace CocosDenshion;



CPlayer::CPlayer()
{
	m_fSpeed = 2;
	m_fJumpPower = 7;
	m_bIsWalking = false;
	m_bIsOnGround = false;
	m_MoveEffectSoundIndex = 0;
}


CPlayer::~CPlayer()
{
}

void CPlayer::Init(CCLayer* parentLayer, b2World* a_World, int ZOrder)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	m_vStartPosition = ccp(50, 300);
	m_pParentLayer = parentLayer;

	m_pCharacter = CSLoader::createNode("char/run.csb");
	parentLayer->addChild(m_pCharacter);

	m_pRunAction = CSLoader::createTimeline("char/run.csb");
	m_pCharacter->runAction(m_pRunAction);

	m_pSprite = static_cast<CCSprite*>(m_pCharacter);

	m_pBodySprite = new CBox2dSprite;
	m_pBodySprite->Init(m_pSprite, a_World, b2BodyType::b2_dynamicBody, 80, 80);

	m_ActorProfile = new TransectorProfile();
	m_ActorProfile->m_vCurrentPosition = m_pSprite->getPosition();
	m_ActorProfile->m_vpHoldingPosition = &m_vHoldingPosition;

	m_pActing = new CActing();
	m_pActing->Init(m_pParentLayer);

	m_nRangeWidth = 500;
	m_nRangeHeight = 250;
}

void CPlayer::Move(MoveDirection dir)
{
	m_bIsWalking = true;
	
	switch (dir)
	{
	case md_Left :
		if (m_pBodySprite->getBodyStructure().body->GetLinearVelocity().x > -m_fSpeed)
			m_pBodySprite->getBodyStructure().body->ApplyForceToCenter(b2Vec2(-m_fSpeed * 7, 0), true);
		m_pSprite->setScaleX(-1.0f);
		break;

	case md_Right :
		if (m_pBodySprite->getBodyStructure().body->GetLinearVelocity().x < m_fSpeed)
			m_pBodySprite->getBodyStructure().body->ApplyForceToCenter(b2Vec2(m_fSpeed * 7, 0), true);
		m_pSprite->setScaleX(1.0f);
		break;
	}
}

void CPlayer::setPositionTo(CCPoint pos)
{
	m_pBodySprite->setPositionTo(pos);
}

void CPlayer::setPositionBy(CCPoint pos)
{
	m_pBodySprite->setPositionBy(pos);
}

void CPlayer::Update()
{
	auto objarr = CObjectManager::getInstance()->getBox2dSprite();
	float maxY = 0;
	CCRect charRect = m_pBodySprite->getBoundingBox();

	for (int i = 0; i < objarr->getSize(); i++)
	{
		auto obj = objarr->getObjectAt(i);
		CCRect objRect = obj->getBoundingBox();
		
		if (objRect.getMaxY() >charRect.getMinY())
			continue;

		if (objRect.getMaxX() > charRect.getMinX() &&
			objRect.getMinX() < charRect.getMaxX() &&
			objRect.getMaxY() > maxY)
		{
			maxY = objRect.getMaxY();
		}
	}

	m_bIsOnGround = charRect.getMinY() - 2 <= maxY ? true : false;

	_setActorPos();
}

void CPlayer::_setActorPos()
{
	m_vHoldingPosition.x = m_pSprite->getPositionX();
	m_vHoldingPosition.y = m_pSprite->getPositionY() + 80;

	m_ActorProfile->m_vCurrentPosition = m_pSprite->getPosition();

	m_ActorProfile->m_TransectRange.setRect(m_pSprite->getPositionX() - m_nRangeWidth / 2, m_pSprite->getPositionY() - m_nRangeHeight / 2,
		m_nRangeWidth, m_nRangeHeight);
}

void CPlayer::Jump(CCNode* a_pParent)
{
	if (m_bIsOnGround)
	{
		m_pBodySprite->getBodyStructure().body->SetLinearVelocity(b2Vec2(m_pBodySprite->getBodyStructure().body->GetLinearVelocity().x, 7.5));
		//CParticleManager::getInstance()->addParticle(a_pParent, "char/jump_smoke.plist", m_pSprite->getPosition() - Vec2(0, 45) - a_pParent->getPosition(), 2);
	}
}

void CPlayer::Scroll(Vec2 a_vScrollVelocity)
{
	setPositionBy(a_vScrollVelocity);
}

void CPlayer::Stop()
{
	m_bIsWalking = false;
	StopMoveAnimation();
	
}

void CPlayer::RunRail(EDirection dir)
{
	if (dir == EDirection::e_drLeft)
	{
		if (m_pBodySprite->getBodyStructure().body->GetLinearVelocity().x > -3)
			m_pBodySprite->getBodyStructure().body->ApplyForceToCenter(b2Vec2(-3 * 7, 0), true);
	}

	else if (dir == EDirection::e_drRight)
	{
		if (m_pBodySprite->getBodyStructure().body->GetLinearVelocity().x < 3)
			m_pBodySprite->getBodyStructure().body->ApplyForceToCenter(b2Vec2(3 * 7, 0), true);
	}
}

void CPlayer::Release()
{
	m_pSprite->stopAllActions();
}

bool CPlayer::Action(shared_ptr<Behavior> a_pBehavior, CCPoint a_Pos)
{
	return m_pActing->Acting(a_pBehavior, a_Pos);
}

void CPlayer::PlayMoveAnimation()
{
	if (!m_pRunAction->isPlaying())
	{
		m_pRunAction->gotoFrameAndPlay(0, true);
	}
	m_MoveEffectSoundIndex = SimpleAudioEngine::sharedEngine()->playEffect("music/step.wav", true);
}

void CPlayer::StopMoveAnimation()
{
	SimpleAudioEngine::sharedEngine()->stopEffect(m_MoveEffectSoundIndex);
	m_pRunAction->gotoFrameAndPause(16);
}

void CPlayer::setStateToBefore()
{
	m_pBodySprite->getBodyStructure().body->SetLinearVelocity(b2Vec2(0, 0));
	m_pBodySprite->setPositionTo(m_vStartPosition + CScrollManager::getInstance()->getDeltaPosition());

	m_pActing->setStateToDefault();

	delete m_pActing;

	m_pActing = new CActing;
	m_pActing->Init(m_pParentLayer);
}