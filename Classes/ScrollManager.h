#pragma once
#include "cocos2d.h"
#include "Singleton.h"
#include <list>
#include <memory>

USING_NS_CC;
using namespace std;

class IScroll;

class CScrollManager :
	public Singleton<CScrollManager>
{
public :
	void	Insert(shared_ptr<IScroll> a_pScrl);
	void	Scroll(Vec2 a_vDeltaPos);
	void	Release();

public :
	Vec2	getDeltaPosition(){ return m_vDeltaPosition; }

public:
	CScrollManager();
	~CScrollManager();

private :
	list<shared_ptr<IScroll>>	m_arrScroll;
	Vec2			m_vDeltaPosition;
};

