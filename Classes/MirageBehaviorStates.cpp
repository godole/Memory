#include "MirageBehaviorStates.h"
#include "ParticleManager.h"
#include "Things.h"
#include "Box2dSprite.h"
#include "LayerDefine.h"


void CMirageBehaviorState::Init(CThings* a_pObject, std::map<string, void* >* a_pValueMap)
{
	m_pObject = a_pObject;
	m_pValueMap = a_pValueMap;

	m_pWallBodySprite = _VMAP_STATIC_CAST(CBox2dSprite*, "wallBodySprite");
	m_pGlassSprite = _VMAP_STATIC_CAST(CCSprite*, "glassSprite");
	m_pWallSprite = m_pWallBodySprite->getSpritePtr();

	BehaviorInit();
}

void CMirageBehaviorState::setStateToDefault()
{
	m_pObject->ChangeState(shared_ptr<CMirageDefaultState>(new CMirageDefaultState));
}


void CMirageDefaultState::BehaviorInit()
{
	m_pGlassSprite->setTexture(_VMAP_STATIC_CAST(CCTexture2D*, "glassTexture"));
	m_pWallSprite->setVisible(true);
	m_pWallBodySprite->getBodyStructure().body->SetActive(true);
}

bool CMirageDefaultState::Action(CCPoint a_Pos)
{
	if (m_pGlassSprite->getBoundingBox().containsPoint(a_Pos) &&
		m_pObject->getIsRanged())
	{
		m_pObject->ChangeState(std::shared_ptr<CMirageBehaviorState>(new CMirageCrashedState));
		return true;
	}

	else
		return false;
}


bool CMirageCrashedState::Action(CCPoint a_Pos)
{
	return false;
}

void CMirageCrashedState::BehaviorInit()
{
	auto parent = Director::getInstance()->getRunningScene()->getChildByTag(MAIN_LAYER)->getChildByTag(OBJ_PARTICLE_NODE);
	m_pGlassSprite->setTexture(_VMAP_STATIC_CAST(CCTexture2D*, "glassCrashedTexture"));
	m_pWallSprite->setVisible(false);
	m_pWallBodySprite->getBodyStructure().body->SetActive(false);
}