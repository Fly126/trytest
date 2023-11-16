#ifndef HUD_001
#define HUD_001
#include "cocos2d.h"
USING_NS_CC;
class HUDLayer :public Layer {
public:
	static HUDLayer* getInstance();
	bool init();
	//¸ê®Æ
	int HP, score_;
	Label* lb, * scores;
	Vector<Sprite*> vec;
	void hud_leave();
	void life_pic();
	void add_score();
};

#endif