#pragma once
#include <memory>
#include "Player.h"
#include "ScrollSprite.h"
#include "Box2D\Box2D.h"

using namespace std;

struct PlayLayerShareData
{
	shared_ptr<CPlayer> m_pPlayer;
	b2World* m_pWorld;
	shared_ptr<CScrollSprite> m_pDestination;
	bool m_bIsLeftButtonTouched;
	bool m_bIsRightButtonTouched;
	bool m_bIsJumpButtonTouched;
};
