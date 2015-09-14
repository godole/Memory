#include "ELayerState.h"
#include "Option.h"
#include "GameSharing.h"

COption::COption()
{
	m_isFading = false;
	m_isVisible = true;
	m_eLayerState = ELayerState::SceneSelect;
}


COption::~COption()
{
}

void COption::init(Layer * a_pParentLayer)
{
	m_pMain = Sprite::create("stageselect/setting_menu.png");
	m_pMain->setPosition(Point(1200, 650));
	a_pParentLayer->addChild(m_pMain);

	m_pStageSelect = Sprite::create("stageselect/map_menu.png");
	m_pStageSelect->setPosition(Point(1200, 650));
	m_pStageSelect->setOpacity(0);
	a_pParentLayer->addChild(m_pStageSelect);

	m_pOption = Sprite::create("stageselect/setting_menu.png");
	m_pOption->setPosition(Point(1200, 650));
	m_pOption->setOpacity(0);
	a_pParentLayer->addChild(m_pOption);

	m_pAchievement = Sprite::create("stageselect/rank_menu.png");
	m_pAchievement->setPosition(Point(1200, 650));
	m_pAchievement->setOpacity(0);
	a_pParentLayer->addChild(m_pAchievement);
}

void COption::FadeOptions()
{
	FadeTo * _pFade1;		// StageSelect
	MoveBy * _pMove1;		
	Spawn * _pSpawn1;

	FadeTo * _pFade2;		// Option
	MoveBy * _pMove2;		
	Spawn * _pSpawn2;

	FadeTo * _pFade3;		// Rank
	MoveBy * _pMove3;
	Spawn * _pSpawn3;

	int _nRotationValue, _nMoveValue;

	if (m_isVisible)
	{
		_nMoveValue = -300;
		_nRotationValue = 180;
		_pFade1 = FadeIn::create(0.5);
		_pFade2 = FadeIn::create(0.5);
		_pFade3 = FadeIn::create(0.5);
	}
	else
	{
		_nMoveValue = 300;
		_nRotationValue = -180;
		_pFade1 = FadeOut::create(0.5);
		_pFade2 = FadeOut::create(0.5);
		_pFade3 = FadeOut::create(0.5);
	}

	_pMove1 = MoveBy::create(0.5, Point(0, _nMoveValue / 3));
	_pMove2 = MoveBy::create(0.5, Point(0, _nMoveValue / 3 * 2));
	_pMove3 = MoveBy::create(0.5, Point(0, _nMoveValue));
	_pSpawn1 = Spawn::create(_pFade1, _pMove1, NULL);
	_pSpawn2 = Spawn::create(_pFade2, _pMove2, NULL);
	_pSpawn3 = Spawn::create(_pFade3, _pMove3, NULL);

	auto _Rotation = RotateBy::create(0.5, _nRotationValue);
	auto _Call = CallFunc::create(std::bind([=]
	{ m_isVisible = !m_isVisible; m_isFading = false; }));
	auto _Sequence = Sequence::create(_Rotation, _Call, NULL);

	m_isFading = true;
	m_pMain->runAction(_Sequence);
	m_pStageSelect->runAction(_pSpawn1);
	m_pOption->runAction(_pSpawn2);
	m_pAchievement->runAction(_pSpawn3);
}

void COption::TouchBegan(Point a_ptPoint)
{
	if (m_pMain->getBoundingBox().containsPoint(a_ptPoint) && !m_isFading)
	{
		FadeOptions();
	}
	else if (!m_isFading)
	{
		if (m_pStageSelect->getBoundingBox().containsPoint(a_ptPoint))
			m_eLayerState = ELayerState::SceneSelect;
		else if (m_pOption->getBoundingBox().containsPoint(a_ptPoint))
			m_eLayerState = ELayerState::Option;
		else if (m_pAchievement->getBoundingBox().containsPoint(a_ptPoint))
			GameSharing::ShowAchievementsUI();
	}
}