#ifndef GAMESTART
#define GAMESTART
#include "cocos2d.h"
USING_NS_CC;
#include "Ant.h"
#include "HUD.h"
#include "SystemHead.h"
class GameScene :public Layer {
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);
	void menuCallBack(Ref*);
	Vector<AntSp*> vec_ant;
	Vector<AntSp*> vec_ant_del;
	void gen_ants(float);
	Size sz;
	//move
	void move_ants(float);
	//À»±þ
	virtual bool onTouchBegan(Touch* touch, Event* unused_event) override;
	//HUD
	HUDLayer* h;
	void update(float);
	//­µ¼Ö
	PlistParse* ptr;
};

#endif