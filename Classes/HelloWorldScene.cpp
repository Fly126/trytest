#pragma execution_character_set("utf-8")

#include "HelloWorldScene.h"
#include "SystemHead.h"
#include "HomeMenu.h"


Scene* HelloWorld::createScene() {
	auto s = Scene::create();
	auto l = HelloWorld::create();
	s->addChild(l);
	return s;
}
bool HelloWorld::init() {
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* bg = Sprite::create("1.jpg");
	auto bg_size = bg->getContentSize();
	log("%f,,%f,,,%f", bg_size.width, bg_size.height, visibleSize.width);
	bg->setScale( visibleSize.width / bg_size.width , visibleSize.height / bg_size.height);
	bg->setAnchorPoint(Vec2(0.5, 0.5));
	bg->setPosition(Vec2(800, 475));
	addChild(bg);
	Loaded = 0;
	Director::getInstance()->getTextureCache()->addImageAsync("BugAnt,png", std::bind(&HelloWorld::loadingTextureCallBack, this, std::placeholders::_1));
	Director::getInstance()->getTextureCache()->addImageAsync("BugSpider,png", std::bind(&HelloWorld::loadingTextureCallBack, this, std::placeholders::_1));
	Director::getInstance()->getTextureCache()->addImageAsync("Star,png", std::bind(&HelloWorld::loadingTextureCallBack, this, std::placeholders::_1));

	hold = new std::thread(&HelloWorld::loadingAudio, this);



	return true;
}
void HelloWorld::loadingTextureCallBack(Texture2D* texture) {
	switch (Loaded++) {
	case 0:
		log("ok1");
		break;
	case 1:
		log("ok2");
		break;
	case 2:
		log("ok3");
		this->schedule(CC_SCHEDULE_SELECTOR(HelloWorld::delaycall), 1, 1, 3);
	}
}
void HelloWorld::delaycall(float dt) {
	auto scene = HomeMenuLayer::createScene();
	Director::getInstance()->replaceScene(scene);
}
void HelloWorld::loadingAudio() {
	AudioEngine::preload("BugDead.mp3");
	AudioEngine::preload("BugEnterHole.mp3");
	AudioEngine::preload("game.mp3");
	AudioEngine::preload("menubg.mp3");
	AudioEngine::play2d("menubg.mp3", true);


	log("讀取完畢");
}
void HelloWorld::onExit() {
	Layer::onExit();
	hold->join();
	CC_SAFE_DELETE(hold);
	this->unschedule(CC_SCHEDULE_SELECTOR(HelloWorld::delaycall));
	log("刪除完畢");
	
}