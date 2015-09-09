#pragma once
#include "SpannerBehaviorState.h"

class CSpannerDefaultState :
	public CSpannerBehaviorState
{
public :
	virtual bool Action(Vec2 a_TouchPos);
	virtual void Update();

public:
	CSpannerDefaultState();
	~CSpannerDefaultState();

private:
	virtual void BehaviorInit() override;
};

