#include "GamePlay.h"
#include <ctime>
#include <fstream>

#pragma execution_character_set("utf-8")
Scene* GameScene::createScene() {
	auto s = Scene::create();
	auto l = GameScene::create();
	s->addChild(l, -1);
	return s;
}
bool GameScene::init() {
	if (!Layer::init()) {
		return false;
	}
	auto h1 = HUDLayer::getInstance();
	addChild(h1, 0);
	h = HUDLayer::getInstance();
	
	//背景//新增判斷
	PlistParse::getInstance(ptr);
	if (ptr->check_music(SOUND_KEY)) {
		AudioEngine::play2d("game.mp3");
	}
	delete ptr;
	ptr = nullptr;
	

	auto bg = Sprite::create("PlaySceneBg.jpg");
	sz = Director::getInstance()->getVisibleSize();
	bg->setPosition(Vec2(sz.width / 2, sz.height / 2));
	bg->setAnchorPoint(Vec2(0.5, 0.5));
	auto te = bg->getContentSize();
	bg->setScale(sz.width / te.width, sz.height / te.height);
	addChild(bg, -1);
	//離開按鈕
	Sprite* exit = Sprite::create("ExitButton.png");
	auto m1 = MenuItemSprite::create(exit, nullptr, CC_CALLBACK_1(GameScene::menuCallBack, this));
	Menu* menu = Menu::create(m1, nullptr);
	menu->setPosition(Vec2(sz.width - 100, 50));
	addChild(menu);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ant.plist");

	//怪物隨機生成
	schedule(CC_SCHEDULE_SELECTOR(GameScene::gen_ants, this), 1);
	schedule(CC_SCHEDULE_SELECTOR(GameScene::move_ants, this), 1);
	//點擊
	EventListenerTouchOneByOne* eventlistener = EventListenerTouchOneByOne::create();
	eventlistener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	eventlistener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventlistener, this);

	scheduleUpdate();//生命0離開
	

	return true;
}
void GameScene::menuCallBack(Ref* r) {
	AudioEngine::stopAll();
	AudioEngine::play2d("menubg.mp3");
	unschedule(CC_SCHEDULE_SELECTOR(GameScene::gen_ants, this));
	unschedule(CC_SCHEDULE_SELECTOR(GameScene::move_ants, this));
	h->hud_leave();
	Director::getInstance()->popScene();
}
void GameScene::gen_ants(float dt) {
	if (vec_ant.size() < 10) {
		AntSp* ant = new AntSp();
		vec_ant.pushBack(ant);
		ant->setPosition(Vec2(800, 475));
		addChild(ant, 10);
	}
	if (vec_ant_del.size() > 0) {
		Vector<AntSp*> temp;
		for (auto& c : vec_ant_del) {
			if (!c->getNumberOfRunningActions()) {
				temp.pushBack(c);
			}
		}
		for (auto& c : temp) {
			removeChild(c);
			vec_ant_del.eraseObject(c);
			vec_ant.eraseObject(c);
		}
	}
}
void GameScene::move_ants(float dt) {
	Vector<AntSp*> temp;
	if (!vec_ant.empty()) {
		for (auto c : vec_ant) {
			if (!c->getNumberOfRunningActions()) {
				int x = CCRANDOM_MINUS1_1() * 10000;
				int y = CCRANDOM_MINUS1_1() * 10000;
				auto move = MoveTo::create(20, Vec2(x, y));
				c->runAction(move);
			}
			
			auto pos = c->getPosition();
			if (pos.x > sz.width || pos.x < 0 || pos.y>sz.height || pos.y < 0) {
				temp.pushBack(c);
				h->life_pic();
				log("%d", h->HP);
			}
		}
		for (auto c : temp) {
			removeChild(c);
			vec_ant.eraseObject(c);
		}
	}
}
bool GameScene::onTouchBegan(Touch* touch, Event* unused_event) {
	Vec2 pos = touch->getLocation();
	for (auto& c : vec_ant) {
		if (c->getLocalZOrder() == 10 && c->getBoundingBox().containsPoint(pos)) {
			AudioEngine::play2d("BugDead.mp3");
			h->add_score();
			c->changeTexture();
			vec_ant_del.pushBack(c);
			break;
		}
	}

	return true;
}
void GameScene::update(float dt) {
	if (h->HP <= 0) {
		time_t now = time(0);
		auto str = localtime(&now);
		auto str_char = std::to_string(str->tm_mon + 1) + "/" + std::to_string(str->tm_mday);

		std::ofstream outFile;
		outFile.open(CSV_FILE_PATH, std::ios::app);
		outFile << "time:" << str_char.c_str() << ",score:" << std::to_string(h->score_).c_str() << '\n';
		outFile.close();

		menuCallBack(this);
	}
}