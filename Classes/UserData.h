#pragma once
#include "Network.h"

class CUserData
{
public:
	CUserData();
	~CUserData();

	void init();
	void CreateUI(Layer *);

	Sprite * getUserProfileImage() { return m_pUserProfileImage; }
	std::string getUserName() const { return m_sUserName; }

	void CreateUserPlayTime(Layer *);

private:
	// Base 
	Layer * m_pParentLayer;

	// Load Data
	void GetDataFromJNI();
	void LoadProfileImage();
	void LoadDataUserDefault();

	// Http Request
	HttpRequest * UserImageRequest;
	HttpRequest * UserPlayTimeRequest;

	void onRequestImgCompleted(HttpClient *sender, HttpResponse *response);
	void onRequestPlayTimeCompleted(HttpClient *sender, HttpResponse *response);

	// 네트워크에 연결 완료인가?
	bool m_isConnectNetwork;

	// 프로필 사진 바이너리 데이터
	const unsigned char * m_ucBinaryData;
	ssize_t		m_ssBinaryDataSize;

	// 유저 프로필
	Sprite		* m_pUserProfileImage;
	Label		* m_pUserName;
	Label		* m_pNetwork;
	Label		* m_pPlayTime;

	// 유저 플레이 타임
	std::string	m_sUserPlayTime;
	// 유저 페이스북 코드
	std::string m_sUserFacebookCode;
	// 유저 이름
	std::string m_sUserName;
};