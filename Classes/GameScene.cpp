#include "GameScene.h"
#include "GameLayer.h"
#include "OperateLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

cocos2d::Scene * GameScene::createScene(int pl1, int pr1, int pl2, int pr2, int bg)
{
	auto scene = Scene::create();
	auto gameLayer = GameLayer::create(pl1, pr1, pl2, pr2, bg);
	auto operateLayer = OperateLayer::create();
	operateLayer->setHero1(gameLayer->getHero1());
	operateLayer->setHero2(gameLayer->getHero2());
	scene->addChild(gameLayer, 0);
	scene->addChild(operateLayer, 1);
	return scene;
}

cocos2d::Scene * GameScene::createScene(const char * pl, const char * pr, const char * bg)
{
	return nullptr;
}