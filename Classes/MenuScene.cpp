#include "MenuScene.h"
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

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/MenuScene.plist");

	// 添加背景图片
	auto background = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("background.png"));
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(background, 0);

	// 添加菜单按钮
	        // 点击“开始”，跳出模式选择菜单项
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
	SimpleAudioEngine::getInstance()->playEffect("music/button.wav", false, 1.0f, 1.0f, 1.0f);
	
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
	auto menu = Menu::create(versusMode, adventureMode, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}

void MenuScene::versusMenuCallback(cocos2d::Ref * pSender)
{
	// 播放点击音效
	SimpleAudioEngine::getInstance()->playEffect("music/button.wav", false, 1.0f, 1.0f, 1.0f);
	auto myScene = VersusModeScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, myScene, Color3B(0, 0, 0)));
}

void MenuScene::adventureMenuCallback(cocos2d::Ref * pSender)
{
	// 播放点击音效
	SimpleAudioEngine::getInstance()->playEffect("music/button.wav", false, 1.0f, 1.0f, 1.0f);
	auto myScene = AdventureModeScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, myScene, Color3B(0, 255, 255)));
}
