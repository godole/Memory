#pragma once
#include <list>
#include <vector>
#include <algorithm>

#include "Update.h"
#include "Network.h"
#include "ui\UIScrollView.h"

// ÇÑ¹ø Á¤¸®ÇØ¾ßÇÏ´Âµ¥..

enum class ESortIndex	{ eMoveCountSort, eClearSort };

class CGameData;
class CFriendProfile;
class FriendList
	: public CNetwork,
	public IUpdate
{
public:
	FriendList();
	~FriendList();

	void init(Layer *);
	void Update() override;
	void GetDataFromJNI() override;

	void setSortIndex(ESortIndex a_eSortIndex);

	void setSortStageFriendRank(int a_pStageNumber){
		setVisibleProfileImage(true);
		m_nSortStageNumber = a_pStageNumber; }

	void setVisibleProfileImage(bool var){ 
		// ±×´ë·Î ³öµÎ¸é ÅÍÄ¡¶û °ãÃÄ¿ä ÈæÈæ
		m_pScrollView->setPosition(Point(120, 1100 - 960 * var));	
		m_pWindow->setVisible(var); }

	bool getLoadComplete() const { return m_isLoadComplete; }
	CGameData * getUserData() { return m_vFriendLists[0]; }

	static int m_nTempCheckClearStage;

private:
	int FriendDataParser();
	void LoadFriendProfileImage();

	// Request
	virtual void onRequestAchieveCompleted(HttpClient *sender, HttpResponse * reponse) override;
	virtual void onRequestImgCompleted(HttpClient *sender, HttpResponse *response) override;
	virtual void onRequestMoveCountCompleted(HttpClient *sender, HttpResponse *response) override;

	void onRequestCreateUserAccount(HttpClient *sender, HttpResponse *response);
	void onRequestClearNumberCompleted(HttpClient * sender, HttpResponse * response);

	Layer *							m_pWindow;
	Layer *							m_pProfileLayer;

	Size							m_sizeClearScrollSize;
	Size							m_sizeMoveCountScrollSize;
	
	std::string						m_sFriendListLog;
	std::vector<CGameData *>		m_vFriendLists;
	ESortIndex						m_eNowSortIndex;

	HttpRequest * Img_Request;
	HttpRequest * Achieve_Request;
	HttpRequest * MoveCount_Request;
	HttpRequest * CraeteUserAccount;
	HttpRequest * StageClear_Request;

	cocos2d::ui::ScrollView * m_pScrollView;

	int m_nLoadCount;
	bool m_isLoadComplete;

	bool m_isConnectFacebook;

	// Sort
	int m_nSortStageNumber;

	void SortFacebookData();
	void CheckClearStage();

	std::string m_sSendUrl;
};

static bool SortClearNumber(CGameData *, CGameData *);
static bool SortMoveCount(CGameData *, CGameData *);
static bool SortStageClear(CGameData *, CGameData *);