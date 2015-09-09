#pragma once
#include "SpannerBehaviorState.h"

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

