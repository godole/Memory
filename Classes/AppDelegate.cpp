#include "AppDelegate.h"
#include "Scene_Title.h"
#include "DataManager.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		glview = GLViewImpl::create("My Game");
		director->setOpenGLView(glview);
		glview->setFrameSize(1280, 720);
		//director->setContentScaleFactor(1.0f);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	glview->setDesignResolutionSize(1280, 720, ResolutionPolicy::FIXED_HEIGHT);
    // create a scene. it's an autorelease object
	/*CDataManager::getInstance()->LoadMapData(
		StringUtils::format("map/data/map1-1.txt"));*/
	auto scene = Scene_Title::createScene();
	//auto scene = Scene_SelectState::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
