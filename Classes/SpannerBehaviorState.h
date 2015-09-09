#pragma once
#include "Behavior.h"
#include "cocos2d.h"
#include <map>
#include <string>

class CSpanner;

class CSpannerBehaviorState :
	public Behavior
{
public :
	void Init(CSpanner* a_pThings, std::map<std::string, void* >* a_pValueMap);
	void setStateToDefault();
	std::string getIconFileName() override{ return "ui/motion.png"; }
	virtual void Update() = 0;

public:
	CSpannerBehaviorState();
	~CSpannerBehaviorState();

protected :
	std::map<std::string, void* >* m_pValueMap;
	CSpanner* m_pParent;

	cocos2d::CCSprite* m_pSprite;
	cocos2d::CCPoint m_vStartPosition;
};

