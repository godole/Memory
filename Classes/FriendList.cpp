#include "DataManager.h"
#include "FriendList.h"
#include "GameData.h"
#include "StageSelectDefine.h"

int FriendList::m_nTempCheckClearStage = 0;
FriendList::FriendList()
{
	m_isConnectFacebook = false;
	m_isLoadComplete = false;
	m_nLoadCount = 0;
	m_nSortStageNumber = 10;

	m_eNowSortIndex = ESortIndex::eClearSort;
}


FriendList::~FriendList()
{
	auto itr_list = m_vFriendLists.begin();
	for (itr_list; itr_list != m_vFriendLists.end(); itr_list++)
	{
		delete (*itr_list);
	}
	m_vFriendLists.clear();
}

void FriendList::GetDataFromJNI()
{
	std::string temp;

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t
		, "org.cocos2dx.cpp/MainFragment"            // 불러올 Java 함수의 위치
		, "getConnectFacebook"                                     // 불러올 Java 함수이름
		, "()Ljava/lang/String;"));
	// 메서드 서명(예제의 경우는 매개변수가 없는 String을 리턴하는 함수)
	{
		jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		const char *msg = t.env->GetStringUTFChars(str, 0);
		CCLog("FriendList Connect To Facebook : %s", msg);                  
		temp = msg;
		t.env->ReleaseStringUTFChars(str, msg);
		t.env->DeleteLocalRef(t.classID);
	}

	if (temp == "O")
	{
		m_isConnectFacebook = true;
		CCLog("FriendList Connected"); 

		if (JniHelper::getStaticMethodInfo(t
			, "org.cocos2dx.cpp/MainFragment"            // 불러올 Java 함수의 위치
			, "getFriendNameCode"                                     // 불러올 Java 함수이름
			, "()Ljava/lang/String;"));
		// 메서드 서명(예제의 경우는 매개변수가 없는 String을 리턴하는 함수)
		{
			// 함수 호출할 때 Object값을 리턴하는 함수로 받아야함!!!!
			jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
			const char *msg = t.env->GetStringUTFChars(str, 0);
			m_sFriendListLog = msg;
			CCLog("Friend List : %s", m_sFriendListLog.c_str());
			t.env->ReleaseStringUTFChars(str, msg);
			// Release
			t.env->DeleteLocalRef(t.classID);
		}
	}
	else
	{
		m_isConnectFacebook = false;
		CCLog("FriendList Connect False");
		CDataManager::getInstance()->m_bConnectFacebook = false;
		return;
	}

#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	m_sFriendListLog = "472858996218424, 하민준, 472858996218424, 하민준, 472858996218424, 하민준, 891299854256648, 송세진, 100004855749021, 송진서, 100010238795384, 김락자, 100010238795384, 김춘자, 100009845986825, 김민자, 100009774228338, 김숙자,";
	m_isConnectFacebook = true;
#endif

	if (m_isConnectFacebook)
	{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CCLog("Connect Parser Friend List %s", m_sFriendListLog.c_str());
#endif
		FriendDataParser();
	}
}

void FriendList::init(Layer * a_pParentLayer)
{
	m_pWindow = Layer::create();
	m_pWindow->setVisible(false);
	a_pParentLayer->addChild(m_pWindow);

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

	CraeteUserAccount = new (std::nothrow) HttpRequest();
	CraeteUserAccount->setRequestType(cocos2d::network::HttpRequest::Type::GET);
	CraeteUserAccount->setResponseCallback(CC_CALLBACK_2(FriendList::onRequestCreateUserAccount, this));

	// Scroll & Layer
	m_pScrollView = cocos2d::ui::ScrollView::create();
	m_pScrollView->setAnchorPoint(Point(0, 0));
	m_pScrollView->setBounceEnabled(true);
	m_pScrollView->setPosition(Point(120, 1100));
	m_pWindow->addChild(m_pScrollView, 2);

	m_pProfileLayer = Layer::create();
	m_pScrollView->addChild(m_pProfileLayer);

	// TEMP
	// 프로필 사진 잘 보이라고
	auto back = Sprite::create("black.png");
	back->setPosition(Point(640, 330));
	m_pWindow->addChild(back);
}

void FriendList::Update()
{
	if (m_isLoadComplete)
	{
		m_nTempCheckClearStage = m_nSortStageNumber;

		CheckClearStage();
		std::sort(m_vFriendLists.begin(), m_vFriendLists.end(), SortStageClear);

		if (m_eNowSortIndex == ESortIndex::eClearSort)
		{

		}
		else if (m_eNowSortIndex == ESortIndex::eMoveCountSort)
		{
			std::sort(m_vFriendLists.begin(), m_vFriendLists.end(), SortMoveCount);
		}

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
		m_nEndPoint = m_sFriendListLog.find(",");
		temp->m_sFaceBookID = m_sFriendListLog.substr(0, m_nEndPoint);
		m_sFriendListLog.erase(0, m_nEndPoint + 2);

		// NAME 
		m_nEndPoint = m_sFriendListLog.find(",");
		temp->m_sName = m_sFriendListLog.substr(0, m_nEndPoint);
		m_sFriendListLog.erase(0, m_nEndPoint + 2);

		m_vFriendLists.push_back(temp);

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CCLog("ID : %s Name : %s", temp->m_sFaceBookID.c_str(),
			temp->m_sName.c_str());
#endif
	}

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CCLog("Facebook Friend Load Complete");
#endif

	Size size ;
	size.setSize(1040 + m_vFriendLists.size() / 14 * 1040, 370);

	m_sizeClearScrollSize = size;

	size.setSize(1040, 370 + m_vFriendLists.size() * 110);

	m_sizeMoveCountScrollSize = size;

	setSortIndex(ESortIndex::eMoveCountSort);
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
		Size(100, 200));
	_FacebookName->setPosition(Point(
		72 + m_nLoadCount * 150,
		90 + 100));
	m_pProfileLayer->addChild(_FacebookName);
	m_vFriendLists[m_nLoadCount]->m_pFacebookName = _FacebookName;

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CCLog("Facebook Friend Complete Http");
#endif
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

static bool SortStageClear(CGameData * a_pDataA, CGameData * a_pDataB)
{
	return a_pDataA->m_isVisible > a_pDataB->m_isVisible;
}

static bool SortMoveCount(CGameData * a_pDataA, CGameData *a_pDataB)
{
	return a_pDataA->m_nStageMoveCount[FriendList::m_nTempCheckClearStage] < a_pDataB->m_nStageMoveCount[FriendList::m_nTempCheckClearStage];
}

void FriendList::setSortIndex(ESortIndex a_eSortIndex)
{
 	m_eNowSortIndex = a_eSortIndex;

	if (a_eSortIndex == ESortIndex::eClearSort)
	{
		m_pScrollView->setDirection(cocos2d::ui::ScrollView::Direction::HORIZONTAL);
		m_pScrollView->setSize(m_sizeClearScrollSize);
	}
	else if (a_eSortIndex == ESortIndex::eMoveCountSort)
	{
		m_pScrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
		m_pScrollView->setSize(m_sizeMoveCountScrollSize);
	}

	m_pScrollView->setContentSize(Size(1040, 370));
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

		(*itr)->m_pMoveCount->setVisible(false);

		if (m_eNowSortIndex == ESortIndex::eClearSort)
		{
			if ((i / 7) % 2 == 0)
			{
				(*itr)->m_pProfileSprite->setPosition(Point(70 + (i % 7) * 150, 310 + m_vFriendLists.size() * 110));
				(*itr)->m_pFacebookName->setPosition(Point(70 + (i % 7) * 150, 140 + m_vFriendLists.size() * 110));
			}
			else
			{
				(*itr)->m_pProfileSprite->setPosition(Point(70 + (i % 7) * 150, 310 + m_vFriendLists.size() * 110 - 210));
				(*itr)->m_pFacebookName->setPosition(Point(70 + (i % 7) * 150, 140 + m_vFriendLists.size() * 110 - 210));
			}

		}
		else
		{
			(*itr)->m_pMoveCount->setVisible(true);
			(*itr)->m_pMoveCount->setString(
				StringUtils::format("MoveCount : %d", m_vFriendLists[i]->m_nStageMoveCount[m_nSortStageNumber]));

			(*itr)->m_pMoveCount->setPosition(Point(700, 310 + m_vFriendLists.size() * 110 - i * 140));
			(*itr)->m_pFacebookName->setPosition(Point(400, 230 + m_vFriendLists.size() * 110 - i * 140));
			(*itr)->m_pProfileSprite->setPosition(Point(170, 320 + m_vFriendLists.size() * 110 - i * 140));
		}

		i++;
	}
}

// NetWork Request
void FriendList::onRequestAchieveCompleted(HttpClient * sender, HttpResponse * response)
{
	if (!response)
	{
		CDataManager::getInstance()->m_bConnectFacebook = false;
		return;
	}

	if (!response->isSucceed())
	{
		CDataManager::getInstance()->m_bConnectFacebook = false;
		return;
	}

	std::vector<char> *buffer = response->getResponseData();
	const char* _receiveMsg = buffer->data();

	std::string temp = buffer->data();
	std::string _sErrorLogCheck = temp.substr(0, 5);

	if (_sErrorLogCheck == "Error")
	{
		std::string _temp = "http://www.anioneguild.com/Memory/PushUserData.php?ID="
			+ m_vFriendLists[m_nLoadCount]->m_sFaceBookID + "&Stage=9";
		CraeteUserAccount->setUrl(_temp.c_str());
		HttpClient::getInstance()->send(CraeteUserAccount);
	}
	else
	{
		int _temp = atoi(_receiveMsg);
		// 달성 스테이지
		m_vFriendLists[m_nLoadCount]->m_nAchieveStage = _temp;

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CCLog("Facebook Friend Achieve Load Complete");
#endif

		std::string _sTemp;
		// 행동 카운트
		_sTemp = "http://www.anioneguild.com/Memory/GetMoveCount.php?ID=" +
			m_vFriendLists[m_nLoadCount]->m_sFaceBookID;
		MoveCount_Request->setUrl(_sTemp.c_str());
		HttpClient::getInstance()->send(MoveCount_Request);

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CCLog("Facebook Friend MoveCount Http URL %s", _sTemp.c_str());
#endif
	}
}
void FriendList::onRequestMoveCountCompleted(HttpClient * sender, HttpResponse * response)
{
	if (!response)
	{
		CDataManager::getInstance()->m_bConnectFacebook = false;
		return;
	}

	if (!response->isSucceed())
	{
		CDataManager::getInstance()->m_bConnectFacebook = false;
		return;
	}

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CCLog("Facebook Friend MoveCount Request Complete");
#endif

	std::vector<char> *buffer = response->getResponseData();
	std::string _receiveMsg = buffer->data();
	std::string _sErrorLogCheck = _receiveMsg.substr(0, 5);

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CCLog("Facebook Friend MoveCount Receive Msg %s", _receiveMsg.c_str());
#endif

	if (_sErrorLogCheck == "Error")
	{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CCLog("Facebook Friend MoveCount Error Log");
#endif
		return;
	}

	// String 문자열을 나누어 int 형으로 30스테이지 까지
	for (int i = 0; i < STAGE_NUMBER; i++)
	{
		m_vFriendLists[m_nLoadCount]->m_nStageMoveCount[i]
			= atoi(_receiveMsg.substr(i * 2 , 2).c_str());
	}

	auto _MoveCount = Label::createWithSystemFont("", "", 30);
	_MoveCount->setVisible(false);
	m_pProfileLayer->addChild(_MoveCount);

	m_vFriendLists[m_nLoadCount]->m_pMoveCount = _MoveCount;

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CCLog("Facebook Friend MoveCount Load Complete");
#endif

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
	{
		CDataManager::getInstance()->m_bConnectFacebook = false;
		return;
	}

	if (!response->isSucceed())
	{
		CDataManager::getInstance()->m_bConnectFacebook = false;
		return;
	}


	std::vector<char> *buffer = response->getResponseData();
	const unsigned char * temp = reinterpret_cast<const unsigned char*>(&(buffer->front()));

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

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CCLog("Facebook Profile Image Load Complete");
#endif

	// 데이터가 받아졌다면 다시 순회
	if (m_nLoadCount < m_vFriendLists.size())
		LoadFriendProfileImage();
	else
	{
		m_isLoadComplete = true;
		CDataManager::getInstance()->m_bFriendDataLoad = true;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		CCLog("Facebook Load Complete");
#endif
	}
}
void FriendList::onRequestCreateUserAccount(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		CDataManager::getInstance()->m_bConnectFacebook = false;
		return;
	}

	if (!response->isSucceed())
	{
		CDataManager::getInstance()->m_bConnectFacebook = false;
		return;
	}

	std::vector<char> *buffer = response->getResponseData();
	std::string temp = buffer->data();

	LoadFriendProfileImage();
}