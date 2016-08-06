#include "GameScene.h"
#include "GameLayer.h"
#include "OperateLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

cocos2d::Scene * GameScene::createScene(int pl1, int pr1, int pl2, int pr2, int bg,  float bv, float ev, int bgm)
{
	auto scene = Scene::create();
	auto gameLayer = GameLayer::create(pl1, pr1, pl2, pr2, bg, bv, ev, bgm);
	auto operateLayer = OperateLayer::create(bgm, 1);
	operateLayer->setHero1(gameLayer->getHero1());
	operateLayer->setHero2(gameLayer->getHero2());
	scene->addChild(gameLayer, 0, 0);
	scene->addChild(operateLayer, 1, 1);
	return scene;
}

cocos2d::Scene * GameScene::createScene(const char * pl, const char * pr, const char * bg)
{
	return nullptr;
}