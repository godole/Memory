#pragma once
#include "Behavior.h"
#include "cocos2d.h"
#include <map>
#include <string>

class CThings;

class CSpannerBehaviorState :
	public Behavior
{
public:
	virtual void Init(CThings* a_pObject, std::map<string, void* >* a_pValueMap) override;
	void setStateToDefault();
	std::string getIconFileName() override{ return "ui/motion.png"; }

public:
	CSpannerBehaviorState();
	~CSpannerBehaviorState();

protected:
	std::map<std::string, void* >* m_pValueMap;
	CThings* m_pObject;

	cocos2d::CCSprite* m_pSprite;
	cocos2d::CCPoint m_vStartPosition;
};


class CSpannerDefaultState :
	public CSpannerBehaviorState
{
public:
	virtual bool Action(Vec2 a_TouchPos);
	virtual void Update();

public:
	CSpannerDefaultState();
	~CSpannerDefaultState();

private:
	virtual void BehaviorInit() override;
};

class CSpannerHoldOnState :
	public CSpannerBehaviorState
{
public:
	virtual bool Action(Vec2 a_TouchPos);
	virtual void Update();

public:
	CSpannerHoldOnState();
	~CSpannerHoldOnState();

private:
	virtual void BehaviorInit() override;
};


class CSpannerUsedState :
	public CSpannerBehaviorState
{
public:
	virtual bool Action(Vec2 a_TouchPos);
	virtual void Update();

public:
	CSpannerUsedState();
	~CSpannerUsedState();

private:
	virtual void BehaviorInit() override;
};

