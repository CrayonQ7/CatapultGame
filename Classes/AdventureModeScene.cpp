#include "AdventureModeScene.h"
#include "AMGameScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

cocos2d::Scene * AdventureModeScene::createScene()
{
	auto scene = Scene::create();
	auto layer = AdventureModeScene::create();
	scene->addChild(layer);
	return scene;
}

bool AdventureModeScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	// * -----------------------初始化---------------------------------- *
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/AdventureModeScene.plist");
	selectGateMenu = NULL;
	selectedHero = NULL;
	selectedGate = NULL;
	confirmItem = NULL;
	heroNum = 0;
	gateNum = 0;
	// * -----------------------背景图片---------------------------------- *
	auto background = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("AMbackground.png"));
	background->setPosition(origin + visibleSize / 2);
	addChild(background, 0);
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("music/heroSelect.mp3", true);
	selectHero();
	return true;
}

void AdventureModeScene::selectHero()
{
	if (selectGateMenu != NULL) selectGateMenu->removeFromParent();
	selectGateMenu = SelectGate::create();
	selectGateMenu->setPosition(10.8*visibleSize.width / 18 + origin.x, visibleSize.height / 2 + origin.y);
	addChild(selectGateMenu, 1);
	auto hero1Item = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero1Normal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero1Selected.png")),
		/*Sprite::create("hero1Normal.png"), Sprite::create("hero1Selected.png"),*/
		CC_CALLBACK_1(AdventureModeScene::heroCallBack, this, 1));

	auto hero2Item = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero2Normal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero2Selected.png")),
		/*Sprite::create("hero2Normal.png"), Sprite::create("hero2Selected.png"),*/
		CC_CALLBACK_1(AdventureModeScene::heroCallBack, this, 2));

	auto hero3Item = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero3Normal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero3Selected.png")),
		/*Sprite::create("hero3Normal.png"), Sprite::create("hero3Selected.png"),*/
		CC_CALLBACK_1(AdventureModeScene::heroCallBack, this, 3));

	selectGateMenu->addMenuItem(hero1Item);
	selectGateMenu->addMenuItem(hero2Item);
	selectGateMenu->addMenuItem(hero3Item);
}

void AdventureModeScene::heroCallBack(cocos2d::Ref * pSender, int heroNumber)
{
	if (selectedHero != NULL) selectedHero->removeFromParent();
	SimpleAudioEngine::getInstance()->playEffect("music/heroConfirm.mp3", false, 1.0f, 1.0f, 1.0f);
	if (heroNumber == 1)
	{
		SimpleAudioEngine::getInstance()->playEffect("music/kongfu.mp3", false, 1.0f, 1.0f, 1.0f);
	}
	else if (heroNumber == 2)
	{
		SimpleAudioEngine::getInstance()->playEffect("music/shana.mp3", false, 1.0f, 1.0f, 1.0f);
	}
	else if (heroNumber == 3)
	{
		SimpleAudioEngine::getInstance()->playEffect("music/bashen.mp3", false, 1.0f, 1.0f, 1.0f);
	}
	this->heroNum = heroNumber;
	char heroName[20];
	sprintf(heroName, "hero%d.png", heroNumber);
	selectedHero = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(heroName));
	selectedHero->setVisible(false);
	selectedHero->setPosition(Vec2(origin.x + visibleSize.width / 7.5, origin.y + visibleSize.height / 2));
	selectedHero->runAction(Sequence::create(FadeOut::create(0.5f), CallFunc::create([&](){selectedHero->setVisible(true);}),
		FadeIn::create(1.0f),
		CallFunc::create([&, heroNumber]()
	{
		if (confirmItem != NULL) confirmItem->removeFromParent();
		confirmItem = MenuItemSprite::create(
			Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("confirmNormal.png")), 
				Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("confirmSelected.png")),
			[&, heroNumber](cocos2d::Ref* pSender)
		{
			SimpleAudioEngine::getInstance()->playEffect("music/button.mp3", false, 1.0f, 1.0f, 1.0f); 
			selectGatemap();
		});
		confirmItem->setPosition(Vec2(selectedHero->getPositionX(), selectedHero->getPositionY() - selectedHero->getContentSize().height / 2 - 30));
		auto menu = Menu::create(confirmItem, NULL);
		menu->setPosition(Vec2::ZERO);
		addChild(menu, 1);
	}), NULL));
	addChild(selectedHero, 1);
}

void AdventureModeScene::selectGatemap()
{
	if (selectGateMenu != NULL) selectGateMenu->removeFromParent();
	if (confirmItem != NULL) confirmItem->removeFromParent();
	selectGateMenu = SelectGate::create();
	selectGateMenu->setPosition(10.8*visibleSize.width / 18 + origin.x, visibleSize.height / 2 + origin.y);
	addChild(selectGateMenu, 1);
	auto gateMap1Item = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("gateMap1Normal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("gateMap1Selected.png")),
		//Sprite::create("gateMap1Normal.png"), Sprite::create("gateMap1Selected.png"),
		CC_CALLBACK_1(AdventureModeScene::gateCallBack, this, 1));

	auto gateMap2Item = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("gateMap2Normal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("gateMap2Selected.png")),
	/*	Sprite::create("gateMap2Normal.png"), Sprite::create("gateMap2Selected.png"),*/
		CC_CALLBACK_1(AdventureModeScene::gateCallBack, this, 2));

	auto gateMap3Item = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("gateMap3Normal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("gateMap3Selected.png")),
		/*Sprite::create("gateMap3Normal.png"), Sprite::create("gateMap3Selected.png"),*/
		CC_CALLBACK_1(AdventureModeScene::gateCallBack, this, 3));

	selectGateMenu->addMenuItem(gateMap1Item);
	selectGateMenu->addMenuItem(gateMap2Item);
	selectGateMenu->addMenuItem(gateMap3Item);

	
}

void AdventureModeScene::gateCallBack(cocos2d::Ref * pSender, int gateNumber)
{
	this->gateNum = gateNumber;
	confirmItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("confirmNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("confirmSelected.png")),
		[&, gateNumber](cocos2d::Ref* pSender)
	{ 
		SimpleAudioEngine::getInstance()->playEffect("music/gateConfirm.mp3", false, 1.0f, 1.0f, 1.0f);
		startGame(); 
	});
	confirmItem->setPosition(Vec2(10.8*visibleSize.width / 18 + origin.x, visibleSize.height / 4 + origin.y));
	auto menu = Menu::create(confirmItem, NULL);
	menu->setPosition(Vec2::ZERO);
	addChild(menu, 1);
}

void AdventureModeScene::startGame()
{
	if (selectGateMenu != NULL) selectGateMenu->removeFromParent();
	if (confirmItem != NULL) confirmItem->removeFromParent();
	char gateName[20];
	sprintf(gateName, "gate%d.png", this->gateNum);
	selectedGate = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(gateName));
	selectedGate->setPosition(10.8*visibleSize.width / 18 + origin.x, visibleSize.height / 2 + origin.y);
	addChild(selectedGate, 1);
	auto startItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("AMstartNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("AMstartSelected.png")),
		[&](cocos2d::Ref* pSender) {
		//切换场景
		SimpleAudioEngine::getInstance()->playEffect("music/selectOver.mp3", false, 1.0f, 1.0f, 1.0f);
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		Director::getInstance()->replaceScene(AMGameScene::createScene(heroNum, gateNum, 1));
	});
	startItem->setPosition(10.8*visibleSize.width / 18 + origin.x-80, visibleSize.height / 4 + origin.y);

	auto cancelItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("cancelNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("cancelSelected.png")),
		[&](cocos2d::Ref* pSender) {
		//重新选
		SimpleAudioEngine::getInstance()->playEffect("music/button.mp3", false, 1.0f, 1.0f, 1.0f);
		this->removeAllChildren();
		auto background = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("AMbackground.png"));
		background->setPosition(origin + visibleSize / 2);
		addChild(background, 0);
		selectHero();
	});
	cancelItem->setPosition(10.8*visibleSize.width / 18 + origin.x + 80, visibleSize.height / 4 + origin.y);

	auto menu = Menu::create(startItem, cancelItem, NULL);
	menu->setPosition(Vec2::ZERO);
	addChild(menu, 1);
}