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

	// ��Ʈ��ũ�� ���� �Ϸ��ΰ�?
	bool m_isConnectNetwork;

	// ������ ���� ���̳ʸ� ������
	const unsigned char * m_ucBinaryData;
	ssize_t		m_ssBinaryDataSize;

	// ���� ������
	Sprite		* m_pUserProfileImage;
	Label		* m_pUserName;
	Label		* m_pNetwork;
	Label		* m_pPlayTime;

	// ���� �÷��� Ÿ��
	std::string	m_sUserPlayTime;
	// ���� ���̽��� �ڵ�
	std::string m_sUserFacebookCode;
	// ���� �̸�
	std::string m_sUserName;
};