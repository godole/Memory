#include "SceneSelectScene.h"
#include "UpdateManager.h"
#include "ELayerState.h"
#include "DataManager.h"
#include "OptionLayer.h"
#include "StageBox.h"
#include "UserData.h"
#include "Option.h"

SceneSelectScene::SceneSelectScene(){
	CDataManager::getInstance()->m_bFriendDataLoad = false;
	CDataManager::getInstance()->m_bUserDataLoad   = false;
	CDataManager::getInstance()->m_bConnectFacebook = true;
	CDataManager::getInstance()->m_bAllDataLoaded = false;
	CDataManager::getInstance()->m_bOptionCreatorDataLoad = false;

	m_bLoadComplete = false;
}
SceneSelectScene::~SceneSelectScene(){
	// 코드 합칠때 수정해야합니다
	UpdateManager::getInstance()->Release();
}

Scene* SceneSelectScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SceneSelectScene::create();
	scene->addChild(layer);
	return scene;
}

bool SceneSelectScene::init()
{
	// 페이스북 체크
	CheckConnectToFacebook();
	settingTouchManager();
	scheduleUpdate();

	// 각 레이어
	m_pStageSelectLayer = Layer::create();
	m_pStageSelectLayer->setVisible(true);
	addChild(m_pStageSelectLayer);

	m_pOptionPageLayer = Layer::create();
	m_pOptionPageLayer->setVisible(false);
	addChild(m_pOptionPageLayer);

	// 배경 초기화
	BackgroundInit();

	// 옵션 선택
	m_pOption = std::shared_ptr<COption>(new COption);
	m_pOption->init(this);

	// 환경설정
	m_pOptionLayer = std::shared_ptr<COptionLayer>(new COptionLayer);
	m_pOptionLayer->init(m_pOptionPageLayer,this);

	// 스테이지
	m_pStageBox = std::shared_ptr<CStageBox>(new CStageBox);
	m_pStageBox->init(m_pStageSelectLayer);
	UpdateManager::getInstance()->Insert(m_pStageBox);

	// 로딩 시작
	LoadingInit();

	return true;
}

void SceneSelectScene::CheckConnectToFacebook()
{
	std::string _sCheckToFacebook;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t
		, "org.cocos2dx.cpp/MainFragment"            
		, "getConnectFacebook"                        
		, "()Ljava/lang/String;"));
	{
		jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		const char *msg = t.env->GetStringUTFChars(str, 0);
		CCLog("Check Connect Facebook : %s", msg);
		_sCheckToFacebook = msg;
		t.env->ReleaseStringUTFChars(str, msg);
		t.env->DeleteLocalRef(t.classID);
	}
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	_sCheckToFacebook = "O";
#endif
	if (_sCheckToFacebook == "O")
		CDataManager::getInstance()->m_bConnectFacebook = true;
	else
		CDataManager::getInstance()->m_bConnectFacebook = false;
}

void SceneSelectScene::LoadingInit()
{
	m_pLoadBackground = Sprite::create("stageselect/loadbackground.png");
	m_pLoadBackground->setAnchorPoint(Point(0, 0));
	addChild(m_pLoadBackground);

	m_pLoadMessage = Label::createWithSystemFont("기억속에서 페이스북 친구들 꺼내는 중 ...",
		"", 30);
	m_pLoadMessage->setPosition(Point(640, 300));
	addChild(m_pLoadMessage);
}
void SceneSelectScene::LoadUpdate()
{
	if (!CDataManager::getInstance()->m_bConnectFacebook)
	{
		CDataManager::getInstance()->m_bAllDataLoaded = true;
		m_pLoadBackground->setVisible(false);
		m_pLoadMessage->setVisible(false);
	}
	else
	{
		if (CDataManager::getInstance()->m_bUserDataLoad)
			m_pLoadMessage->setString("내 기억 찾는 중...");
		if (CDataManager::getInstance()->m_bOptionCreatorDataLoad)
			m_pLoadMessage->setString("나를 만든 사람들을 기억하는 중...");
		if (CDataManager::getInstance()->m_bFriendDataLoad &&
			CDataManager::getInstance()->m_bUserDataLoad &&
			CDataManager::getInstance()->m_bOptionCreatorDataLoad)
		{
			m_pLoadMessage->setString("모두의 기억 찾기 완료 !");
			CDataManager::getInstance()->m_bAllDataLoaded = true;
		}
	}
}

void SceneSelectScene::update(float dt)
{
	UpdateManager::getInstance()->Updating();

	BackgroundScroll();
	LoadUpdate();

	// Change State
	if (m_pOption->getLayerState() == ELayerState::Option)
	{
		m_pOptionPageLayer->setVisible(true); 
		m_pStageSelectLayer->setVisible(false);
	}
	else if (m_pOption->getLayerState() == ELayerState::SceneSelect)
	{
		m_pOptionPageLayer->setVisible(false);
		m_pStageSelectLayer->setVisible(true);
	}
}

void SceneSelectScene::BackgroundInit()
{
	// 이거 다른 클래스로 옮겨야할것같다 음음
	auto _pBackground = Sprite::create("stageselect/menu_ground.png");
	_pBackground->setAnchorPoint(Point(0, 0));
	m_pStageSelectLayer->addChild(_pBackground);

	m_pScrollBack[0] = Sprite::create("stageselect/menu_1.png");
	m_pScrollBack[0]->setAnchorPoint(Point(0, 0));
	m_pScrollBack[0]->setPosition(Point(0, 0));
	m_pStageSelectLayer->addChild(m_pScrollBack[0]);

	m_pScrollBack[1] = Sprite::create("stageselect/menu_1.png");
	m_pScrollBack[1]->setAnchorPoint(Point(0, 0));
	m_pScrollBack[1]->setPosition(Point(0, -1440));
	m_pStageSelectLayer->addChild(m_pScrollBack[1]);

	m_pScrollBack[2] = Sprite::create("stageselect/menu_2.png");
	m_pScrollBack[2]->setAnchorPoint(Point(0, 0));
	m_pScrollBack[2]->setPosition(Point(0, 0));
	m_pStageSelectLayer->addChild(m_pScrollBack[2]);

	m_pScrollBack[3] = Sprite::create("stageselect/menu_2.png");
	m_pScrollBack[3]->setAnchorPoint(Point(0, 0));
	m_pScrollBack[3]->setPosition(Point(0, -1440));
	m_pStageSelectLayer->addChild(m_pScrollBack[3]);
}
void SceneSelectScene::BackgroundScroll()
{
	for (int i = 0; i < 4; i++)
	{
		if (m_pScrollBack[i]->getPositionY() >= 720)
			m_pScrollBack[i]->setPositionY(-1440);

		if (i >1)
			m_pScrollBack[i]->setPositionY(
			m_pScrollBack[i]->getPositionY() + 2);
		else
			m_pScrollBack[i]->setPositionY(
			m_pScrollBack[i]->getPositionY() + 1);
	}
}

void SceneSelectScene::settingTouchManager()
{
	EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
	auto* touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(SceneSelectScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(SceneSelectScene::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(SceneSelectScene::onTouchEnded, this);

	dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool SceneSelectScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	auto _ptTouchpos = touch->getLocation();

	auto _touchparticle = ParticleSystemQuad::create("stageselect/particle_texture.plist");
	_touchparticle->setPosition(Point(_ptTouchpos.x, _ptTouchpos.y));
	this->addChild(_touchparticle);
	
	if (CDataManager::getInstance()->m_bAllDataLoaded)
	{
		m_pLoadBackground->setVisible(false);
		m_pLoadMessage->setVisible(false);

		m_pOption->TouchBegan(_ptTouchpos);

		if (m_pOption->getLayerState() == ELayerState::SceneSelect)
			m_pStageBox->StageTouchBegan(_ptTouchpos);
		else if (m_pOption->getLayerState() == ELayerState::Option)
			m_pOptionLayer->TouchBegan(_ptTouchpos);
	}

	return true;
}

void SceneSelectScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	if (CDataManager::getInstance()->m_bAllDataLoaded)
		m_pStageBox->StageTouchEnded(touch->getLocation());
}

void SceneSelectScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	if (CDataManager::getInstance()->m_bAllDataLoaded)
	{
		if (m_pOption->getLayerState() == ELayerState::SceneSelect)
			m_pStageBox->StageTouchMoved(touch->getLocation());
		else if (m_pOption->getLayerState() == ELayerState::Option)
			m_pOptionLayer->TouchMoved(touch->getLocation());
	}
}