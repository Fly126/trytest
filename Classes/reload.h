#ifndef RELOAD
#define RELOAD
#include "cocos2d.h"
USING_NS_CC;
class PlistParse {
public:
	static PlistParse* getInstance(PlistParse*);

	bool init();

	void click_setting();
	bool check_music(std::string);
};

#endif