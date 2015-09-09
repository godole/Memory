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

	HttpRequest * UserClearNumber;			// Ŭ���� Ÿ��
	HttpRequest * UserImageRequest;			// ������ �̹��� 
	HttpRequest * UserPlayTimeRequest;		// �÷��� Ÿ��

	void onRequestImgCompleted(HttpClient *sender, HttpResponse *response);
	void onRequestPlayTimeCompleted(HttpClient *sender, HttpResponse *response);

	// ������ ���� ���̳ʸ� ������
	const unsigned char * m_ucBinaryData;
	ssize_t		m_ssBinaryDataSize;

	// ���� ������
	Sprite		* m_pUserProfileImage;
	Sprite		* m_pProfileback;
	Label		* m_pUserName;
	Label		* m_pPlayTime;

	// ���� �÷��� Ÿ��
	std::string	m_sUserPlayTime;
	// ���� ���̽��� �ڵ�
	std::string m_sUserFacebookCode;
	// ���� �̸�
	std::string m_sUserName;

	// Http Send Url
	std::string m_sSendUrl;
};