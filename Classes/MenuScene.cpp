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

	// ��ӱ���ͼƬ
	auto background = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("background.png"));
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	auto scaleX = background->getTextureRect().getMaxX();
	auto scaleY = background->getTextureRect().getMaxY();
	background->setScaleX(visibleSize.width / scaleX);
	background->setScaleY(visibleSize.height / scaleY);

	this->addChild(background, 0);

	//// ������ת�����ý���İ�ť
	//configItem = Button::create("ConfigItemNormal.png", "ConfigItemSelected.png");
	//configItem->addTouchEventListener(CC_CALLBACK_1(MenuScene::configMenuCallback, this));
	//configItem->setPosition(Vec2(origin.x + visibleSize.width - configItem->getContentSize().width / 2.5f,
	//	origin.y + visibleSize.height - configItem->getContentSize().height / 2));
	//this->addChild(configItem, 1);

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

	auto flower = ParticleSnow::create();
	flower->setTexture(Director::getInstance()->getTextureCache()->addImage("flower.png"));
	flower->setEmitterMode(kCCParticleModeGravity);
	flower->setSpeed(100);
	addChild(flower);

	return true;
}

// ��� ����ʼ�����ͻᵯ��ģʽѡ��˵���
void MenuScene::menuCallback(cocos2d::Ref * pSender)
{
	//���ŵ����Ч
	//SimpleAudioEngine::getInstance()->setEffectsVolume(effectVolume);
	SimpleAudioEngine::getInstance()->playEffect("music/button.mp3", false, 1.0f, 1.0f, 1.0f);
	//CCLOG("E:%f", SimpleAudioEngine::getInstance()->getEffectsVolume());

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
	//SimpleAudioEngine::getInstance()->setEffectsVolume(effectVolume);
	SimpleAudioEngine::getInstance()->playEffect("music/button.mp3", false, 1.0f, 1.0f, 1.0f);
	auto myScene = VersusModeScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, myScene, Color3B(0, 0, 0)));
}

void MenuScene::adventureMenuCallback(cocos2d::Ref * pSender)
{
	// ���ŵ����Ч
	//SimpleAudioEngine::getInstance()->setEffectsVolume(effectVolume);
	SimpleAudioEngine::getInstance()->playEffect("music/button.mp3", false, 1.0f, 1.0f, 1.0f);
	auto myScene = AdventureModeScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, myScene, Color3B(0, 255, 255)));
}
