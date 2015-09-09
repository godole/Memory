#pragma once
#include "SpannerBehaviorState.h"

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

