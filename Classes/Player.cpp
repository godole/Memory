#include "Player.h"
#include "LayerDefine.h"
#include "Acting.h"
#include "SimpleAudioEngine.h"
#include "ObjectManager.h"
#include "Box2dSprite.h"
#include "Behavior.h"

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

void CPlayer::Init(CCLayer* parentLayer, b2World* a_World, CCSprite* a_Sprite)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto standimage = new CCImage;
	standimage->initWithImageFile("char/box_stand.png");

	m_pStandTexture = new CCTexture2D;
	m_pStandTexture->initWithImage(standimage);

	m_pBodySprite = a_Sprite;
	m_pBodySprite->setPosition(ccp(m_pBodySprite->getContentSize().width / 2, m_pBodySprite->getContentSize().height / 2));

	m_BodyStructure = CreateDynamicStructure(a_World, a_Sprite);
	m_BodyStructure.bodyDef.allowSleep = false;
	m_BodyStructure.bodyDef.fixedRotation = true;

	parentLayer->addChild(m_pBodySprite, CHARACTER_ZORDER);

	auto walk1 = new CCImage;
	walk1->initWithImageFile("char/box_1.png");

	m_parrWalkTexture[0] = new CCTexture2D;
	m_parrWalkTexture[0]->initWithImage(walk1);

	auto walk2 = new CCImage;
	walk2->initWithImageFile("char/box_2.png");

	m_parrWalkTexture[1] = new CCTexture2D;
	m_parrWalkTexture[1]->initWithImage(walk2);

	m_ActorProfile = new TransectorProfile();
	m_ActorProfile->m_vCurrentPosition = m_pBodySprite->getPosition();
	m_ActorProfile->m_vpHoldingPosition = &m_vHoldingPosition;

	m_pActing = new CActing();

	m_nRangeWidth = 500;
	m_nRangeHeight = 250;
}

void CPlayer::Move(MoveDirection dir)
{
	//¼öÁ¤ÇØ¾ßµÊ
	m_bIsWalking = true;
	
	switch (dir)
	{
	case md_Left :
		if (m_BodyStructure.body->GetLinearVelocity().x > -m_fSpeed)
			m_BodyStructure.body->ApplyForceToCenter(b2Vec2(-m_fSpeed * 7, 0), true);
		m_pBodySprite->setFlipX(true);
		break;

	case md_Right :
		if (m_BodyStructure.body->GetLinearVelocity().x < m_fSpeed)
			m_BodyStructure.body->ApplyForceToCenter(b2Vec2(m_fSpeed * 7, 0), true);
		m_pBodySprite->setFlipX(false);
		break;
	}
}

void CPlayer::setPositionTo(CCPoint pos)
{
	m_BodyStructure.body->SetTransform(ChangeVecTob2Vec2(pos), 0);
}

void CPlayer::setPositionBy(CCPoint pos)
{
	m_BodyStructure.body->SetTransform(m_BodyStructure.body->GetTransform().p + ChangeVecTob2Vec2(pos), 0);
}

void CPlayer::Update()
{	
	/*if (m_bIsJumping)
	{
		if ((m_iRigidBody->getBottomY()) == (m_iRigidBody->getFloatY()))
		{
			m_bIsJumping = false;
		}
		else
			m_iRigidBody->setPositionYBy(m_fJumpPower);
	}*/

	static int i = 0;
	static int j = 0;
	if (m_bIsWalking)
		i++;
	if (i > 10)
	{
		j++;
		i = 0;
		m_pBodySprite->setTexture(m_parrWalkTexture[j % 2]);
	}

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
	m_vHoldingPosition.x = m_pBodySprite->getPositionX();
	m_vHoldingPosition.y = m_pBodySprite->getPositionY() + m_pBodySprite->getContentSize().height;

	m_ActorProfile->m_vCurrentPosition = m_pBodySprite->getPosition();

	m_ActorProfile->m_TransectRange.setRect(m_pBodySprite->getPositionX() - m_nRangeWidth / 2, m_pBodySprite->getPositionY() - m_nRangeHeight / 2,
		m_nRangeWidth, m_nRangeHeight);
}

void CPlayer::Jump()
{
	if (m_bIsOnGround)
	{
		m_BodyStructure.body->SetLinearVelocity(b2Vec2(m_BodyStructure.body->GetLinearVelocity().x, 7.5));
	}
}

void CPlayer::Scroll(Vec2 a_vScrollVelocity)
{
	setPositionBy(a_vScrollVelocity);
}

void CPlayer::Stop()
{
	m_pBodySprite->setTexture(m_pStandTexture);
	m_bIsWalking = false;
	StopMoveSound();
}

void CPlayer::RunRail(EDirection dir)
{
	if (dir == EDirection::e_drLeft)
	{
		if (m_BodyStructure.body->GetLinearVelocity().x > -3)
			m_BodyStructure.body->ApplyForceToCenter(b2Vec2(-3 * 7, 0), true);
	}

	else if (dir == EDirection::e_drRight)
	{
		if (m_BodyStructure.body->GetLinearVelocity().x < 3)
			m_BodyStructure.body->ApplyForceToCenter(b2Vec2(3 * 7, 0), true);
	}
}

void CPlayer::Release()
{
	m_pBodySprite->stopAllActions();
}

bool CPlayer::Action(CCLayer* a_pLayer, shared_ptr<Behavior> a_pBehavior, CCPoint a_Pos)
{
	return m_pActing->Acting(a_pLayer, a_pBehavior, a_Pos);
}

void CPlayer::PlayMoveSound()
{
	m_MoveEffectSoundIndex = SimpleAudioEngine::sharedEngine()->playEffect("music/step.wav", true);
}

void CPlayer::StopMoveSound()
{
	SimpleAudioEngine::sharedEngine()->stopEffect(m_MoveEffectSoundIndex);
}
