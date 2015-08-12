#pragma once
#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "MoveDirection.h"
#include "EDirection.h"
#include "ITransector.h"
#include "Update.h"
#include "IScroll.h"
#include "b2Structure.h"
#include "PhysicsDefine.h"
#include "TransectorProfile.h"

USING_NS_CC;
using namespace cocostudio;

class Behavior;
class CActing;
class CBox2dSprite;

class CPlayer :
	public IUpdate,
	public IScroll
{
public :	//IScroll
	virtual void		Scroll(Vec2 a_vScrollVelocity) override;

public :	//Update
	virtual void		Update() override;

public :
	void	Init(CCLayer* parentLayer, b2World* a_World, int ZOrder = 0);
	void	setPositionTo(CCPoint pos);
	void	setPositionBy(CCPoint pos);
	void	Move(MoveDirection dir);
	void	PlayMoveAnimation();
	void	StopMoveAnimation();
	void	Stop();
	void	Jump(CCNode* a_pParticleParent);
	void	Release();
	void	RunRail(EDirection dir);
	bool	Action(CCLayer* a_pLayer, shared_ptr<Behavior> a_pBehavior, CCPoint a_Pos);

	Vec2	getPosition(){ return m_pSprite->getPosition(); }
	CCSprite* getBodySpritePtr(){ return m_pSprite; }
	TransectorProfile* getActorProfile(){ return m_ActorProfile; }

public:
	CPlayer();
	~CPlayer();

private :

	float			m_fSpeed;
	float			m_fJumpPower;
	bool			m_bIsOnGround;
	bool			m_bIsDoing;
	CCNode*			m_pCharacter;
	timeline::ActionTimeline*		m_pRunAction;
	CCSprite*		m_pSprite;
	CCTimer*		m_pTimer;
	CBox2dSprite*	m_pBodySprite;

	CCPoint			m_vHoldingPosition;
	TransectorProfile* m_ActorProfile;
	CActing*		m_pActing;

	bool			m_bIsWalking;
	unsigned int	m_MoveEffectSoundIndex;

	int				m_nRangeWidth;
	int				m_nRangeHeight;

	void _setActorPos();
};

