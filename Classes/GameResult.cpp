#include "GameResult.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

cocos2d::Scene * GameResult::scene(RenderTexture * sqr, int r)
{
	auto scene = Scene::create();
	auto layer = GameResult::create();
	scene->addChild(layer, 1);

	// 使用游戏界面中截图的sqr纹理图片创建sprite
	// 并将Sprite添加到GamePauseScene场景中
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto back_sqr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	back_sqr->setPosition((origin + visibleSize) / 2);
	back_sqr->setFlipY(true);  // 翻转，因为UI坐标和OpenGL坐标不同
							   //back_sqr->setColor(cocos2d::Color3B(200, 190, 180));  //图片变灰色
	back_sqr->setColor(cocos2d::Color3B::GRAY);  //图片变灰色
	scene->addChild(back_sqr);
	Sprite* back_samll_sqr;
	if (r == 1)
	{
		back_samll_sqr = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("victory.png"));
		SimpleAudioEngine::getInstance()->playBackgroundMusic("music/WinMusic.mp3", false);
	}
	else if (r == 2) 
	{
		back_samll_sqr = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("faliure.png"));
		SimpleAudioEngine::getInstance()->playBackgroundMusic("music/failure.mp3", false);
	}
	back_samll_sqr->setPosition((origin + visibleSize) / 2);
	//back_samll_sqr->setScale(1.5);
	scene->addChild(back_samll_sqr);
	return scene;
}

bool GameResult::init()
{
	if (!Layer::init()) {
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto backItem = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tipsNext.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tipsNext.png")),
		CC_CALLBACK_1(GameResult::menuBackCallBack, this));
	backItem->setScale(1.5f);
	backItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + backItem->getContentSize().height / 2));
	auto menu = Menu::create(backItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);
	return true;
}

void GameResult::menuBackCallBack(cocos2d::Ref * pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("music/button.mp3", false, 1.0f, 1.0f, 1.0f);
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	auto mainScene = MenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, mainScene, Color3B(0, 0, 0)));
}
