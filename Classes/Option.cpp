#include "ELayerState.h"
#include "Option.h"

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
}

void COption::FadeOptions()
{
	FadeTo * _pFade1;		// StageSelect
	MoveBy * _pMove1;		
	Spawn * _pSpawn1;

	FadeTo * _pFade2;		// Option
	MoveBy * _pMove2;		
	Spawn * _pSpawn2;

	int _nRotationValue, _nMoveValue;

	if (m_isVisible)
	{
		_nMoveValue = -200;
		_nRotationValue = 180;
		_pFade1 = FadeIn::create(0.5);
		_pFade2 = FadeIn::create(0.5);
	}
	else
	{
		_nMoveValue = 200;
		_nRotationValue = -180;
		_pFade1 = FadeOut::create(0.5);
		_pFade2 = FadeOut::create(0.5);
	}

	_pMove1 = MoveBy::create(0.5, Point(0, _nMoveValue));
	_pMove2 = MoveBy::create(0.5, Point(0, _nMoveValue / 2));
	_pSpawn1 = Spawn::create(_pFade1, _pMove1, NULL);
	_pSpawn2 = Spawn::create(_pFade2, _pMove2, NULL);

	auto _Rotation = RotateBy::create(0.5, _nRotationValue);
	auto _Call = CallFunc::create(std::bind([=]
	{ m_isVisible = !m_isVisible; m_isFading = false; }));
	auto _Sequence = Sequence::create(_Rotation, _Call, NULL);

	m_isFading = true;
	m_pMain->runAction(_Sequence);
	m_pStageSelect->runAction(_pSpawn1);
	m_pOption->runAction(_pSpawn2);
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
	}
}