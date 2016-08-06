#include "AMGameScene.h"
#include "AMGameLayer.h"
#include "OperateLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;
cocos2d::Scene * AMGameScene::createScene(int pl, int bg, int bgm)
{
	auto scene = Scene::create();
	auto amGameLayer = AMGameLayer::create(pl, bg, bgm);
	auto operateLayer = OperateLayer::create(bgm, 2);
	operateLayer->setAMHero(amGameLayer->getAMHero());
	scene->addChild(amGameLayer, 0, 0);
	scene->addChild(operateLayer, 1, 1);
	return scene;
}
