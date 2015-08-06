#ifndef __Scene_Play_SCENE_H__
#define __Scene_Play_SCENE_H__

#include "cocos2d.h"
#include "EDirection.h"
#include "DataManager.h"
#include "Box2D/Box2D.h"
#include <vector>
#include <memory>

USING_NS_CC;
using namespace std;

class CBox;
class CPlayer;
class CThings;
class CGround;
class IScroll;
class CRail;
class CPulley;
class CMirage;
class CScrollSprite;
class CBox2dSprite;

class Scene_Play : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	void b2Init();
	void UIInit();
	void ObjectInit();
	void BackgroundInit();

	//TouchCallback
	virtual void onTouchesBegan(const vector<Touch*>&touches, Event* event);
	virtual void onTouchesMoved(const vector<Touch*>&touches, Event* event);
	virtual void onTouchesEnded(const vector<Touch*>&touches, Event* event);
	virtual void onTouchesCancelled(const vector<Touch*>&touches, Event* event);

	//KeyboardCallback
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	//MainLoop
	virtual void update(float dt) override;
	void b2tick(float dt);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Scene_Play);

private :
	b2World* m_world;
	//visible size
	Size visibleSize;
	Vec2 origin;

	//Player
	shared_ptr<CPlayer> m_pPlayer;

	//Destination
	shared_ptr<CScrollSprite> m_pDestination;
	
	//Background
	shared_ptr<CScrollSprite> m_pBackground;

	//UI
	CCSprite* m_pLeftMoveButton;
	CCTexture2D* m_pLeftButtonOn;
	CCTexture2D* m_pLeftButtonOff;

	CCSprite* m_pRightMoveButton;
	CCTexture2D* m_pRightButtonOn;
	CCTexture2D* m_pRightButtonOff;

	CCSprite* m_pJumpButton;
	CCTexture2D* m_pJumpButtonOn;
	CCTexture2D* m_pJumpButtonOff;

	CCSprite* m_pFilmSprite;

	CBox2dSprite* m_pZeroWall;
	CBox2dSprite* m_pMaxWall;

	//¾ß¸Å
	bool m_bIsLeftButtonTouched;
	bool m_bIsRightButtonTouched;
	bool m_bIsJumpButtonTouched;

	void settingTouchManager();
	void settingKeyboardManager();

	void Scrolling();

private :
	vector<shared_ptr<CThings>> m_arrObject;
	vector<shared_ptr<CRail>>	 m_arrRail;

	bool			m_bIsEnd;

	void GoNextStage();
	CCTexture2D* CreateTexture(string filename);
	CBox2dSprite* CreateWall(string filename, CCPoint pos);
	shared_ptr<CPlayer> CreatePlayer();
};

#endif // __Scene_Play_SCENE_H__
