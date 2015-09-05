#pragma once
#include <list>
#include <vector>
#include <algorithm>

#include "Update.h"
#include "Network.h"
#include "ui\UIScrollView.h"


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

	void setSortStageFriendRank(int a_pStageNumber){
		setVisibleProfileImage(true);
		m_nSortStageNumber = a_pStageNumber; }

	void setVisibleProfileImage(bool var){ 
		// ±×´ë·Î ³öµÎ¸é ÅÍÄ¡¶û °ãÃÄ¿ä ÈæÈæ
		m_pScrollView->setPosition(Point(100, 1000 - 900 * var));	
		m_pProfileLayer->setVisible(var); }

private:
	
	int FriendDataParser();
	void LoadFriendProfileImage();

	virtual void onRequestAchieveCompleted(HttpClient *sender, HttpResponse * reponse) override;
	virtual void onRequestImgCompleted(HttpClient *sender, HttpResponse *response) override;
	virtual void onRequestMoveCountCompleted(HttpClient *sender, HttpResponse *response) override;

	Layer *							m_pProfileLayer;
	std::string						m_sFriendListLog;
	std::vector<CGameData *>		m_vFriendLists;

	HttpRequest * Img_Request;
	HttpRequest * Achieve_Request;
	HttpRequest * MoveCount_Request;

	cocos2d::ui::ScrollView * m_pScrollView;

	int m_nLoadCount;
	bool m_isLoadComplete;

	// Sort
	static int m_nTempCheckClearStage;
	int m_nSortStageNumber;

	friend bool SortMoveCount(CGameData *, CGameData *);
	friend bool SortStageClear(CGameData *, CGameData *);

	void SortFacebookData();
	void CheckClearStage();
};