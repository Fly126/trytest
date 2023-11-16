#ifndef HELP
#define HELP
#include "BaseLayer.h"
#include "cocos2d.h"
USING_NS_CC;
class HelpScene : public BaseLayer {
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(HelpScene);
};
#endif