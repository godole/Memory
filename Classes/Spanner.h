#pragma once
#include "Things.h"
#include "DataStructure.h"
#include "TransectorProfile.h"
#include <map>
#include <string>
#include <memory>

class CSpannerBehaviorState;
class CSpannerDefaultState;

class CSpanner :
	public CThings
{
public:
	void Init(cocos2d::CCLayer* parentLayer, TransectorProfile* profile, SpannerData data);
	void setStateToDefault() override;
	void ChangeState(shared_ptr<CSpannerBehaviorState> a_Ptr);

public:
	void Scroll(cocos2d::Vec2 a_vVelocity);

public:
	CSpanner();
	~CSpanner();

private:
	void Active() override;
	void DisActive() override;
	void ObjectUpdate() override;

	virtual shared_ptr<Behavior> CreateBehavior() override;

	std::map<std::string, void*> m_ValueMap;

	cocos2d::CCSprite* m_pSprite;

	std::shared_ptr<CSpannerBehaviorState> m_pState;
	CCPoint* m_vStartPosition;
};

