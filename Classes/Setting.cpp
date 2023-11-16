#include "Setting.h"
#pragma execution_character_set("utf-8")
Scene* SettingScene::createScene() {
	auto s = Scene::create();
	auto l = SettingScene::create();
	s->addChild(l);
	return s;
}
bool SettingScene::init() {
	if (!BaseLayer::init()) {
		return false;
	}

	auto m = MenuItemFont::create("設置測試", CC_CALLBACK_1(SettingScene::click, this));
	m->setFontSizeObj(56);
	auto menu = Menu::create(m, nullptr);
	menu->setPosition(Vec2(800, 475));
	addChild(menu);

	return true;
}
void SettingScene::click(Ref* r) {
	PlistParse::getInstance(ptr);
	ptr->click_setting();
	delete ptr;
	ptr = nullptr;
}