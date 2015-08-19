#pragma once
#include "cocos2d.h"
#include <memory>
#include "PlayLayerShareData.h"
#include "PlayLayerEntity.h"

USING_NS_CC;
using namespace std;

class CScrollSprite;
class CPlayer;
class CBox2dSprite;
class BackgroundCloud;

class Stage1Background :
	public PlayLayerEntity
{
public:
	CREATE_FUNC(Stage1Background);
	void LayerInit() override;

private :
	void MakeTreeEffect(string texturename, CCPoint a_vPos);

	vector<shared_ptr<CScrollSprite>> m_arrCloud;

	int m_nCloudCount;
	float m_fCloudSpeed;
};

