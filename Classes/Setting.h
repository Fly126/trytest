#ifndef SETTING
#define SETTING
#include "cocos2d.h"
#include "SystemHead.h"
#include "BaseLayer.h"
USING_NS_CC;
class SettingScene :public BaseLayer {
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SettingScene);

	void click(Ref*);
	PlistParse* ptr;
};

#endif