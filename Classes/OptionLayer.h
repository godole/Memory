#pragma once
#include "ESoundState.h"
#include "cocos2d.h"
#include "Network.h"
#include <string>

USING_NS_CC;

class CUserData;
class COptionLayer
{
public:
	COptionLayer();
	~COptionLayer();

	void init(Layer *,Layer *);

	void TouchBegan(Point);
	void TouchMoved(Point);

	// UserData
	std::shared_ptr<CUserData> m_pUserData;

private:
	// Layer Base
	Layer  * m_pMainLayer;
	Layer  * m_pParentLayer;
	Sprite * m_pBackground;

	// Facebook Login / LogOut
	Sprite * m_pFacebookAccess;

	// Sound Layer
	Sprite * m_pScrollSound[2];
	Sprite * m_pScrollSoundBackground[2];
	ESoundState m_eSoundState;

	// Develope Profile
	HttpRequest * Img_Request;

	// = Value =
	std::string m_sName[4];
	std::string m_sEmail[4];
	std::string m_sFacebookID[4];
	
	Sprite * m_pProfileImage[4];
	Label  * m_pFacebookName[4];
	Label  * m_pEmail[4];

	int m_nProfileImgLoadCount;
	
	void DrawProfileImage();
	void LoadProfileImage(int a_nLoadCount);
	void onRequestImgCompleted(HttpClient *sender, HttpResponse *response);
};

