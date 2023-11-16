#include "Ant.h"
AntSp::AntSp() {
	auto ant = SpriteFrameCache::getInstance()->getSpriteFrameByName("sp000.png");
	this->initWithSpriteFrame(ant);
}

void AntSp::changeTexture() {
	this->stopAllActions();
	auto ant = SpriteFrameCache::getInstance()->getSpriteFrameByName("sp002.png");
	this->initWithSpriteFrame(ant);
	auto fadeOut = FadeOut::create(2.0f);
	auto rotate = RotateBy::create(2.0f, 360);
	auto spawn = Spawn::create(rotate, fadeOut, nullptr);
	this->runAction(spawn);
	this->setLocalZOrder(0);
}