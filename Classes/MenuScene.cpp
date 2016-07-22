#include "MenuScene.h"
#include "ConfigScene.h"
#include "VersusModeScene.h"
#include "AdventureModeScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace CocosDenshion;
cocos2d::Scene * MenuScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MenuScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool MenuScene::init()
{
	//////////////////////////////
	// super init first
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	//backgroundVolume = effectVolume = 0.5f;
	//curBgm = 0;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/MenuScene.plist");

	// 添加背景图片
	auto background = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("background.png"));
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	auto scaleX = background->getTextureRect().getMaxX();
	auto scaleY = background->getTextureRect().getMaxY();
	background->setScaleX(visibleSize.width / scaleX);
	background->setScaleY(visibleSize.height / scaleY);

	this->addChild(background, 0);

	//// 可以跳转到设置界面的按钮
	//configItem = Button::create("ConfigItemNormal.png", "ConfigItemSelected.png");
	//configItem->addTouchEventListener(CC_CALLBACK_1(MenuScene::configMenuCallback, this));
	//configItem->setPosition(Vec2(origin.x + visibleSize.width - configItem->getContentSize().width / 2.5f,
	//	origin.y + visibleSize.height - configItem->getContentSize().height / 2));
	//this->addChild(configItem, 1);

	// 添加菜单按钮
	        // 点击“开始”，弹出模式选择菜单项
	startMenuItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("startNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("startSelected.png")),
		CC_CALLBACK_1(MenuScene::menuCallback, this));
	startMenuItem->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	        // create menu, it's an autorelease object
	auto menu = Menu::create(startMenuItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

// 点击 “开始”，就会弹出模式选择菜单项
void MenuScene::menuCallback(cocos2d::Ref * pSender)
{
	//播放点击音效
	//SimpleAudioEngine::getInstance()->setEffectsVolume(effectVolume);
	SimpleAudioEngine::getInstance()->playEffect("music/button.mp3", false, 1.0f, 1.0f, 1.0f);
	//CCLOG("E:%f", SimpleAudioEngine::getInstance()->getEffectsVolume());

	startMenuItem->setVisible(false);
	// 可以跳转到 “对战模式”的按钮
	auto versusMode = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("versusNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("versusSelected.png")),
		CC_CALLBACK_1(MenuScene::versusMenuCallback, this));
	// 可以跳转到 “冒险模式”的按钮
	auto adventureMode = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("adventureNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("adventureSelected.png")),
		CC_CALLBACK_1(MenuScene::adventureMenuCallback, this));
	versusMode->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + versusMode->getContentSize().height));
	adventureMode->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - adventureMode->getContentSize().height));
	adventureMode->setEnabled(false);  // ??
	auto menu = Menu::create(versusMode, adventureMode, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}

void MenuScene::versusMenuCallback(cocos2d::Ref * pSender)
{
	// 播放点击音效
	//SimpleAudioEngine::getInstance()->setEffectsVolume(effectVolume);
	SimpleAudioEngine::getInstance()->playEffect("music/button.mp3", false, 1.0f, 1.0f, 1.0f);
	auto myScene = VersusModeScene::createScene();

	//auto curLayer = (VersusModeScene*)myScene->getChildren().at(1);
	//curLayer->backgroundVolume = backgroundVolume;
	//curLayer->effectVolume = effectVolume;
	//curLayer->curBgm = curBgm;

	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, myScene, Color3B(0, 0, 0)));
}

void MenuScene::adventureMenuCallback(cocos2d::Ref * pSender)
{
	// 播放点击音效
	//SimpleAudioEngine::getInstance()->setEffectsVolume(effectVolume);
	SimpleAudioEngine::getInstance()->playEffect("music/button.mp3", false, 1.0f, 1.0f, 1.0f);
	auto myScene = AdventureModeScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, myScene, Color3B(0, 255, 255)));
}

//void MenuScene::onEnter()
//{
//	Layer::onEnter();
//	
//			//添加声音开关按钮
//	soundOn = MenuItemImage::create("SoundOn.png", "SoundOn.png");
//	soundOn->setScale(0.55f);
//	soundOff = MenuItemImage::create("SoundOff.png", "SoundOff.png");
//	soundOff->setScale(0.55f);
//	soundStateToggle = MenuItemToggle::createWithTarget(this, menu_selector(MenuScene::soundCallback), soundOn, soundOff, NULL);
//	//soundStateToggle->setPosition(Vec2(origin.x + soundOn->getContentSize().width / 5,
//	//	origin.y + visibleSize.height / 2 - soundOn->getContentSize().height / 6));
//	soundStateToggle->setPosition(Vec2(origin.x + soundOn->getContentSize().width / 2,
//		origin.y + visibleSize.height/2 - soundOn->getContentSize().height / 2));
//	if (backgroundVolume <= 0.01 && effectVolume <= 0.01) soundStateToggle->setSelectedIndex(1);
//	soundState = Menu::create(soundStateToggle, NULL);
//	soundState->setPosition(Vec2(origin.x + soundOn->getContentSize().width / 2,
//		origin.y + visibleSize.height - soundOn->getContentSize().height / 2));
//	this->addChild(soundState, 1);
//	}
//
//void MenuScene::onEnterTransitionDidFinish()
//{
//	auto audio = SimpleAudioEngine::getInstance();
//	//char file[20];
//	//sprintf(file, "music/BGM_%d.mp3", curBgm + 1);
//	//audio->playBackgroundMusic(file, true);
//	audio->setBackgroundMusicVolume(backgroundVolume);
//	audio->setEffectsVolume(effectVolume);
//	CCLOG("E:%f", audio->getEffectsVolume());
//}
//
//void MenuScene::configMenuCallback(cocos2d::Ref * pSender)
//{
//		// 播放点击音效
//    SimpleAudioEngine::getInstance()->setEffectsVolume(effectVolume);
//	SimpleAudioEngine::getInstance()->playEffect("music/button.mp3", false, 1.0f, 1.0f, 1.0f);
//	auto configScene = ConfigScene::createScene();
//	auto curLayer = (ConfigScene*)configScene->getChildren().at(1);
//	curLayer->backgroundVolume = backgroundVolume;
//	curLayer->effectVolume = effectVolume;
//	curLayer->curBgm = curBgm;
//	Director::getInstance()->replaceScene(CCTransitionMoveInR::create(0.5f, configScene));
//}
//
//void MenuScene::soundCallback(cocos2d::Ref * pSender)
//{
//		// 播放点击音效
//	SimpleAudioEngine::getInstance()->setEffectsVolume(effectVolume);
//	SimpleAudioEngine::getInstance()->playEffect("music/button.mp3", false, 1.0f, 1.0f, 1.0f);
//	if (backgroundVolume > 0 || effectVolume > 0) {
//		backgroundVolume = effectVolume = 0;
//		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(backgroundVolume);
//		SimpleAudioEngine::getInstance()->setEffectsVolume(effectVolume);
//	}
//	else if (backgroundVolume == 0 && effectVolume == 0) {
//		backgroundVolume = effectVolume = 0.5f;
//		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(backgroundVolume);
//		SimpleAudioEngine::getInstance()->setEffectsVolume(effectVolume);
//	}
//}