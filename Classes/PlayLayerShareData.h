#pragma once
#include <memory>
#include "Player.h"
#include "ScrollSprite.h"
#include "Box2D\Box2D.h"
#include "Things.h"
#include "Rail.h"

using namespace std;

struct PlayLayerShareData
{
	shared_ptr<CPlayer> m_pPlayer;
	b2World* m_pWorld;
	shared_ptr<CScrollSprite> m_pBackground;
	vector<shared_ptr<CThings>> m_arrObject;
};
