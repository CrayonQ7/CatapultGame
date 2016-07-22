#include "VersusModeScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ConfigScene.h"
USING_NS_CC;
using namespace CocosDenshion;

int VersusModeScene::curBgm = 0;
float VersusModeScene::backgroundVolume = 0.5f;
float VersusModeScene::effectVolume = 0.5f;

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

	// * -----------------------初始化---------------------------------- *
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	flag = 0;
	player1 = 0;
	player2 = 0;
	prop1 = 0;
	prop2 = 0;
	background = 0;
	backgroundVolume = 0.5f;
	effectVolume = 0.5f;
	curBgm = 0;

	selectGateMenu = SelectGate::create();
	selectGateMenu->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 20);
	addChild(selectGateMenu, 2);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/VersusModeScene.plist");

	// * -----------------------背景图片---------------------------------- *
	auto backGround = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("background.png"));
	backGround->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	auto scaleX = backGround->getTextureRect().getMaxX();
	auto scaleY = backGround->getTextureRect().getMaxY();
	backGround->setScaleX(visibleSize.width / scaleX);
	backGround->setScaleY(visibleSize.height / scaleY);
	this->addChild(backGround, 0);
	
	//  * -----------------------可以跳转到设置界面的按钮---------------------------------- *
	configItem = MenuItemSprite::create(
		Sprite::create("icons/ConfigItemNormal.png"),
		Sprite::create("icons/ConfigItemSelected.png"),
		CC_CALLBACK_1(VersusModeScene::configMenuCallback, this));
	configItem->setPosition(Vec2(origin.x + visibleSize.width - configItem->getContentSize().width,
		origin.y + visibleSize.height - configItem->getContentSize().height));
	auto menu = Menu::create(configItem, NULL);
	menu->setPosition(Vec2::ZERO);
	addChild(menu, 1);

	// * -----------------------声音开关按钮---------------------------------- *
	soundOn = MenuItemSprite::create(
		Sprite::create("icons/SoundOn.png"),
		Sprite::create("icons/SoundOn.png"));
	soundOff = MenuItemSprite::create(
		Sprite::create("icons/SoundOff.png"),
		Sprite::create("icons/SoundOff.png"));
	soundStateToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(VersusModeScene::soundCallback, this), soundOn, soundOff, NULL);
	soundStateToggle->setPosition(Vec2(origin.x + soundStateToggle->getContentSize().width,
		origin.y + visibleSize.height - soundStateToggle->getContentSize().height));
	soundState = Menu::create(soundStateToggle, NULL);
	soundState->setPosition(Vec2::ZERO);
	addChild(soundState, 1);

	// * -----------------------加载玩家---------------------------------- *
	displayPlayer();

	// * -----------------------加载音效---------------------------------- *
	//auto audio = SimpleAudioEngine::getInstance();
	return true;
}

void VersusModeScene::onEnter() 
{
	Layer::onEnter();
	if (backgroundVolume <= 0.01 && effectVolume <= 0.01) soundStateToggle->setSelectedIndex(1);
	else soundStateToggle->setSelectedIndex(0);
	auto audio = SimpleAudioEngine::getInstance();
	//char file[20];
	//sprintf(file, "music/BGM_%d.mp3", curBgm + 1);
	audio->playBackgroundMusic("music/gateMap.mp3", true);
	audio->setEffectsVolume(effectVolume);
	audio->setBackgroundMusicVolume(backgroundVolume);
}


// * -----------------------------------------------------显示函数-------------------------------------------------------- *

    // * -----------------------加载玩家图片---------------------------------- *
void VersusModeScene::displayPlayer()
{
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

    // * -----------------------加载英雄图片---------------------------------- *
void VersusModeScene::displayGate()
{
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

    // * -----------------------加载道具图片---------------------------------- *
void VersusModeScene::displayPropGate()
{
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

    // * -----------------------加载地图图片---------------------------------- *
void VersusModeScene::displayMapGate()
{
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

    // * -----------------------加载确认按钮---------------------------------- *
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
	SimpleAudioEngine::getInstance()->playEffect("music/button.mp3", false, 1.0f, 1.0f, 1.0f);
	if (flag != 0) return;  // 如果当前正在选人，就不能再点击玩家了
	flag = 1;
	player1MenuItem->setScale(1.5f);
	displayGate();
}

void VersusModeScene::player2Callback(Ref * pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("music/button.mp3", false, 1.0f, 1.0f, 1.0f);
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
		prop1 = 1;
		player1MenuItem->setScale(1.0f);
	}
	else if (flag == 2)
	{
		if (prop2 != NULL) pr2->removeFromParent();
		pr2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop_1.png"));
		pr2->setPosition(Vec2(visibleSize.width - pr2->getContentSize().width + origin.x, pr2->getContentSize().height / 2 + origin.y + 50));
		addChild(pr2, 1);
		prop2 = 1;
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
		prop1 = 2;
		player1MenuItem->setScale(1.0f);
	}
	else if (flag == 2)
	{
		if (prop2 != NULL) pr2->removeFromParent();
		pr2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop_2.png"));
		pr2->setPosition(Vec2(visibleSize.width - pr2->getContentSize().width + origin.x, pr2->getContentSize().height / 2 + origin.y + 50));
		addChild(pr2, 1);
		prop2 = 2;
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
		prop1 = 3;
		player1MenuItem->setScale(1.0f);
	}
	else if (flag == 2)
	{
		if (prop2 != NULL) pr2->removeFromParent();
		pr2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop_3.png"));
		pr2->setPosition(Vec2(visibleSize.width - pr2->getContentSize().width + origin.x, pr2->getContentSize().height / 2 + origin.y + 50));
		addChild(pr2, 1);
		prop2 = 3;
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
	// 播放点击音效
	SimpleAudioEngine::getInstance()->setEffectsVolume(effectVolume);
	SimpleAudioEngine::getInstance()->playEffect("music/button.mp3", false, 1.0f, 1.0f, 1.0f);
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	auto gameScene = GameScene::createScene(player1, prop1, player2, prop2, background, backgroundVolume, effectVolume, curBgm);
	Director::getInstance()->replaceScene(gameScene);
}

void VersusModeScene::restartCallback(Ref * pSender)
{
	flag = 0;
	player1 = 0;
	player2 = 0;
	prop1 = 0;
	prop2 =0 ;
	background = 0;
	pl1->removeFromParent();
	pl2->removeFromParent();
	pr1->removeFromParent();
	pr2->removeFromParent();
	bg->removeFromParent();
	start->removeFromParent();
	restart->removeFromParent();
}

void VersusModeScene::configMenuCallback(cocos2d::Ref * pSender)
{
	// 播放点击音效
	SimpleAudioEngine::getInstance()->setEffectsVolume(effectVolume);
	SimpleAudioEngine::getInstance()->playEffect("music/button.mp3", false, 1.0f, 1.0f, 1.0f);

	/*auto renderTexture = RenderTexture::create(origin.x + visibleSize.width, origin.y + visibleSize.height);
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();*/
	auto renderTexture = RenderTexture::create(origin.x + visibleSize.width, origin.y + visibleSize.height);
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();
	auto configScene = ConfigScene::createScene(renderTexture);
	// 将当前界面的音量传入设置界面
	auto curLayer = (ConfigScene*)configScene->getChildren().at(2);
	curLayer->backgroundVolume = backgroundVolume;
	curLayer->effectVolume = effectVolume;
	curLayer->curBgm = curBgm;

	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	Director::getInstance()->pushScene(configScene);
}

void VersusModeScene::soundCallback(cocos2d::Ref * pSender)
{
	// 播放点击音效
	SimpleAudioEngine::getInstance()->setEffectsVolume(effectVolume);
	SimpleAudioEngine::getInstance()->playEffect("music/button.mp3", false, 1.0f, 1.0f, 1.0f);
	if (backgroundVolume > 0 || effectVolume > 0) {
		backgroundVolume = effectVolume = 0;
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(backgroundVolume);
		SimpleAudioEngine::getInstance()->setEffectsVolume(effectVolume);
		}
	else if (backgroundVolume == 0 && effectVolume == 0) {
		backgroundVolume = effectVolume = 0.5f;
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(backgroundVolume);
		SimpleAudioEngine::getInstance()->setEffectsVolume(effectVolume);
	}
}
