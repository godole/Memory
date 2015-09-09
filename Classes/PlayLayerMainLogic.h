#pragma once
#include "cocos2d.h"
#include "EDirection.h"
#include "DataManager.h"
#include "Box2D/Box2D.h"
#include <vector>
#include <memory>
#include <functional>
#include "CTextureFactory.h"
#include "ui\CocosGUI.h"

class CBox2dSprite;
class CPlayer;
class CThings;
class CScrollSprite;
class BackgroundCloud;

class PlayLayerMainLogic :
	public cocos2d::CCLayer
{
public:
	bool init();
	void b2Init();

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

	virtual void draw(Renderer *renderer, const kmMat4& transform, bool transformUpdated);

	virtual void update(float dt) override;
	void PlayerObjectUpdate();
	void b2tick(float dt);
	void Release();

	void ObjInit();
	void BGInit();
	void ObjUpdate();
	virtual void BackgroundInit() = 0;
	virtual void ObjectInit() = 0;
	virtual void BackgroundUpdate() = 0;
	virtual void ObjectUpdate() = 0;

protected :
	void settingKeyboardManager();
	void settingTouchDispatcher();
	CBox2dSprite* CreateWall(string filename, CCPoint pos);

	CCPoint origin;
	CCSize visibleSize;

	CBox2dSprite* m_pZeroWall;
	CBox2dSprite* m_pMaxWall;
	shared_ptr<CScrollSprite> m_pDestination;

	void GoNextStage();
	void Scroll();
	void ShowDeadMenu();
	void CloseDeadMenu();

	Label* m_pPlayerBehaviorCount;

	bool m_bIsEnd;
	bool m_bIsPaused;

	CCSprite* m_pMenuBackground;
	CCSprite* m_pRetryButton;
	CCSprite* m_pGoHomeButton;

	cocos2d::ui::Button* m_pLeftMoveButton;
	cocos2d::ui::Button* m_pRightMoveButton;
	cocos2d::ui::Button* m_pJumpButton;

	CCNode* m_pBGParticleNode;
	CCNode* m_pObjParticleNode;
	CCNode* m_pCharParticleNode;
	CCNode* m_pScreenParticleNode;

	shared_ptr<CPlayer> m_pPlayer;
	b2World* m_pWorld;
	shared_ptr<CScrollSprite> m_pBackground;
	vector<shared_ptr<CThings>> m_arrObject;
	BackgroundCloud* m_pBackgroundCloud;

	bool m_bIsLeftButtonTouched;
	bool m_bIsRightButtonTouched;
	bool m_bIsJumpButtonTouched;
};

