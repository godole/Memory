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
#include "Canfly.h" 
#include "Acting.h"

USING_NS_CC;
using namespace cocostudio;

class Behavior;
class CBox2dSprite;

class CPlayer :
	public IUpdate,
	public IScroll,
	public ICanfly
{
public :
	virtual void		Fly(cocos2d::Vec2 a_vVelocity) override;
	virtual cocos2d::CCRect getCanFlyRect() override;

public :	//IScroll
	virtual void		Scroll(Vec2 a_vScrollVelocity) override;

public :	//Update
	virtual void		Update() override;

public :
	void	Init(CCLayer* parentLayer, b2World* a_World, int a_nMaxBehaviorCount = 9, int ZOrder = 0);
	void	setPositionTo(CCPoint pos);
	void	setPositionBy(CCPoint pos);
	void	Move(MoveDirection dir);
	void	PlayMoveAnimation();
	void	StopMoveAnimation();
	void	Stop();
	void	Jump();
	void	setStateToBefore();
	void	Release();
	void	RunRail(EDirection dir);
	bool	Action(shared_ptr<Behavior> a_pBehavior, CCPoint a_Pos);

	Vec2	getPosition(){ return m_pSprite->getPosition(); }
	CCSprite* getBodySpritePtr(){ return m_pSprite; }
	TransectorProfile* getActorProfile(){ return m_ActorProfile; }

	int		getCurrentBehaviorCount(){ return m_pActing->getBehaviorCount(); }
	int		getMaxBehaviorCount(){ return m_pActing->getMaxBehaviorCount(); }
	int		getLatestCount(){ return m_pActing->getMaxBehaviorCount() - m_pActing->getBehaviorCount(); }
	bool	Isfall();

public:
	CPlayer();
	~CPlayer();

private :

	float			m_fSpeed;
	float			m_fJumpPower;
	bool			m_bIsOnGround;
	bool			m_bIsDoing;
	CCNode*			m_pCharacter;
	CCLayer*		m_pParentLayer;
	timeline::ActionTimeline*		m_pRunAction;
	CCSprite*		m_pSprite;
	CCTimer*		m_pTimer;
	CBox2dSprite*	m_pBodySprite;

	CCPoint			m_vHoldingPosition;
	CCPoint			m_vStartPosition;
	TransectorProfile* m_ActorProfile;
	CActing*		m_pActing;

	bool			m_bIsWalking;
	unsigned int	m_MoveEffectSoundIndex;

	int				m_nRangeWidth;
	int				m_nRangeHeight;

	void _setActorPos();
};

