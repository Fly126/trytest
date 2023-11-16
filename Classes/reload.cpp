#include "reload.h"
PlistParse* PlistParse::getInstance(PlistParse* ptr) {
	if (!ptr) {
		PlistParse* p = new PlistParse();
		if (!p->init()) {
			delete p;
			return nullptr;
		}
		ptr = p;
	}
	return ptr;
}
bool PlistParse::init() {
	auto file = FileUtils::getInstance();
	file->setWritablePath("E:/cocos_example/resume/Resources/utf8.plist");
	log("%s", file->getWritablePath().c_str());

	return true;
}

void PlistParse::click_setting() {
	auto str = FileUtils::getInstance()->getWritablePath();
	auto d = FileUtils::getInstance()->getValueMapFromFile(str);
	ValueMap vm = d;
	if (vm["sound_key"].asBool()) {
		bool temp = false;
		vm["sound_key"] = Value(temp);
	}
	else {
		bool temp = true;
		vm["sound_key"] = Value(temp);
	}
	log("%d", vm["sound_key"].asBool());
	FileUtils::getInstance()->writeToFile(vm, str);
}
bool PlistParse::check_music(std::string music) {
	auto str = FileUtils::getInstance()->getWritablePath();
	auto d = FileUtils::getInstance()->getValueMapFromFile(str);
	if (d[music].asBool()) {
		return true;
	}
	else {
		return false;
	}
}