#pragma once
#include "cocos2d.h"
#include <memory>
#include "PlayLayerShareData.h"
#include "Scene_PlayLayer.h"

USING_NS_CC;
using namespace std;

class CScrollSprite;
class CPlayer;
class CBox2dSprite;

class Scene_PlayBGLayer :
	public Scene_PlayLayer
{
public:
	CREATE_FUNC(Scene_PlayBGLayer);

	virtual void update(float dt) override;
	void LayerInit() override;

private :
	CBox2dSprite* CreateWall(string filename, CCPoint pos);

	shared_ptr<CScrollSprite> m_pBackground;

	CBox2dSprite* m_pZeroWall;
	CBox2dSprite* m_pMaxWall;
};

