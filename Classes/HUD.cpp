#include "HUD.h"
#pragma execution_character_set("utf-8")
static HUDLayer* hud = nullptr;
HUDLayer* HUDLayer::getInstance() {
	HUDLayer* l = nullptr;
	if (!hud) {
		l = new HUDLayer();
		if (!l->init()) {
			CC_SAFE_DELETE(l);
			return nullptr;
		}
		l->autorelease();
		hud = l;
	}
	return hud;
}
bool HUDLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	//初始化
	Size sz = Director::getInstance()->getVisibleSize();
	HP = 5;
	score_ = 0;
	for (auto i = 1; i <= 5; i++) {
		auto sp = Sprite::create("Star.png");
		vec.pushBack(sp);
		sp->setPosition(Vec2(sz.width - i * 30, sz.height - 30));
		addChild(sp, 1);
	}
	lb = Label::createWithTTF("", "fonts/msjh.ttc", 24);
	std::string str = StringUtils::format("生命:%d", HP);
	lb->setString(str);
	lb->setPosition(Vec2(50, sz.height - 30));
	addChild(lb, 1);
	scores = Label::createWithTTF("", "fonts/msjh.ttc", 24);
	std::string str_score = StringUtils::format("分數:%d", score_);
	scores->setString(str_score);
	scores->setPosition(Vec2(50, sz.height - 60));
	addChild(scores, 1);
	return true;
}
void HUDLayer::hud_leave() {
	hud = nullptr;
}
void HUDLayer::life_pic() {
	HP -= 1;
	std::string str = StringUtils::format("生命:%d", HP);
	lb->setString(str);
	if (HP >= 0) {
		removeChild(vec.at(HP));
		vec.popBack();
	}		
}
void HUDLayer::add_score() {
	score_ += 100;
	std::string str_score = StringUtils::format("分數:%d", score_);
	scores->setString(str_score);
}