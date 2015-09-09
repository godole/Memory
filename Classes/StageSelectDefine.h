#pragma once
#include "cocos2d.h"

#define STAGE_NUMBER 30
#define FACEBOOK_LOADIMAGESIZE "120"
#define ScrollValue 15

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform\android\jni\JniHelper.h"
#endif

#define HTTPREQUEST_SEND(Http,Url) \
	Http->setUrl(Url.c_str()); \
	HttpClient::getInstance()->send(Http)

#include "Network.h"
#include "DataManager.h"
#include <memory>
#include <string>

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

USING_NS_CC;
