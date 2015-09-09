#pragma once
#include "cocos2d.h"
#include "Update.h"
#include <vector>
#include <string>

class CScrollSprite;

class BackgroundCloud
{
public :
	void Init(float a_fSpeed, int a_nMaxWidth);
	cocos2d::CCSprite* InsertCloud(std::string filename, cocos2d::CCPoint a_Pos);
	void Update();

public:
	BackgroundCloud();
	~BackgroundCloud();

private :
	std::vector<shared_ptr<CScrollSprite>> m_arrCloud;

	float m_fSpeed;
	int m_nMaxWidth;
};

