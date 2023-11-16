#include "Help.h"
#pragma execution_character_set("utf-8")
Scene* HelpScene::createScene() {
	auto s = Scene::create();
	auto l = HelpScene::create();
	s->addChild(l);
	return s;
}
bool HelpScene::init() {
	if (!BaseLayer::init()) {
		return false;
	}
	Label* label = Label::createWithTTF("寫不出來，還是你幫助我吧!拜託", "fonts/msjhbd.ttc", 48);
	auto sz = Director::getInstance()->getVisibleSize();
	label->setPosition(Vec2(sz.width / 2, sz.height / 2));
	addChild(label);


	return true;
}