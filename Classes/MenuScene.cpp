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

	// ��ӱ���ͼƬ
	auto background = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("background.png"));
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(background, 0);

	// ��Ӳ˵���ť
	        // �������ʼ��������ģʽѡ��˵���
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

// ��� ����ʼ�����ͻᵯ��ģʽѡ��˵���
void MenuScene::menuCallback(cocos2d::Ref * pSender)
{
	//���ŵ����Ч
	SimpleAudioEngine::getInstance()->playEffect("music/button.wav", false, 1.0f, 1.0f, 1.0f);
	
	startMenuItem->setVisible(false);
	// ������ת�� ����սģʽ���İ�ť
	auto versusMode = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("versusNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("versusSelected.png")),
		CC_CALLBACK_1(MenuScene::versusMenuCallback, this));
	// ������ת�� ��ð��ģʽ���İ�ť
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
	// ���ŵ����Ч
	SimpleAudioEngine::getInstance()->playEffect("music/button.wav", false, 1.0f, 1.0f, 1.0f);
	auto myScene = VersusModeScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, myScene, Color3B(0, 0, 0)));
}

void MenuScene::adventureMenuCallback(cocos2d::Ref * pSender)
{
	// ���ŵ����Ч
	SimpleAudioEngine::getInstance()->playEffect("music/button.wav", false, 1.0f, 1.0f, 1.0f);
	auto myScene = AdventureModeScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, myScene, Color3B(0, 255, 255)));
}
