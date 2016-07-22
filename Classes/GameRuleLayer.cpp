#include "GameRuleLayer.h"
#include "GameLayer.h"
USING_NS_CC;


cocos2d::Scene * GameRuleLayer::createScene(RenderTexture* sqr, bool isBegin)
{
	auto scene = Scene::create();
	auto layer = GameRuleLayer::create(isBegin);
	scene->addChild(layer, 1);

	// 使用游戏界面中截图的sqr纹理图片创建sprite
	// 并将Sprite添加到GamePauseScene场景中
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto back_sqr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	back_sqr->setPosition((origin + visibleSize) / 2);
	back_sqr->setFlippedY(true);  // 翻转，因为UI坐标和OpenGL坐标不同
	back_sqr->setColor(cocos2d::Color3B::GRAY);  //图片变灰色
	scene->addChild(back_sqr);

	// 添加游戏说明背景小图
	auto background = Sprite::create("plist/GameRuleBG.png");
	background->setPosition(Vec2(origin + visibleSize / 2));
	scene->addChild(background);

	return scene;
}

GameRuleLayer * GameRuleLayer::create(bool isBegin)
{
	GameRuleLayer* pRet = new(std::nothrow) GameRuleLayer();
	if (pRet && pRet->init(isBegin))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool GameRuleLayer::init(bool isBegin)
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	if (isBegin)
	{
		this->scheduleOnce(schedule_selector(GameRuleLayer::updateOnce), 3.0f);
	}
	else
	{
		auto backItem = MenuItemImage::create("icons/BackNormal.png", "icons/BackSelected.png", CC_CALLBACK_1(GameRuleLayer::sceneBackCallback, this));
		backItem->setPosition(Vec2(origin.x + visibleSize.width / 4, origin.y + backItem->getContentSize().height * 2.5f));
		auto menu = Menu::create(backItem, NULL);
		menu->setPosition(Vec2::ZERO);
		addChild(menu, 1);
	}
	// 标题
	auto label = Label::createWithTTF("Game Rule", "fonts/Marker Felt.ttf", 40);
	label->setColor(Color3B::BLACK);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height * 5));
	this->addChild(label, 1);

	TTFConfig config("fonts/1.ttf", 32);
	auto strings = FileUtils::getInstance()->getValueMapFromFile("xml/GameRule.xml");

	auto player1 = Label::createWithTTF("player1:", "fonts/Marker Felt.ttf", 40);
	player1->setColor(Color3B::BLACK);
	player1->setPosition(Vec2(origin.x + visibleSize.width / 2 -  player1->getContentSize().width*2,
		origin.y + visibleSize.height / 2 + player1->getContentSize().height * 2));
	this->addChild(player1);
	std::string description1 = strings["description1"].asString();
	auto player1Des = Label::createWithTTF(config, description1, TextHAlignment::LEFT);
	player1Des->setColor(Color3B::BLACK);
	player1Des->setPosition(Vec2(player1->getPositionX() + player1Des->getContentSize().width, player1->getPositionY()));
	this->addChild(player1Des, 1);

	auto player2 = Label::createWithTTF("player2:", "fonts/Marker Felt.ttf", 40);
	//player2->setPosition(Vec2(origin.x + visibleSize.width / 2 - player2->getContentSize().width*2,
	//	origin.y + visibleSize.height / 2 - player2->getContentSize().height * 2));
	player2->setColor(Color3B::BLACK);
	player2->setPosition(Vec2(player1->getPositionX(), origin.y + visibleSize.height / 2 - player2->getContentSize().height * 2));
	this->addChild(player2);
	std::string description2 = strings["description2"].asString();
	auto player2Des = Label::createWithTTF(config, description2, TextHAlignment::LEFT);
	player2Des->setColor(Color3B::BLACK);
	player2Des->setPosition(Vec2(player2->getPositionX() + player2Des->getContentSize().width, player2->getPositionY()));
	this->addChild(player2Des, 1);

	return true;
}

void GameRuleLayer::updateOnce(float dt)
{
	Director::getInstance()->popScene();
}

void GameRuleLayer::sceneBackCallback(Ref * pSender)
{
	Director::getInstance()->popScene();
}
