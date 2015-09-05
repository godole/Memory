#pragma once
#include <string>
#include "cocos2d.h"
#include "network\HttpClient.h"

using namespace cocos2d::network;

USING_NS_CC;

class CNetwork
{
public:
	virtual void GetDataFromJNI() = 0;

	virtual void onRequestAchieveCompleted(HttpClient *sender, HttpResponse * reponse) = 0;
	virtual void onRequestImgCompleted(HttpClient *sender, HttpResponse *response) = 0;
	virtual void onRequestMoveCountCompleted(HttpClient *sender, HttpResponse *response) = 0;
};