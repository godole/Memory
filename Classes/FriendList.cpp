#include "FriendList.h"
#include "GameData.h"
#include "Define.h"

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//#include "platform\android\jni\JniHelper.h"
//#endif

int FriendList::m_nTempCheckClearStage = 0;
FriendList::FriendList()
{
	m_isLoadComplete = false;
	m_nLoadCount = 0;
	m_nSortStageNumber = 10;
}


FriendList::~FriendList()
{
	Achieve_Request->release();
	Img_Request->release();

	auto itr_list = m_vFriendLists.begin();
	for (itr_list; itr_list != m_vFriendLists.end(); itr_list++)
	{
		delete (*itr_list);
	}
	m_vFriendLists.clear();
}

void FriendList::GetDataFromJNI()
{
//#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//	JniMethodInfo t;
//	if (JniHelper::getStaticMethodInfo(t
//		, "org.cocos2dx.cpp/AppActivity"            // 불러올 Java 함수의 위치
//		, "getFriendList"                                     // 불러올 Java 함수이름
//		, "()Ljava/lang/String;"));
//	// 메서드 서명(예제의 경우는 매개변수가 없는 String을 리턴하는 함수)
//	{
//		// 함수 호출할 때 Object값을 리턴하는 함수로 받아야함!!!!
//		jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
//		const char *msg = t.env->GetStringUTFChars(str, 0);
//		CCLog("JNI GET : %s", msg);                    // 여기서 전달받은 값이 출력됨
//		m_sFriendListLog = msg;
//		t.env->ReleaseStringUTFChars(str, msg);
//		// Release
//		t.env->DeleteLocalRef(t.classID);
//	}
//#endif
	
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	m_sFriendListLog = "472858996218424\n 하민준\n 100001299266383\n 송세진\n 100004855749021\n 송진서\n 100010238795384\n 김말자\n 100010238795384\n 노비무\n 100009845986825\n 민숙킴\n 100009774228338\n 김춘배즙이 맛있어서 만들었다\n";
//#endif
	FriendDataParser();
}

void FriendList::init(Layer * a_pParentLayer)
{
	// Init HttpRequest
	Img_Request = new (std::nothrow) HttpRequest();
	Img_Request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
	Img_Request->setResponseCallback(CC_CALLBACK_2(FriendList::onRequestImgCompleted, this));

	Achieve_Request = new (std::nothrow) HttpRequest();
	Achieve_Request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
	Achieve_Request->setResponseCallback(CC_CALLBACK_2(FriendList::onRequestAchieveCompleted, this));

	MoveCount_Request = new (std::nothrow) HttpRequest();
	MoveCount_Request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
	MoveCount_Request->setResponseCallback(CC_CALLBACK_2(FriendList::onRequestMoveCountCompleted, this));

	// Scroll & Layer
	m_pScrollView = cocos2d::ui::ScrollView::create();
	m_pScrollView->setDirection(cocos2d::ui::ScrollView::Direction::HORIZONTAL);
	m_pScrollView->setBackGroundColorType
		(cocos2d::ui::Layout::BackGroundColorType::NONE);
	m_pScrollView->setClippingEnabled(false);
	m_pScrollView->setSize(Size(1080, 500));
	m_pScrollView->setAnchorPoint(Point(0, 0));
	m_pScrollView->setPosition(Point(100, 1000));
	m_pScrollView->setBounceEnabled(true);
	a_pParentLayer->addChild(m_pScrollView, 5);

	m_pProfileLayer = Layer::create();
	m_pProfileLayer->setVisible(false);
	m_pScrollView->addChild(m_pProfileLayer);

	// TEMP
	// 프로필 사진 잘 보이라고
	auto back = Sprite::create("black.png");
	back->setPosition(Point(0, -100));
	back->setScale(2.1);
	m_pProfileLayer->addChild(back);
}

void FriendList::Update()
{
	if (m_isLoadComplete)
	{
		m_nTempCheckClearStage = m_nSortStageNumber;

		CheckClearStage();

		//std::sort(m_vFriendLists.begin(), m_vFriendLists.end(), SortStageClear);
		//std::sort(m_vFriendLists.begin(), m_vFriendLists.end(), SortMoveCount);

		SortFacebookData();
	}
}

int FriendList::FriendDataParser()
{
	int m_nStringCheckPoint, m_nEndPoint;

	for (int i = 0; i < m_sFriendListLog.size(); i++)
	{
		auto temp = new CGameData;

		// ID
		m_nEndPoint = m_sFriendListLog.find("\n");
		temp->m_sFaceBookID = m_sFriendListLog.substr(0, m_nEndPoint);
		m_sFriendListLog.erase(0, m_nEndPoint + 2);

		// NAME 
		m_nEndPoint = m_sFriendListLog.find("\n");
		temp->m_sName = m_sFriendListLog.substr(0, m_nEndPoint);
		m_sFriendListLog.erase(0, m_nEndPoint + 2);

		m_vFriendLists.push_back(temp);
	}

	LoadFriendProfileImage();

	return true;
}

void FriendList::LoadFriendProfileImage()
{
	std::string _sTemp;

	// 스테이지 로드 -> 행동 카운트 로드 -> 프로필 이미지 로드
	_sTemp = "http://www.anioneguild.com/Memory/GetFriendsData.php?ID=" +
		m_vFriendLists[m_nLoadCount]->m_sFaceBookID;
	Achieve_Request->setUrl(_sTemp.c_str());
	HttpClient::getInstance()->send(Achieve_Request);

	Label * _FacebookName = Label::createWithSystemFont
		(StringUtils::format("%s",
		m_vFriendLists[m_nLoadCount]->m_sName.c_str()), "", 30,
		Size(100,200));
	_FacebookName->setPosition(Point(
		72 + m_nLoadCount * 150,
		90 + 100));
	m_pProfileLayer->addChild(_FacebookName);
	m_vFriendLists[m_nLoadCount]->m_pFacebookName = _FacebookName;
}

void FriendList::CheckClearStage()
{
	auto itr = m_vFriendLists.begin();
	for (itr; itr != m_vFriendLists.end(); itr++)
	{
		if ((*itr)->m_nAchieveStage >= m_nTempCheckClearStage)
			(*itr)->m_isVisible = true;
		else
			(*itr)->m_isVisible = false;
	}
}

bool SortStageClear(CGameData * a_pDataA, CGameData * a_pDataB)
{	
	return a_pDataA->m_isVisible > a_pDataB->m_isVisible;
}

bool SortMoveCount(CGameData * a_pDataA, CGameData *a_pDataB)
{
	return a_pDataA->m_nStageMoveCount[FriendList::m_nTempCheckClearStage] < a_pDataB->m_nStageMoveCount[FriendList::m_nTempCheckClearStage];
}

void FriendList::SortFacebookData()
{
	int i = 0;
	auto itr = m_vFriendLists.begin();
	for (itr; itr != m_vFriendLists.end(); itr++)
	{
		(*itr)->m_pFacebookName->setVisible((*itr)->m_isVisible);
		(*itr)->m_pProfileSprite->setVisible((*itr)->m_isVisible);

		if (!(*itr)->m_isVisible)
			continue;
			
		(*itr)->m_pFacebookName->setPosition(Point(72 + i * 150,90 + 100));
		(*itr)->m_pProfileSprite->setPosition(Point(70 + i * 150,250 + 100));

		i++;
	}
}

// NetWork Load
void FriendList::onRequestAchieveCompleted(HttpClient * sender, HttpResponse * response)
{
	if (!response)
		return;
	
	if (!response->isSucceed())
		return;

	std::vector<char> *buffer = response->getResponseData();
	const char* _receiveMsg = buffer->data();

	int _temp = atoi(_receiveMsg);
	// 달성 스테이지
	m_vFriendLists[m_nLoadCount]->m_nAchieveStage = _temp;

	std::string _sTemp;
	// 행동 카운트
	_sTemp = "http://www.anioneguild.com/Memory/GetMoveCount.php?ID=" +
		m_vFriendLists[m_nLoadCount]->m_sFaceBookID;
	MoveCount_Request->setUrl(_sTemp.c_str());
	HttpClient::getInstance()->send(MoveCount_Request);
}
void FriendList::onRequestMoveCountCompleted(HttpClient * sender, HttpResponse * response)
{
	if (!response)
		return;

	if (!response->isSucceed())
		return;

	std::vector<char> *buffer = response->getResponseData();
	std::string _receiveMsg = buffer->data();

	// String 문자열을 나누어 int 형으로 30스테이지 까지
	for (int i = 0; i< STAGE_NUMBER; i++)
	{
		m_vFriendLists[m_nLoadCount]->m_nStageMoveCount[i]
			= atoi(_receiveMsg.substr(i * 2 , 2).c_str());
	}

	std::string _sTemp;
	// 페이스북 이미지
	_sTemp = "https://graph.facebook.com/" +
		m_vFriendLists[m_nLoadCount]->m_sFaceBookID + "/picture?width=" +
		FACEBOOK_LOADIMAGESIZE + "&height=" + FACEBOOK_LOADIMAGESIZE;
	Img_Request->setUrl(_sTemp.c_str());
	HttpClient::getInstance()->send(Img_Request);
}
void FriendList::onRequestImgCompleted(HttpClient *sender, HttpResponse *response)
{
	if (!response)
		return;

	if (!response->isSucceed())
		return;

	std::vector<char> *buffer = response->getResponseData();
	const unsigned char * temp =  reinterpret_cast<const unsigned char*>(&(buffer->front()));

	// 바이너리 데이터를 텍스쳐로 저장
	Image * image = new  Image();
	image->initWithImageData(temp, buffer->size());
	Texture2D * texture = new  Texture2D();
	texture->initWithImage(image);

	Sprite * _FacebookImage = Sprite::createWithTexture(texture);
	_FacebookImage->setPosition(Point(
		70 + m_nLoadCount * 150,
		250 + 100));

	m_pProfileLayer->addChild(_FacebookImage);
	// 데이터에 페이스북 프로필 이미지를 저장합니다.
	m_vFriendLists[m_nLoadCount]->m_pProfileSprite = _FacebookImage;

	// 로드 번호
	m_vFriendLists[m_nLoadCount]->m_nLoadNumber = m_nLoadCount;

	// 다음 사람을 로드
	m_nLoadCount++;

	// 데이터가 받아졌다면 다시 순회
	if (m_nLoadCount < m_vFriendLists.size())
		LoadFriendProfileImage();
	else
	{
		m_isLoadComplete = true;
	}
}