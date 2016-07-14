#include "GameScene.h"
#include "GameLayer.h"
#include "OperateLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

cocos2d::Scene * GameScene::createScene(int pl1, const char * pr1, int pl2, const char* pr2, int bg)
{
	auto scene = Scene::create();
	auto gameLayer = GameLayer::create(pl1, pl2, bg);
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