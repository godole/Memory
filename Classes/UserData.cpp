#include "UserData.h"
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//#include "platform\android\jni\JniHelper.h"
//#endif

CUserData::CUserData()
{
	m_isConnectNetwork = false;
}


CUserData::~CUserData()
{
	UserImageRequest->release();
	UserPlayTimeRequest->release();
}

void CUserData::CreateUserPlayTime(Layer * a_ParentLayer)
{
	m_pPlayTime = Label::createWithSystemFont(
		"Now Loading...", "", 40);
	m_pPlayTime->setColor(Color3B::BLACK);
	m_pPlayTime->setPosition(Point(850, 370));
	a_ParentLayer->addChild(m_pPlayTime,4);
}

void CUserData::CreateUI(Layer * a_pParentLayer)
{
	m_pParentLayer = a_pParentLayer;

	// 
	m_pUserProfileImage = Sprite::create("profileimage.png");
	m_pUserProfileImage->setAnchorPoint(Point(0, 1));
	m_pUserProfileImage->setPosition(Point(5, 715));
	m_pParentLayer->addChild(m_pUserProfileImage);
	
	auto profileback = Sprite::create("profileback.png");
	profileback->setAnchorPoint(Point(0, 0));
	profileback->setPosition(Point(130, 595));
	m_pParentLayer->addChild(profileback);

	// Label Load
	m_pNetwork = Label::createWithSystemFont("네트워크 연결중...", "", 30);
	m_pNetwork->setAnchorPoint(Point(0, 0));
	m_pNetwork->setPosition(150, 610);
	a_pParentLayer->addChild(m_pNetwork);

	m_pUserName = Label::createWithSystemFont("Loading...", "", 40);
	m_pUserName->setAnchorPoint(Point(0, 0));
	m_pUserName->setPosition(150, 650);
	a_pParentLayer->addChild(m_pUserName);
}

void CUserData::init()
{
	//LoadDataUserDefault();
	GetDataFromJNI();

	// Init HttpRequest
	UserImageRequest = new (std::nothrow) HttpRequest();
	UserImageRequest->setRequestType(cocos2d::network::HttpRequest::Type::GET);
	UserImageRequest->setResponseCallback(CC_CALLBACK_2(CUserData::onRequestImgCompleted, this));

	UserPlayTimeRequest = new (std::nothrow) HttpRequest();
	UserPlayTimeRequest->setRequestType(cocos2d::network::HttpRequest::Type::GET);
	UserPlayTimeRequest->setResponseCallback(CC_CALLBACK_2(CUserData::onRequestPlayTimeCompleted, this));

	// 이름 UserDefault 저장
	UserDefault::getInstance()->setStringForKey("UserName", m_sUserName);

	// 이미지 로드 시작
	//std::string _temp = "https://graph.facebook.com/" + m_sUserFacebookCode + "/picture?width=120&height=120";

	std::string _temp = "https://graph.facebook.com/472858996218424/picture?width=120&height=120";
	UserImageRequest->setUrl(_temp.c_str());
	HttpClient::getInstance()->send(UserImageRequest);
}

void CUserData::LoadDataUserDefault()
{
	// 기기에 바이너리 코드가 있다면 이미지를 기기에서 불러옴
	//m_ucBinaryData = reinterpret_cast<const unsigned char*>(&UserDefault::getInstance()->getStringForKey("ImageBinaryData"));
	m_ssBinaryDataSize = UserDefault::getInstance()->getStringForKey("ImageBinaryData").size();

	//	LoadProfileImage();

	// 기기에서 이름이 저장되어 있다면 기기에서 불러옴
	m_sUserName = UserDefault::getInstance()->getStringForKey("UserName");
	m_pUserName->setString(StringUtils::format("%s", m_sUserName.c_str()));

	// 기기의 플레이 타임을 받아옴
	m_sUserPlayTime = UserDefault::getInstance()->getStringForKey("UserPlayTime");
}

void CUserData::LoadProfileImage()
{
	if (m_ssBinaryDataSize == 0 || m_ucBinaryData == NULL ||
		strcmp((const char *)m_ucBinaryData,"\0") == 0)
		return;

	// 바이너리 데이터를 텍스쳐로 저장
	Image * image = new  Image();
	image->initWithImageData(m_ucBinaryData, m_ssBinaryDataSize);
	Texture2D * texture = new  Texture2D();
	texture->initWithImage(image);

	m_pUserProfileImage->setTexture(texture);
}

void CUserData::GetDataFromJNI()
{
	// Get User Fadebook Code
//#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//	JniMethodInfo t;
//	if (JniHelper::getStaticMethodInfo(t
//		, "org.cocos2dx.cpp/AppActivity"      
//		, "getUserCode"                       
//		, "()Ljava/lang/String;"));
//	{
//		jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
//		const char *msg = t.env->GetStringUTFChars(str, 0);
//		CCLog("JNI GET : %s", msg);                  
//		m_pUserFacebookCode = msg;
//		t.env->ReleaseStringUTFChars(str, msg);
//		t.env->DeleteLocalRef(t.classID);
//	}
//
//	if (JniHelper::getStaticMethodInfo(t
//		, "org.cocos2dx.cpp/AppActivity"          
//		, "getUserName"                           
//		, "()Ljava/lang/String;"));
//	{
//		jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
//		const char *msg = t.env->GetStringUTFChars(str, 0);
//		CCLog("JNI GET : %s", msg);                  
//		m_pUserName = msg;
//		t.env->ReleaseStringUTFChars(str, msg);
//		t.env->DeleteLocalRef(t.classID);
//	}
//#endif
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	m_sUserFacebookCode = "472858996218424";
	m_sUserName			= "하민준";
//#endif
	m_pUserName->setString(StringUtils::format("%s", m_sUserName.c_str()));
}

void CUserData::onRequestImgCompleted(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		m_pNetwork->setString("네트워크 연결 실패 !");
		return;
	}

	if (!response->isSucceed())
	{
		m_pNetwork->setString("네트워크 연결 실패 !");
		return;
	}

	std::vector<char> *buffer = response->getResponseData();
	
	//m_ucBinaryData = reinterpret_cast<const unsigned char*>(&(buffer->front()));
	m_ssBinaryDataSize = buffer->size();

	std::string temp = buffer->data();

	// 같은 데이터인지 비교

	CCLOG("Load User Profile Image");

	//UserDefault::getInstance()->setStringForKey("ImageBinaryData", buffer->data());
	//UserDefault::getInstance()->flush();

	//UserDefault::getInstance()->setStringForKey("ImageBinarySize", strlen((const char *)m_ucBinaryData);
	//UserDefault::getInstance()->flush();

	// 바이너리 데이터를 텍스쳐로 저장
	Image * image = new  Image();
	image->initWithImageData(reinterpret_cast<const unsigned char*>(&(buffer->front())), m_ssBinaryDataSize);
	Texture2D * texture = new  Texture2D();
	texture->initWithImage(image);

	m_pUserProfileImage->setTexture(texture);

	// 플레이 시간 로드
	std::string _sTemp = "http://www.anioneguild.com/Memory/GetPlayTimeData.php?ID="
		+ m_sUserFacebookCode;
	UserPlayTimeRequest->setUrl(_sTemp.c_str());
	HttpClient::getInstance()->send(UserPlayTimeRequest);
}

void CUserData::onRequestPlayTimeCompleted(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		m_pNetwork->setString("네트워크 연결 실패 !");
		return;
	}

	if (!response->isSucceed())
	{
		m_pNetwork->setString("네트워크 연결 실패 !");
		return;
	}

	std::vector<char> *buffer = response->getResponseData();
	std::string temp = buffer->data();
	m_sUserPlayTime = temp.substr(0, 6);

	// 플레이 타임 로드
	CCLOG("Load User Play Time %s", m_sUserPlayTime.c_str());

	m_pPlayTime->setString(StringUtils::format("Play Time : %c%c:%c%c:%c%c",
		m_sUserPlayTime[0], m_sUserPlayTime[1],
		m_sUserPlayTime[2], m_sUserPlayTime[3],
		m_sUserPlayTime[4], m_sUserPlayTime[5]));

	UserDefault::getInstance()->setStringForKey("UserPlayTime", m_sUserPlayTime);
	UserDefault::getInstance()->flush();

	m_isConnectNetwork = true;
	m_pNetwork->setString("네트워크 연결 성공 !");
}