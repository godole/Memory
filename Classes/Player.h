#pragma once
#include "cocos2d.h"
#include "MoveDirection.h"
#include "EDirection.h"
#include "ITransector.h"
#include "Update.h"
#include "IScroll.h"
#include "b2Structure.h"
#include "PhysicsDefine.h"
#include "TransectorProfile.h"

USING_NS_CC;

class Behavior;
class CActing;

class CPlayer :
	public IUpdate,
	public IScroll
{
public :	//IScroll
	virtual void		Scroll(Vec2 a_vScrollVelocity) override;

public :	//Update
	virtual void		Update() override;

public :
	void	Init(CCLayer* parentLayer, b2World* a_World, CCSprite* a_Sprite);
	void	setPositionTo(CCPoint pos);
	void	setPositionBy(CCPoint pos);
	void	Move(MoveDirection dir);
	void	PlayMoveSound();
	void	StopMoveSound();
	void	Stop();
	void	Jump();
	void	Release();
	void	RunRail(EDirection dir);
	bool	Action(CCLayer* a_pLayer, shared_ptr<Behavior> a_pBehavior, CCPoint a_Pos);

	Vec2	getPosition(){ return m_pBodySprite->getPosition(); }
	CCSprite* getBodySpritePtr(){ return m_pBodySprite; }
	TransectorProfile* getActorProfile(){ return m_ActorProfile; }

public:
	CPlayer();
	~CPlayer();

private :

	float			m_fSpeed;
	float			m_fJumpPower;
	bool			m_bIsOnGround;
	bool			m_bIsDoing;
	CCSprite*		m_pBodySprite;
	CCTimer*		m_pTimer;
	CCTexture2D*	m_parrWalkTexture[2];
	CCTexture2D*	m_pStandTexture;
	b2Structure		m_BodyStructure;

	CCPoint			m_vHoldingPosition;
	TransectorProfile* m_ActorProfile;
	CActing*		m_pActing;

	bool			m_bIsWalking;
	unsigned int	m_MoveEffectSoundIndex;

	int				m_nRangeWidth;
	int				m_nRangeHeight;

	void _setActorPos();
};

