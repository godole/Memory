#pragma once
#include "Things.h"
#include <memory>

using namespace std;

class CBox2dSprite;

class CThingsWithBody :
	public CThings
{
public :
	void setBodyPositionTo(CCPoint a_vPos);
	void setBodyPositionBy(CCPoint a_vPos);

public:
	CThingsWithBody();
	~CThingsWithBody();

protected :
	shared_ptr<CBox2dSprite> m_pBodySprite;
};

