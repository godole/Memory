#pragma once

class CUserData
{
public:
	CUserData();
	~CUserData();

	void init();
	void CreateUserProfileImage(Layer *);
	void CreateUserPlayTime(Layer *);

	Sprite * getUserProfileImage() { return m_pUserProfileImage; }
	std::string getUserName() const { return m_sUserName; }

private:
	// Load Data
	void GetDataFromJNI();
	void LoadProfileImage();

	HttpRequest * UserClearNumber;			// 클리어 타임
	HttpRequest * UserImageRequest;			// 프로필 이미지 
	HttpRequest * UserPlayTimeRequest;		// 플레이 타임

	void onRequestImgCompleted(HttpClient *sender, HttpResponse *response);
	void onRequestPlayTimeCompleted(HttpClient *sender, HttpResponse *response);

	// 프로필 사진 바이너리 데이터
	const unsigned char * m_ucBinaryData;
	ssize_t		m_ssBinaryDataSize;

	// 유저 프로필
	Sprite		* m_pUserProfileImage;
	Sprite		* m_pProfileback;
	Label		* m_pUserName;
	Label		* m_pPlayTime;

	// 유저 플레이 타임
	std::string	m_sUserPlayTime;
	// 유저 페이스북 코드
	std::string m_sUserFacebookCode;
	// 유저 이름
	std::string m_sUserName;

	// Http Send Url
	std::string m_sSendUrl;
};