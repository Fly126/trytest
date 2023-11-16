#ifndef BASELAYER
#define BASELAYER
#include "cocos2d.h"
USING_NS_CC;
class BaseLayer :public Layer {
public:
	virtual bool init();

	void menuCallBack(Ref*);
	void onEnterTransitionDidFinish();
};


#endif