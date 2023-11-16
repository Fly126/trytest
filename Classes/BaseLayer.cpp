#include "BaseLayer.h"
#pragma execution_character_set("utf-8")
bool BaseLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	auto sz = Director::getInstance()->getVisibleSize();
	auto bg = Sprite::create("2.jpg");
	bg->setPosition(Vec2(sz.width / 2, sz.height / 2));
	bg->setAnchorPoint(Vec2(0.5, 0.5));
	auto sz_bg = bg->getContentSize();
	bg->setScale(sz.width / sz_bg.width, sz.height / sz_bg.height);
	addChild(bg);

	auto m1 = MenuItemFont::create("§¹¬ü", std::bind(&BaseLayer::menuCallBack, this, std::placeholders::_1));
	auto menu = Menu::create(m1, nullptr);
	menu->setPosition(Vec2(sz.width / 2, 30));
	addChild(menu);

	return true;
}

void BaseLayer::menuCallBack(Ref* r) {
	Director::getInstance()->popScene();
}

void BaseLayer::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
}