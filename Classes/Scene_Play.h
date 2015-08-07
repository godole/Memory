#ifndef __Scene_Play_SCENE_H__
#define __Scene_Play_SCENE_H__

#include "cocos2d.h"
#include "EDirection.h"
#include "DataManager.h"
#include "PlayLayerShareData.h"
#include "Box2D/Box2D.h"
#include <vector>
#include <memory>

USING_NS_CC;
using namespace std;
class CPlayer;
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

	//KeyboardCallback
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	//MainLoop
	virtual void update(float dt) override;
	void b2tick(float dt);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Scene_Play);

	PlayLayerShareData* getLayerDataPtr(){ return &m_LayerData; }

private :
	//visible size
	Size visibleSize;
	Vec2 origin;

	PlayLayerShareData m_LayerData;

	void settingKeyboardManager();

private :
	void GoNextStage();
	shared_ptr<CPlayer> CreatePlayer();

	bool m_bIsEnd;
};

#endif // __Scene_Play_SCENE_H__
