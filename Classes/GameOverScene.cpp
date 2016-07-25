#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include "MenuScene.h"
#include "VersusModeScene.h"
USING_NS_CC;
using namespace CocosDenshion;
// ����һ��RenderTexture
// �൱��һ���������е���Ϸ�Ľ�ͼ��Ϊ�����ͣ�Ի���ı���
Scene* GameOverScene::scene(RenderTexture* sqr, int p, int d) {
	auto scene = Scene::create();
	auto layer = GameOverScene::create();
	scene->addChild(layer, 1);

	// ʹ����Ϸ�����н�ͼ��sqr����ͼƬ����sprite
	// ����Sprite��ӵ�GamePauseScene������
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto back_sqr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	back_sqr->setPosition((origin + visibleSize) / 2);
	back_sqr->setFlipY(true);  // ��ת����ΪUI�����OpenGL���겻ͬ
							   //back_sqr->setColor(cocos2d::Color3B(200, 190, 180));  //ͼƬ���ɫ
	back_sqr->setColor(cocos2d::Color3B(96, 96, 96));  //ͼƬ���ɫ
	scene->addChild(back_sqr);

	// �����Ϸ��ͣ����Сͼ�������Ű�ť
	
	auto back_samll_sqr = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("win.png"));
	back_samll_sqr->setPosition((origin + visibleSize) / 2);
	back_samll_sqr->setScale(1.5);
	scene->addChild(back_samll_sqr);

	auto audio = SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("music/WinMusic.mp3");
	audio->preloadEffect("music/Gate_2_Win.mp3");
	Sprite* sp;
	char str[20];
	sprintf(str, "Gate_%d.png", p);
	sp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(str));
	sp->setScale(2);
	scene->addChild(sp, 2);
	//if (p == 1) {
	//	//auto sp = Sprite::create("Gate_1_Idle_0.png");
	//	sp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_1.png"));
	//	sp->setScale(2);
	//	scene->addChild(sp, 2);
	//}
	//else if (p == 2) {
	//	//auto sp = Sprite::create("Gate_2_Idle_0.png");
	//	sp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_2.png"));
	//	sp->setScale(2);
	//	scene->addChild(sp, 2);
	//}
	//else if (p == 3) {
	//	//auto sp = Sprite::create("Gate_3_Idle_0.png");
	//	sp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_3.png"));
	//	sp->setScale(2);
	//	scene->addChild(sp, 2);
	//}
	if (d == 1)
	{
		sp->setPosition(origin.x + visibleSize.width / 4, origin.y + visibleSize.height / 2);
	}
	else if (d == 2)
	{
		sp->setPosition(origin.x + 3*visibleSize.width / 4, origin.y + visibleSize.height / 2);
	}
	return scene;
}

bool GameOverScene::init() {
	if (!Layer::init()) {
		return false;
	}
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("music/WinMusic.mp3", false);
	audio->playEffect("music/Gate_2_Win.mp3", false, 1.0f, 1.0f, 1.0f);
	//auto visibleSize = Director::getInstance()->getVisibleSize();
	//auto origin = Director::getInstance()->getVisibleOrigin();

	//auto restartItem = MenuItemImage::create("pause_restart.png", "pause_restart.png", this, menu_selector(GamePauseScene::menuRestart));
	//restartItem->setPosition((origin.x + visibleSize.width) / 2, (origin.y + visibleSize.height) / 2 - 30);

	//auto menu = Menu::create(restartItem, NULL);
	//menu->setPosition(Vec2::ZERO);
	//this->addChild(menu, 2);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	
	auto backItem = MenuItemFont::create("Back To Menu", CC_CALLBACK_1(GameOverScene::menuBackCallBack, this));
	backItem->setScale(1.5f);
	backItem->setPosition(Vec2(origin.x + backItem->getContentSize().width / 1.25f,
		origin.y + backItem->getContentSize().height / 2));
	
	auto restartItem = MenuItemFont::create("Restart", CC_CALLBACK_1(GameOverScene::menuRestartCallBack, this));
	restartItem->setScale(1.5f);
	restartItem->setPosition(Vec2(origin.x + visibleSize.width - backItem->getContentSize().width / 2,
		origin.y + backItem->getContentSize().height / 2));
	
	auto menu = Menu::create(backItem, restartItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);
	return true;
}

void GameOverScene::menuRestartCallBack(cocos2d::Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("music/button.mp3", false, 1.0f, 1.0f, 1.0f);
	auto mainScene = VersusModeScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, mainScene, Color3B(0, 0, 0)));
	}

void GameOverScene::menuBackCallBack(cocos2d::Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("music/button.mp3", false, 1.0f, 1.0f, 1.0f);
	auto mainScene = MenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, mainScene, Color3B(0, 0, 0)));
}
