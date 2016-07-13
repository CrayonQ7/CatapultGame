#include "VersusModeScene.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace CocosDenshion;

cocos2d::Scene * VersusModeScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = VersusModeScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool VersusModeScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	flag = 0;
	player1 = NULL;
	player2 = NULL;
	prop1 = NULL;
	prop2 = NULL;
	background = NULL;
	
	selectGateMenu = SelectGate::create();
	selectGateMenu->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 20);
	addChild(selectGateMenu, 2);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/VersusModeScene.plist");


	// * -----------------------背景图片---------------------------------- *
	auto backGround = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("background.png"));
	backGround->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backGround, 0);
	
	displayPlayer();

	auto audio = SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("music/BGM_1.mp3");
	audio->playBackgroundMusic("music/gateMap.wav", true);
	return true;
}

// * -----------------------------------------------------显示函数-------------------------------------------------------- *
void VersusModeScene::displayPlayer()
{
	// * -----------------------加载玩家图片---------------------------------- *
	player1MenuItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("player1.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("player1.png")),
		CC_CALLBACK_1(VersusModeScene::player1Callback, this));
	player1MenuItem->setPosition(Vec2(visibleSize.width / 2 - player1MenuItem->getContentSize().width + origin.x - 15, player1MenuItem->getContentSize().height + origin.y));

	player2MenuItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("player2.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("player2.png")),
		CC_CALLBACK_1(VersusModeScene::player2Callback, this));
	player2MenuItem->setPosition(Vec2(visibleSize.width / 2 + player1MenuItem->getContentSize().width + origin.x + 15, player1MenuItem->getContentSize().height + origin.y));

	auto menuPlayer = Menu::create(player1MenuItem, player2MenuItem, NULL);
	menuPlayer->setPosition(Vec2::ZERO);
	addChild(menuPlayer, 1);
}

void VersusModeScene::displayGate()
{
	// * -----------------------加载英雄图片---------------------------------- *

	auto gateOneItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_1_1.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_1_2.png")),
		CC_CALLBACK_1(VersusModeScene::gateOneCallBack, this));

	auto gateTwoItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_2_1.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_2_2.png")),
		CC_CALLBACK_1(VersusModeScene::gateTwoCallBack, this));

	auto gateThreeItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_3_1.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_3_2.png")),
		CC_CALLBACK_1(VersusModeScene::gateThreeCallBack, this));

	selectGateMenu->addMenuItem(gateOneItem);
	selectGateMenu->addMenuItem(gateTwoItem);
	selectGateMenu->addMenuItem(gateThreeItem);
}

void VersusModeScene::displayPropGate()
{
	// * -----------------------加载道具图片---------------------------------- *

	auto propOneItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop_1_1.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop_1_2.png")),
		CC_CALLBACK_1(VersusModeScene::propOneCallback, this));

	auto propTwoItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop_2_1.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop_2_2.png")),
		CC_CALLBACK_1(VersusModeScene::propTwoCallback, this));

	auto propThreeItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop_3_1.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop_3_2.png")),
		CC_CALLBACK_1(VersusModeScene::propThreeCallback, this));

	selectGateMenu->addMenuItem(propOneItem);
	selectGateMenu->addMenuItem(propTwoItem);
	selectGateMenu->addMenuItem(propThreeItem);
}

void VersusModeScene::displayMapGate()
{
	// * -----------------------加载地图图片---------------------------------- *

	auto mapOneItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("map_1_1.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("map_1_2.png")),
		CC_CALLBACK_1(VersusModeScene::mapOneCallback, this));

	auto mapTwoItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("map_2_1.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("map_2_2.png")),
		CC_CALLBACK_1(VersusModeScene::mapTwoCallback, this));

	auto mapThreeItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("map_3_1.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("map_3_2.png")),
		CC_CALLBACK_1(VersusModeScene::mapThreeCallback, this));

	selectGateMenu->addMenuItem(mapOneItem);
	selectGateMenu->addMenuItem(mapTwoItem);
	selectGateMenu->addMenuItem(mapThreeItem);
}

void VersusModeScene::displayButton()
{
	start = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("startNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("startSelected.png")),
		CC_CALLBACK_1(VersusModeScene::startCallback, this));
	start->setPosition(Vec2(visibleSize.width / 2 + origin.x - start->getContentSize().width / 2, start->getContentSize().height + origin.y + 50));
	restart = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("restartNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("restartSelected.png")),
		CC_CALLBACK_1(VersusModeScene::restartCallback, this));
	restart->setPosition(Vec2(visibleSize.width / 2 + origin.x + restart->getContentSize().width / 2, restart->getContentSize().height + origin.y + 50));
	auto menu = Menu::create(start, restart, NULL);
	menu->setPosition(Vec2::ZERO);
	addChild(menu, 1);
}

// * -----------------------------------------------------点击玩家-------------------------------------------------------- *
void VersusModeScene::player1Callback(Ref * pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("music/button.wav", false, 1.0f, 1.0f, 1.0f);
	if (flag != 0) return;  // 如果当前正在选人，就不能再点击玩家了
	flag = 1;
	player1MenuItem->setScale(1.5f);
	displayGate();
}

void VersusModeScene::player2Callback(Ref * pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("music/button.wav", false, 1.0f, 1.0f, 1.0f);
	if (flag != 0) return;
	flag = 2;
	player2MenuItem->setScale(1.5f);
	displayGate();
}


// * -----------------------------------------------------点击英雄-------------------------------------------------------- *
void VersusModeScene::gateOneCallBack(Ref * pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("music/Gate_1_selected.mp3", false, 1.0f, 1.0f, 1.0f);
	if (flag == 1)
	{
		if (player1 != NULL) 
			pl1->removeFromParent();
		pl1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_1.png"));
		pl1->setPosition(Vec2(20 + pl1->getContentSize().width + origin.x, pl1->getContentSize().height/2 + origin.y));
		addChild(pl1, 1);
		player1 = 1;
	}
	else if (flag == 2) {
		if (player2 != NULL)
			pl2->removeFromParent();
		pl2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_1.png"));
		pl2->setPosition(Vec2(visibleSize.width - 20 - pl2->getContentSize().width + origin.x, pl2->getContentSize().height/2 + origin.y));
		addChild(pl2, 1);
		player2 = 1;
	}
	selectGateMenu->clearGate();
	displayPropGate();  // 显示选道具菜单
}

void VersusModeScene::gateTwoCallBack(Ref * pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("music/Gate_2_selected.mp3", false, 1.0f, 1.0f, 1.0f);
	if (flag == 1)
	{
		if (player1 != NULL) pl1->removeFromParent();
		pl1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_2.png"));
		pl1->setPosition(Vec2(20 + pl1->getContentSize().width + origin.x, pl1->getContentSize().height/2 + origin.y));
		addChild(pl1, 1);
		player1 = 2;
	}
	else if (flag == 2) {
		if (player2 != NULL) pl2->removeFromParent();
		pl2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_2.png"));
		pl2->setPosition(Vec2(visibleSize.width - 20 - pl2->getContentSize().width + origin.x, pl2->getContentSize().height/2 + origin.y));
		addChild(pl2, 1);
		player2 = 2;
	}
	selectGateMenu->clearGate();
	displayPropGate();  // 显示选道具菜单
}

void VersusModeScene::gateThreeCallBack(Ref * pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("music/Gate_3_selected.mp3", false, 1.0f, 1.0f, 1.0f);
	if (flag == 1)
	{
		if (player1 != NULL) pl1->removeFromParent();
		pl1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_3.png"));
		pl1->setPosition(Vec2(20 + pl1->getContentSize().width + origin.x, pl1->getContentSize().height/2 + origin.y));
		addChild(pl1, 1);
		player1 = 3;
	}
	else if (flag == 2) {
		if (player2 != NULL) pl2->removeFromParent();
		pl2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_3.png"));
		pl2->setPosition(Vec2(visibleSize.width - 20 - pl2->getContentSize().width + origin.x, pl2->getContentSize().height/2 + origin.y));
		addChild(pl2, 1);
		player2 = 3;
	}
	selectGateMenu->clearGate();
	displayPropGate();  // 显示选道具菜单
}



// * -----------------------------------------------------点击道具-------------------------------------------------------- *

void VersusModeScene::propOneCallback(Ref * pSender)
{
	if (flag == 1)
	{
		if (prop1 != NULL) pr1->removeFromParent();
		pr1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop_1.png"));
		pr1->setPosition(Vec2(pr1->getContentSize().width + origin.x, pr1->getContentSize().height / 2 + origin.y + 50));
		addChild(pr1, 1);
		prop1 = "Prop_1";
		player1MenuItem->setScale(1.0f);
	}
	else if (flag == 2)
	{
		if (prop2 != NULL) pr2->removeFromParent();
		pr2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop_1.png"));
		pr2->setPosition(Vec2(visibleSize.width - pr2->getContentSize().width + origin.x, pr2->getContentSize().height / 2 + origin.y + 50));
		addChild(pr2, 1);
		prop2 = "Prop_1";
		player2MenuItem->setScale(1.0f);
	}
	selectGateMenu->clearGate();  // 隐藏选道具菜单
	if (player1 != NULL && player2 != NULL)
		displayMapGate();
	else flag = 0;
}

void VersusModeScene::propTwoCallback(Ref * pSender)
{
	if (flag == 1)
	{
		if (prop1 != NULL) pr1->removeFromParent();
		pr1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop_2.png"));
		pr1->setPosition(Vec2(pr1->getContentSize().width + origin.x, pr1->getContentSize().height / 2 + origin.y + 50));
		addChild(pr1, 1);
		prop1 = "Prop_2";
		player1MenuItem->setScale(1.0f);
	}
	else if (flag == 2)
	{
		if (prop2 != NULL) pr2->removeFromParent();
		pr2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop_2.png"));
		pr2->setPosition(Vec2(visibleSize.width - pr2->getContentSize().width + origin.x, pr2->getContentSize().height / 2 + origin.y + 50));
		addChild(pr2, 1);
		prop2 = "Prop_2";
		player2MenuItem->setScale(1.0f);
	}
	selectGateMenu->clearGate();  // 隐藏选道具菜单
	if (player1 != NULL && player2 != NULL)
		displayMapGate();
	else flag = 0;
}

void VersusModeScene::propThreeCallback(Ref * pSender)
{
	if (flag == 1)
	{
		if (prop1 != NULL) pr1->removeFromParent();
		pr1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop_3.png"));
		pr1->setPosition(Vec2(pr1->getContentSize().width + origin.x, pr1->getContentSize().height / 2 + origin.y + 50));
		addChild(pr1, 1);
		prop1 = "Prop_3";
		player1MenuItem->setScale(1.0f);
	}
	else if (flag == 2)
	{
		if (prop2 != NULL) pr2->removeFromParent();
		pr2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop_3.png"));
		pr2->setPosition(Vec2(visibleSize.width - pr2->getContentSize().width + origin.x, pr2->getContentSize().height / 2 + origin.y + 50));
		addChild(pr2, 1);
		prop2 = "Prop_3";
		player2MenuItem->setScale(1.0f);
	}
	selectGateMenu->clearGate();  // 隐藏选道具菜单
	if (player1 != NULL && player2 != NULL)
		displayMapGate();
	else flag = 0;
}

// * -----------------------------------------------------点击地图-------------------------------------------------------- *

void VersusModeScene::mapOneCallback(Ref * pSender)
{
	if (background != NULL) bg->removeFromParent();
	bg = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("map_1_2.png"));
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + bg->getContentSize().height/2));
	addChild(bg, 1);
	background = 1;
	selectGateMenu->clearGate();
	displayButton();
}

void VersusModeScene::mapTwoCallback(Ref * pSender)
{
	if (background != NULL) bg->removeFromParent();
	bg = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("map_2_2.png"));
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + bg->getContentSize().height/2));
	addChild(bg, 1);
	background = 2;
	selectGateMenu->clearGate();
	displayButton();
}

void VersusModeScene::mapThreeCallback(Ref * pSender)
{
	if (background != NULL) bg->removeFromParent();
	bg = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("map_3_2.png"));
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + bg->getContentSize().height/2));
	addChild(bg, 1);
	background = 3;
	selectGateMenu->clearGate();
	displayButton();
}

// * -----------------------------------------------------点击按钮-------------------------------------------------------- *

void VersusModeScene::startCallback(Ref * pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("music/button.wav", false, 1.0f, 1.0f, 1.0f);
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	Director::getInstance()->replaceScene(GameScene::createScene(player1, prop1, player2, prop2, background));
}

void VersusModeScene::restartCallback(Ref * pSender)
{
	flag = 0;
	player1 = NULL;
	player2 = NULL;
	prop1 = NULL;
	prop2 = NULL;
	background = NULL;
	pl1->removeFromParent();
	pl2->removeFromParent();
	pr1->removeFromParent();
	pr2->removeFromParent();
	bg->removeFromParent();
	start->removeFromParent();
	restart->removeFromParent();
}
