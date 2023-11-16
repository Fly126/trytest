#ifndef HOME
#define HOME

#include "cocos2d.h"
USING_NS_CC;
#include "Setting.h"
#include "GamePlay.h"
#include "Help.h"
typedef enum {
	MenuItemStart,
	MenuItemSetting,
	MenuItemHelp,
	MenuItemRank
}ActionType;

class HomeMenuLayer :public Layer {
public:
	static Scene* createScene();
	bool init();
	CREATE_FUNC(HomeMenuLayer);

	virtual void onEnterTransitionDidFinish() override;
	void menuItemCallBack(Ref*);
	Size vs;
	Vec2 origin;
};
#endif // !HOME
