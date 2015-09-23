#include "StageSelectDefine.h"
#include "UserData.h"

CUserData::CUserData()
{
}


CUserData::~CUserData()
{
}

// 
void CUserData::CreateUserPlayTime(Layer * a_ParentLayer)
{
	m_pPlayTime = Label::createWithSystemFont(
		"Now Loading...", "", 40);
	m_pPlayTime->setColor(Color3B::BLACK);
	m_pPlayTime->setPosition(Point(850, 370));
	a_ParentLayer->addChild(m_pPlayTime, 4);
}

// 유저 프로필 사진 , 이름 구성
void CUserData::CreateUserProfileImage(Layer * a_pParentLayer)
{
	m_pUserProfileImage = Sprite::create("profileimage.png");
	m_pUserProfileImage->setAnchorPoint(Point(0, 1));
	m_pUserProfileImage->setPosition(Point(5, 715));
	a_pParentLayer->addChild(m_pUserProfileImage);

	m_pProfileback = Sprite::create("profileback.png");
	m_pProfileback->setAnchorPoint(Point(0, 0));
	m_pProfileback->setPosition(Point(130, 595));
	a_pParentLayer->addChild(m_pProfileback);

	m_pUserName = Label::createWithSystemFont("Loading...", "", 40);
	m_pUserName->setAnchorPoint(Point(0, 0));
	m_pUserName->setPosition(150, 650);
	a_pParentLayer->addChild(m_pUserName);
}

void CUserData::init()
{
	GetDataFromJNI();

	// 유저 이름 변경
	m_pUserName->setString(StringUtils::format("%s", m_sUserName.c_str()));

	// Init HttpRequest
	UserImageRequest = new (std::nothrow) HttpRequest();
	UserImageRequest->setRequestType(cocos2d::network::HttpRequest::Type::GET);
	UserImageRequest->setResponseCallback(CC_CALLBACK_2(CUserData::onRequestImgCompleted, this));

	UserPlayTimeRequest = new (std::nothrow) HttpRequest();
	UserPlayTimeRequest->setRequestType(cocos2d::network::HttpRequest::Type::GET);
	UserPlayTimeRequest->setResponseCallback(CC_CALLBACK_2(CUserData::onRequestPlayTimeCompleted, this));

	// 이미지 로드 시작
	m_sSendUrl = "https://graph.facebook.com/" + m_sUserFacebookCode + "/picture?width=120&height=120";
	HTTPREQUEST_SEND(UserImageRequest, m_sSendUrl);
}

void CUserData::GetDataFromJNI()
{
	std::string temp;

	// Get User Fadebook Code

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;

	// Facebook ID
	if (JniHelper::getStaticMethodInfo(t
		, "org.cocos2dx.cpp/AppActivity"      
		, "getUserFacebookID"                       
		, "()Ljava/lang/String;"));
	{
		jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		const char *msg = t.env->GetStringUTFChars(str, 0);
		CCLog("User Facebook ID : %s", msg);                  
		m_sUserFacebookCode = msg;
		t.env->ReleaseStringUTFChars(str, msg);
		t.env->DeleteLocalRef(t.classID);
	}

	// Facebook Name
	if (JniHelper::getStaticMethodInfo(t
		, "org.cocos2dx.cpp/AppActivity"          
		, "getUserName"                           
		, "()Ljava/lang/String;"));
	{
		jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		const char *msg = t.env->GetStringUTFChars(str, 0);
		CCLog("User Name : %s", msg);                  
		m_sUserName = msg;
		t.env->ReleaseStringUTFChars(str, msg);
		t.env->DeleteLocalRef(t.classID);
	}

#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	m_sUserFacebookCode = "472858996218424";
	m_sUserName			= "하민준";
#endif

	log("Change User Name Complete");
}

// Profile Image Request
void CUserData::onRequestImgCompleted(HttpClient *sender, HttpResponse *response)
{
	if (!response || !response->isSucceed())
	{
		m_pPlayTime->setVisible(false);
		m_pUserName->setVisible(false);
		m_pProfileback->setVisible(false);
		m_pUserProfileImage->setVisible(false);

		CDataManager::getInstance()->m_bConnectFacebook = false;
		return;
	}

	std::vector<char> *buffer = response->getResponseData();
	std::string temp = buffer->data();

	// 바이너리 데이터를 텍스쳐로 저장
	Image * image = new  Image();
	image->initWithImageData(reinterpret_cast<const unsigned char*>(&(buffer->front())), buffer->size());
	Texture2D * texture = new  Texture2D();
	texture->initWithImage(image);

	if (m_pUserProfileImage != nullptr)
		m_pUserProfileImage->setTexture(texture);

	// 플레이 시간 로드
	m_sSendUrl = "http://www.anioneguild.com/Memory/GetPlayTimeData.php?ID=" + m_sUserFacebookCode;
	HTTPREQUEST_SEND(UserPlayTimeRequest, m_sSendUrl);
}

// PlayTime Request
void CUserData::onRequestPlayTimeCompleted(HttpClient *sender, HttpResponse *response)
{
	if (!response || !response->isSucceed())
	{
		CDataManager::getInstance()->m_bConnectFacebook = false;
		return;
	}

	std::vector<char> *buffer = response->getResponseData();
	std::string temp = buffer->data();

	std::string _sErrorLogCheck = temp.substr(0, 5);

	if (_sErrorLogCheck == "Error")
		return;
	else
	{
		m_sUserPlayTime = temp.substr(0, 6);
		m_pPlayTime->setString(StringUtils::format("Play Time : %c%c:%c%c:%c%c",
			m_sUserPlayTime[0], m_sUserPlayTime[1],
			m_sUserPlayTime[2], m_sUserPlayTime[3],
			m_sUserPlayTime[4], m_sUserPlayTime[5]));

		CDataManager::getInstance()->m_bUserDataLoad = true;
	}
}