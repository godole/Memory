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
	bool		Acting(CCLayer* a_pParentLayer, shared_ptr<Behavior> a_Behavior, CCPoint a_Pos);

public:
	CActing();
	~CActing();

private :
	void		CreateIcon(CCLayer* a_pParentLayer, string filename );
	void		SortIcon();
	void		RemoveFirstMemory(CCLayer* a_pParentLayer);

	shared_ptr<Behavior>		m_pCurrentBehavior;
	list<shared_ptr<Behavior>>	m_listBehavior;
	list<CCSprite*>		m_listBehaviorIcon;

	int					m_nBehaviorCount;
	bool				m_bIsDoing;
};

