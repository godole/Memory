#pragma once
#include "StageSelectDefine.h"

class CStageBox;
class COption;
class CStageData;
class COptionLayer;
class SceneSelectScene : public Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	//TouchCallback
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);

	//MainLoop
	virtual void update(float dt) override;

	CREATE_FUNC(SceneSelectScene);

public:
	SceneSelectScene();
	~SceneSelectScene();

private:
	void BackgroundInit();
	void BackgroundScroll();

	void settingTouchManager();
	void CheckConnectToFacebook();

private:
	void LoadingInit();
	void LoadUpdate();
private:
	std::shared_ptr<CStageBox>  m_pStageBox;
	std::shared_ptr<COption>	m_pOption;
	std::shared_ptr<COptionLayer> m_pOptionLayer;
	std::shared_ptr<CStageData> m_pStageData;

private:
	Layer * m_pStageSelectLayer;
	Layer * m_pOptionPageLayer;
	
	Sprite * m_pScrollBack[4];

	Sprite * m_pLoadBackground;
	Label  * m_pLoadMessage;

	bool m_bLoadComplete;
};