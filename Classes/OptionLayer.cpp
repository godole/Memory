#include "OptionLayer.h"
#include "UserData.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

COptionLayer::COptionLayer()
{
	m_nProfileImgLoadCount = 0;
	m_eSoundState = ESoundState::null;

	// 세진 선배
	m_sFacebookID[0] = "https://graph.facebook.com/100001299266383/picture?width=120&height=120";		
	// 진서 선배
	m_sFacebookID[1] = "https://graph.facebook.com/100004855749021/picture?width=120&height=120";
	// 현정 선배
	m_sFacebookID[2] = "https://fbcdn-profile-a.akamaihd.net/hprofile-ak-xfa1/v/t1.0-1/c33.33.414.414/s200x200/417828_109471292588411_1004723278_n.jpg?oh=995913c3a03603f9872594744522008e&oe=566154D3&__gda__=1449105979_772eb15dafb7c88c2d27ec7ab3947a98";
	// 나
	m_sFacebookID[3] = "https://graph.facebook.com/472858996218424/picture?width=120&height=120";

	m_sName[0] = "송세진", m_sName[1] = "송진서";
	m_sName[2] = "권현정", m_sName[3] = "하민준";

	m_sEmail[0] = "haminjun0@gmail.com";
	m_sEmail[1] = "haminjun0@gmail.com";
	m_sEmail[2] = "haminjun0@gmail.com";
	m_sEmail[3] = "haminjun0@gmail.com";
}


COptionLayer::~COptionLayer()
{
}

void COptionLayer::init(Layer * a_pParentLayer, Layer * a_pMainLayer)
{
	m_pUserData = std::shared_ptr<CUserData>(new CUserData);

	m_pMainLayer	= a_pMainLayer;
	m_pParentLayer  = a_pParentLayer;

	m_pUserData->CreateUI(a_pMainLayer);
	m_pUserData->CreateUserPlayTime(a_pParentLayer);

	m_pBackground = Sprite::create("background.png");
	m_pBackground->setAnchorPoint(Point(0, 0));
	m_pBackground->setPosition(Point(0, 0));
	a_pParentLayer->addChild(m_pBackground);

	m_pFacebookAccess = Sprite::create("facebook_logout.png");
	m_pFacebookAccess->setPosition(Point(350, 370));
	a_pParentLayer->addChild(m_pFacebookAccess);

	for (int i = 0; i < 2; i++)
	{
		m_pScrollSoundBackground[i] = Sprite::create("effectback.png");
		m_pScrollSoundBackground[i]->setAnchorPoint(Point(0, 0.5));
		m_pScrollSoundBackground[i]->setPosition(Point(250, 550 - i * 100));
		a_pParentLayer->addChild(m_pScrollSoundBackground[i]);

		m_pScrollSound[i] = Sprite::create("a.png");
		m_pScrollSound[i]->setPosition(Point(250 + 400 , 550 - i * 100));
		m_pScrollSound[i]->setScale(2.0);
		a_pParentLayer->addChild(m_pScrollSound[i]);
	}

	// Init HttpRequest
	Img_Request = new (std::nothrow) HttpRequest();
	Img_Request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
	Img_Request->setResponseCallback(CC_CALLBACK_2(COptionLayer::onRequestImgCompleted, this));
	LoadProfileImage(0);
}

void COptionLayer::LoadProfileImage(int a_nLoadCount)
{
	Img_Request->setUrl(m_sFacebookID[a_nLoadCount].c_str());
	HttpClient::getInstance()->send(Img_Request);
}

void COptionLayer::TouchBegan(Point a_ptPoint)
{
	for (int i = 0; i < 2; i++)
	{
		if (m_pScrollSound[i]->getBoundingBox().containsPoint(a_ptPoint))
		{
			if (i == 0)
			{
				m_eSoundState = ESoundState::BGM_Channel;
				break;
			}
			else if (i == 1)
			{
				m_eSoundState = ESoundState::Effect_Channel;
				break;
			}
		}
		else
			m_eSoundState = ESoundState::null;
	}
}

void COptionLayer::TouchMoved(Point a_ptPoint)
{
	if (m_eSoundState == ESoundState::BGM_Channel)
	{
		if (m_pScrollSound[0]->getPositionX() >= 250 &&
			m_pScrollSound[0]->getPositionX() <= 1050)
		{
			if (a_ptPoint.x < 250)
				a_ptPoint.x = 250;
			else if (a_ptPoint.x > 1050)
				a_ptPoint.x = 1050;

			m_pScrollSound[0]->setPosition(Point((int)a_ptPoint.x, m_pScrollSound[0]->getPositionY()));
		}
	}
	else if (m_eSoundState == ESoundState::Effect_Channel)
	{
		if (m_pScrollSound[1]->getPositionX() >= 250 &&
			m_pScrollSound[1]->getPositionX() <= 1050)
		{
			if (a_ptPoint.x < 250)
				a_ptPoint.x = 250;
			else if (a_ptPoint.x > 1050)
				a_ptPoint.x = 1050;

			m_pScrollSound[1]->setPosition(Point((int)a_ptPoint.x, m_pScrollSound[1]->getPositionY()));
		}
	}

	float BGM	 = (m_pScrollSound[0]->getPositionX() - 250) / 800;
	float EFFECT = (m_pScrollSound[1]->getPositionX() - 250) / 800;

	CCLOG("%f %f", BGM, EFFECT);
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(BGM);
	CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(EFFECT);

}

void COptionLayer::DrawProfileImage()
{
	for (int i = 0; i < 4; i++)
	{
		m_pProfileImage[i]->setVisible(true);

		m_pEmail[i]			= Label::createWithSystemFont(m_sEmail[i].c_str(),"",30);
		m_pFacebookName[i]  = Label::createWithSystemFont(m_sName[i].c_str(), "", 30);

		m_pEmail[i]->setColor(Color3B::BLACK);
		m_pFacebookName[i]->setColor(Color3B::BLACK);

		m_pEmail[i]->setAnchorPoint(Point(0, 0));
		m_pProfileImage[i]->setAnchorPoint(Point(0, 0));
		m_pFacebookName[i]->setAnchorPoint(Point(0, 0));

		switch (i)
		{
		case 0:
			m_pProfileImage[i]->setPosition(Point(50, 200));
			m_pFacebookName[i]->setPosition(Point(200, 250));
			m_pEmail[i]->setPosition(Point(200, 210));
			break;
		case 1:
			m_pProfileImage[i]->setPosition(Point(50, 50));
			m_pFacebookName[i]->setPosition(Point(200, 100));
			m_pEmail[i]->setPosition(Point(200, 60));
			break;
		case 2:
			m_pProfileImage[i]->setPosition(Point(690, 200));
			m_pFacebookName[i]->setPosition(Point(840, 250));
			m_pEmail[i]->setPosition(Point(840, 210));
			m_pProfileImage[i]->setScale(0.6);
			break;
		case 3:
			m_pProfileImage[i]->setPosition(Point(690, 50));
			m_pFacebookName[i]->setPosition(Point(840, 100));
			m_pEmail[i]->setPosition(Point(840, 60));
			break;
		default:
			break;
		}

		m_pParentLayer->addChild(m_pFacebookName[i]);
		m_pParentLayer->addChild(m_pEmail[i]);
	}

	m_pUserData->init();
}

void COptionLayer::onRequestImgCompleted(HttpClient * sender, HttpResponse * response)
{
	if (!response)
		return;

	if (!response->isSucceed())
		return;

	std::vector<char> *buffer = response->getResponseData();

	// 바이너리 데이터를 텍스쳐로 저장
	Image * image = new  Image();
	image->initWithImageData(reinterpret_cast<const unsigned char*>(&(buffer->front())), buffer->size());
	Texture2D * texture = new  Texture2D();
	texture->initWithImage(image);

	// 0 1 2 3
	m_pProfileImage[m_nProfileImgLoadCount] = Sprite::createWithTexture(texture);
	m_pProfileImage[m_nProfileImgLoadCount]->setVisible(false);
	m_pParentLayer->addChild(m_pProfileImage[m_nProfileImgLoadCount]);

	m_nProfileImgLoadCount++;

	if (m_nProfileImgLoadCount < 4)
	{
		LoadProfileImage(m_nProfileImgLoadCount);
	}
	else
	{
		DrawProfileImage();
	}
}