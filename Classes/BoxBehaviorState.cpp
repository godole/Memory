#include "BoxBehaviorState.h"
#include "BoxDefaultState.h"
#include "ObjectManager.h"
#include "Box2dSprite.h"
#include "TransectorProfile.h"

void CBoxBehaviorState::Init(CBox* a_pBox, std::map<string, void* >* a_pValueMap)
{
	m_pBox = a_pBox;
	m_pValueMap = a_pValueMap;

	BehaviorInit();
}

void CBoxBehaviorState::setStateToDefault()
{
	m_pBox->ChangeState(shared_ptr<CBoxBehaviorState>(new CBoxDefaultState));
}

bool CBoxBehaviorState::IsPutable(TransectorProfile* profile, CCSprite* sprite, CCPoint touchPos, CCPoint& avaliablePos)
{
	auto arr = CObjectManager::getInstance()->getBox2dSprite();
	CCPoint setPos;
	bool bIsEnable = true;
	CCRect rect;

	for (int i = 0; i <= 20; i++)
	{
		for (int j = 0; j <= 20; j++)
		{
			CCRect r;
			r.setRect(i * 105 + CScrollManager::getInstance()->getDeltaPosition().x, j * 105 + CScrollManager::getInstance()->getDeltaPosition().y, 105, 105);

			if (r.containsPoint(touchPos))
			{
				setPos = ccp(r.getMidX(), r.getMidY());
				rect = r;
			}
		}
	}

	for (int i = 0; i < arr->getSize(); i++)
	{
		auto anothersprite = arr->getObjectAt(i)->getSpritePtr();

		if (anothersprite == sprite)
			continue;

		if (rect.intersectsRect(anothersprite->getBoundingBox()))
			bIsEnable = false;
	}

	if (!profile->m_TransectRange.containsPoint(touchPos))
		bIsEnable = false;

	avaliablePos = setPos;
	return bIsEnable;
}