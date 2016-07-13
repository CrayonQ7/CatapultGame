#include "AdventureModeScene.h"

USING_NS_CC;

cocos2d::Scene * AdventureModeScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = AdventureModeScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool AdventureModeScene::init()
{
	return false;
}
