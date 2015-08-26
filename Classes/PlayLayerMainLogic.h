#pragma once
#include "PlayLayerEntity.h"
#include "cocos2d.h"
#include "EDirection.h"
#include "DataManager.h"
#include "Box2D/Box2D.h"
#include <vector>
#include <memory>
#include <functional>
#include "CTextureFactory.h"

class PlayLayerMainLogic :
	public PlayLayerEntity
{
public:
	void LayerInit();
	void b2Init();

	// implement the "static create()" method manually
	CREATE_FUNC(PlayLayerMainLogic);

	//KeyboardCallback
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	virtual void onTouchesBegan(const vector<Touch*>&touches, Event* event);
	virtual void onTouchesMoved(const vector<Touch*>&touches, Event* event);
	virtual void onTouchesEnded(const vector<Touch*>&touches, Event* event);
	virtual void onTouchesCancelled(const vector<Touch*>&touches, Event* event);

	void leftButtonCallback(Ref* sender, ui::Widget::TouchEventType type);
	void rightButtonCallback(Ref* sender, ui::Widget::TouchEventType type);
	void jumpButtonCallback(Ref* sender, ui::Widget::TouchEventType type);

	virtual void update(float dt) override;
	void PlayerObjectUpdate();
	void b2tick(float dt);
	void Release();

private :
	void settingKeyboardManager();
	void settingTouchDispatcher();
	CBox2dSprite* CreateWall(string filename, CCPoint pos);

	CBox2dSprite* m_pZeroWall;
	CBox2dSprite* m_pMaxWall;
	shared_ptr<CScrollSprite> m_pDestination;

	PlayLayerShareData m_LayerData;

	void GoNextStage();
	void Scroll();
	void ShowDeadMenu();
	void CloseDeadMenu();

	

	bool m_bIsEnd;
	bool m_bIsPaused;

	CCSprite* m_pMenuBackground;
	CCSprite* m_pRetryButton;
	CCSprite* m_pGoHomeButton;

	CCNode* m_pParticleLayer;

	bool m_bIsLeftButtonTouched;
	bool m_bIsRightButtonTouched;
	bool m_bIsJumpButtonTouched;
};

