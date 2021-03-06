#pragma once
#include "cocos2d.h"
#include <memory>

USING_NS_CC;
using namespace std;

class CThings;
class TransectorProfile;
class Behavior;

class CActing
{
public :
	void		Init(CCLayer* a_pParentLayer);
	bool		Acting(shared_ptr<Behavior> a_Behavior, CCPoint a_Pos);
	void		setStateToDefault();
	int			getBehaviorCount(){ return m_nBehaviorCount; }
	int			getMaxBehaviorCount(){ return m_nMaxBehaviorCount; }

public:
	CActing(int a_nMaxCount);
	~CActing();

private :
	void		CreateIcon(string filename );
	void		SortIcon();
	void		RemoveFirstMemory();
	void		RemoveAllMemory();

	shared_ptr<Behavior>		m_pCurrentBehavior;
	list<shared_ptr<Behavior>>	m_listBehavior;
	list<CCSprite*>		m_listBehaviorIcon;
	CCLayer*			m_pParentLayer;

	int					m_nBehaviorCount;
	int					m_nMaxBehaviorCount;
	bool				m_bIsDoing;
};

