#pragma once
#include "StageSelectDefine.h"
#include "ESoundState.h"

class CUserData;
class COptionLayer
{
public:
	COptionLayer();
	~COptionLayer();

	//	Option Layer , Running Scene Layer
	void init(Layer *,Layer *);

	void TouchBegan(Point);
	void TouchMoved(Point);

	// UserData
	std::shared_ptr<CUserData> m_pUserData;

private:
	// Layer Base
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
	void onRequestImgCompleted(HttpClient *sender, HttpResponse *response);
};

