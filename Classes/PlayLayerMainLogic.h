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
	class CButton
	{
	public :
		std::function<void()> m_ButtonOnFunc;
		std::function<void()> m_ButtonOffFunc;

	public :
		void Init(CCLayer* a_pParentLayer, string a_szOnTextureName, string a_szOffTextureName, CCPoint a_vPos, int ZOrder = 0)
		{
			m_pOnTexture = CTextureFactory::CreateTexture(a_szOnTextureName);
			m_pOffTexture = CTextureFactory::CreateTexture(a_szOffTextureName);
			m_pParentLayer = a_pParentLayer;

			m_pSprite = CCSprite::createWithTexture(m_pOffTexture);
			m_pSprite->setPosition(a_vPos);
			a_pParentLayer->addChild(m_pSprite, ZOrder);
		}

		void OnTouchBegan(Vec2 touchPos)
		{
			if (m_pSprite->getBoundingBox().containsPoint(touchPos))
			{
				m_pSprite->setTexture(m_pOnTexture);
				m_ButtonOnFunc();
			}
		}

		void OnTouchMoved(Vec2 touchPos)
		{
			if (m_pSprite->getBoundingBox().containsPoint(touchPos))
			{
				m_pSprite->setTexture(m_pOnTexture);
				m_ButtonOnFunc();
			}
			
			else
			{
				m_pSprite->setTexture(m_pOffTexture);
				m_ButtonOffFunc();
			}
		}

		void OnTouchEnded(Vec2 touchPos)
		{
			if (m_pSprite->getBoundingBox().containsPoint(touchPos))
			{
				m_pSprite->setTexture(m_pOffTexture);
				m_ButtonOffFunc();
			}
		}

		void Release()
		{
			m_pParentLayer->removeChild(m_pSprite);
		}

	private :
		CCLayer* m_pParentLayer;
		CCSprite* m_pSprite;
		CCTexture2D* m_pOnTexture;
		CCTexture2D* m_pOffTexture;
	};
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

	CButton* m_pLeftMoveButton;
	CButton* m_pRightMoveButton;
	CButton* m_pJumpButton;

	CCSprite* m_pMenuBackground;
	CCSprite* m_pRetryButton;
	CCSprite* m_pGoHomeButton;

	CCNode* m_pParticleLayer;

	bool m_bIsLeftButtonTouched;
	bool m_bIsRightButtonTouched;
	bool m_bIsJumpButtonTouched;
};

