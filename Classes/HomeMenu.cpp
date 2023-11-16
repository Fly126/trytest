#include "HomeMenu.h"
#include "SystemHead.h"
#include "Setting.h"
#include "Help.h"
#include "GamePlay.h"
#include "rank.h"
#pragma execution_character_set("utf-8")
Scene* HomeMenuLayer::createScene() {
	auto s = Scene::create();
	auto l = HomeMenuLayer::create();
	s->addChild(l);
	return s;
}

bool HomeMenuLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	
	vs = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	Sprite* bg = Sprite::create("MainSceneBg.jpg");
	bg->setPosition(Vec2(vs.width / 2, vs.height / 2));
	bg->setAnchorPoint(Vec2(0.5, 0.5));
	auto te = bg->getContentSize();
	bg->setScale(vs.width / te.width, vs.height / te.height);
	addChild(bg);

	auto item1 = MenuItemImage::create("PlayButton.png", "PlayButton.png", CC_CALLBACK_1(HomeMenuLayer::menuItemCallBack, this));
	item1->setTag(MenuItemStart);
	auto item2 = MenuItemFont::create("設置", CC_CALLBACK_1(HomeMenuLayer::menuItemCallBack, this));
	item2->setTag(MenuItemSetting);
	auto item3 = MenuItemFont::create("幫助", CC_CALLBACK_1(HomeMenuLayer::menuItemCallBack, this));
	item3->setTag(MenuItemHelp);
	auto item4 = MenuItemFont::create("排名", CC_CALLBACK_1(HomeMenuLayer::menuItemCallBack, this));
	item4->setTag(MenuItemRank);
	Menu* menu = Menu::create(item1, item2, item3, item4, nullptr);
	menu->alignItemsVertically();
	menu->setPosition(Vec2(vs.width / 2, vs.height / 2));
	menu->setAnchorPoint(Vec2(0.5, 0.5));
	addChild(menu);

	return true;
}
void HomeMenuLayer::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
	
}
void HomeMenuLayer::menuItemCallBack(Ref* r) {
	Scene* sc = nullptr;
	MenuItem* m = (MenuItem*)r;
	switch (m->getTag()) {
	case MenuItemStart:
		log("開始");
		AudioEngine::stopAll();
		sc = GameScene::createScene();
		break;
	case MenuItemSetting:
		log("設置");
		sc = SettingScene::createScene();
		break;
	case MenuItemHelp:
		sc = HelpScene::createScene();
		log("幫助");
		break;
	case MenuItemRank:
		sc = RankShow::createScene();
		log("排名");
		break;
	}
	if (sc) {
		Director::getInstance()->pushScene(sc);
	}
}