#include "PauseMenu.h"
#include "MenuScene.h"
#include "GameLayer.h"
#include "GameScene.h"
#include "GameRuleLayer.h"
#include "SimpleAudioEngine.h"
#include "ConfigScene.h"
#include "OperateLayer.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;
using namespace CocosDenshion;

USING_NS_CC;

Scene* PauseMenu::createScene(RenderTexture* sqr)
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	auto spr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	spr->setColor(cocos2d::Color3B::GRAY);  //图片变灰色
    spr->setAnchorPoint(ccp(0, 0));
    spr->setFlippedY(true);
	scene->addChild(spr);

	// 'layer' is an autorelease object
	auto layer = PauseMenu::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool PauseMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	// 添加游戏说明背景小图
	auto background = Sprite::create("plist/GameRuleBG.png");
	background->setPosition(Vec2(origin + visibleSize / 2));
	background->setScale(1.25f);
	this->addChild(background, 1);

	// 暂停界面标题
	auto label = Label::createWithTTF("Config", "fonts/Marker Felt.ttf", 40);
	label->setColor(Color3B::BLACK);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height * 3.75f));
	this->addChild(label, 1);

	// 选择背景音乐
	auto musicSelectLabel = Label::createWithTTF("BackgroundMusic:", "fonts/Marker Felt.ttf", 40);
	musicSelectLabel->setColor(Color3B::BLACK);
	musicSelectLabel->setPosition(Vec2(origin.x + background->getAnchorPoint().x + musicSelectLabel->getContentSize().width / 1.2f,
		origin.y + background->getAnchorPoint().y + musicSelectLabel->getContentSize().height * 12));
	this->addChild(musicSelectLabel, 1);

	// 调节BGM音量
	auto musicControlLabel = Label::createWithTTF("MusicVolume:", "fonts/Marker Felt.ttf", 40);
	musicControlLabel->setColor(Color3B::BLACK);
	musicControlLabel->setPosition(Vec2(origin.x + background->getAnchorPoint().x + musicControlLabel->getContentSize().width,
		origin.y + background->getAnchorPoint().y + musicControlLabel->getContentSize().height * 10));
	this->addChild(musicControlLabel, 1);
	// 

	// 调节音效音量
	auto effectControlLabel = Label::createWithTTF("EffectsVolume:", "fonts/Marker Felt.ttf", 40);
	effectControlLabel->setColor(Color3B::BLACK);
	effectControlLabel->setPosition(Vec2(origin.x + background->getAnchorPoint().x + effectControlLabel->getContentSize().width,
		origin.y + background->getAnchorPoint().y + effectControlLabel->getContentSize().height * 8));
	this->addChild(effectControlLabel, 1);

	testItem = MenuItemImage::create("icons/testNormal.png", "icons/testSelected.png", [&](Ref* pSender)
	{
		// 播放点击音效
		SimpleAudioEngine::getInstance()->setEffectsVolume(effectVolume);
		SimpleAudioEngine::getInstance()->playEffect("music/button.mp3", false, 1.0f, 1.0f, 1.0f);
	});
	testItem->setPosition(Vec2(origin.x + +background->getAnchorPoint().x + background->getContentSize().width -
		testItem->getContentSize().width / 2, effectControlLabel->getPositionY()));

	// 返回游戏按钮
	auto backItem = MenuItemFont::create("Resume", CC_CALLBACK_1(PauseMenu::sceneBackCallback, this));
	backItem->setColor(Color3B::BLACK);
	backItem->setScale(1.5f);
	backItem->setPosition(Vec2(origin.x + background->getAnchorPoint().x + backItem->getContentSize().width * 2,
		origin.y + background->getAnchorPoint().y + backItem->getContentSize().height * 5));

	// 返回主菜单按钮
	auto exitItem = MenuItemFont::create("Back to Menu", CC_CALLBACK_1(PauseMenu::sceneExitCallback, this));
	exitItem->setColor(Color3B::BLACK);
	exitItem->setScale(1.5f);
	exitItem->setPosition(Vec2(origin.x + background->getAnchorPoint().x + background->getContentSize().width +
		exitItem->getContentSize().width / 2.5f, origin.y + background->getAnchorPoint().y + exitItem->getContentSize().height * 5));

	// 打开帮助界面按钮
	auto helpItem = MenuItemFont::create("Help", CC_CALLBACK_1(PauseMenu::sceneHelpCallback, this));
	helpItem->setColor(Color3B::BLACK);
	helpItem->setScale(1.5f);
	helpItem->setPosition(Vec2(origin.x + background->getAnchorPoint().x + helpItem->getContentSize().width * 3,
		origin.y + background->getAnchorPoint().y + helpItem->getContentSize().height * 7));

	auto menu = Menu::create(backItem, exitItem, helpItem, testItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);

	// 显示背景音乐
	musicLabel = Label::createWithTTF(loadbgm[curBgm], "fonts/1.ttf", 32);
	musicLabel->setColor(Color3B::BLACK);
	musicLabel->setPosition(Vec2(origin.x + visibleSize.width / 2 + musicLabel->getContentSize().width / 2,
		origin.y + visibleSize.height / 2 + musicLabel->getContentSize().height * 3.75f));
	this->addChild(musicLabel, 1);

	// 音效音量滑动条
	eSlider = Slider::create();
	eSlider->loadBarTexture("icons/SliderTrack.png");
	eSlider->loadSlidBallTextures("icons/SliderThumb.png", "icons/SliderThumb.png", "");
	eSlider->loadProgressBarTexture("icons/SliderBar.png");
	eSlider->setScale9Enabled(true);
	eSlider->setCapInsets(Rect(0, 0, 0, 0));
	eSlider->setContentSize(Size(400, 30));
	eSlider->setPosition(Vec2(origin.x + visibleSize.width / 2,
		testItem->getPositionY()));
	eSlider->addEventListener(CC_CALLBACK_2(PauseMenu::effectVolumeSliderEvent, this));
	eSlider->setScale(0.5);
	this->addChild(eSlider, 1);

	// 背景音乐音量滑动条
	bSlider = Slider::create();
	bSlider->loadBarTexture("icons/SliderTrack.png");
	bSlider->loadSlidBallTextures("icons/SliderThumb.png", "icons/SliderThumb.png", "");
	bSlider->loadProgressBarTexture("icons/SliderBar.png");
	bSlider->setScale9Enabled(true);
	bSlider->setCapInsets(Rect(0, 0, 0, 0));
	bSlider->setContentSize(Size(400, 30));
	bSlider->setPosition(Vec2(origin.x + visibleSize.width / 2,
		eSlider->getPositionY() + 3 * bSlider->getContentSize().height));
	bSlider->addEventListener(CC_CALLBACK_2(PauseMenu::backgroundVolumeSliderEvent, this));
	bSlider->setScale(0.5);
	this->addChild(bSlider, 1);

	// 左选按钮
	m_leftSelectItem = MenuItemImage::create("icons/LeftNormal.png", "icons/LeftSelected.png", "icons/LeftDisabled.png",
		CC_CALLBACK_1(PauseMenu::m_leftSelectCallback, this));
	m_leftSelectItem->setPosition(Vec2(musicLabel->getPositionX() - musicLabel->getContentSize().width / 2 - 30, musicLabel->getPositionY()));
	m_leftSelectItem->setScale(0.6f);

	// 右选按钮
	m_rightSelectItem = MenuItemImage::create("icons/RightNormal.png", "icons/RightSelected.png", "icons/RightDisabled.png",
		CC_CALLBACK_1(PauseMenu::m_rightSelectCallback, this));
	m_rightSelectItem->setPosition(Vec2(musicLabel->getPositionX() + musicLabel->getContentSize().width / 2 + 30, musicLabel->getPositionY()));
	m_rightSelectItem->setScale(0.6f);
	auto menuItem = Menu::create(m_leftSelectItem, m_rightSelectItem, NULL);
	menuItem->setPosition(Vec2::ZERO);
	this->addChild(menuItem, 1);
	return true;
}

void PauseMenu::onEnter() 
{
	Layer::onEnter();
	musicLabel->setString(loadbgm[curBgm]);
	eSlider->setPercent((int)(effectVolume * 100));
	bSlider->setPercent((int)(backgroundVolume * 100));
}

void PauseMenu::sceneBackCallback(Ref* pSender) {
	Director::getInstance()->popScene();
	OperateLayer::curBgm = curBgm;
}

void PauseMenu::sceneExitCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->stopAllEffects();
	auto mainMenu = MenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, mainMenu, Color3B(0, 0, 0)));
}

void PauseMenu::sceneHelpCallback(Ref* pSender)
{
	auto renderTexture = RenderTexture::create(origin.x + visibleSize.width, origin.y + visibleSize.height);
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();

	auto helpInfo = GameRuleLayer::createScene(renderTexture, false);
	Director::getInstance()->pushScene(helpInfo);
}

void PauseMenu::m_leftSelectCallback(Ref* pSender)
{
	char file[20];
	if (curBgm > 0)
	{
		sprintf(file, "music/BGM_%d.mp3", --curBgm + 1);
		//m_rightSelectItem->setEnabled(true);
	}
	else if (curBgm == 0)
	{
		curBgm = musics - 1;
		sprintf(file, "music/BGM_%d.mp3", curBgm + 1);
	}
	musicLabel->setString(loadbgm[curBgm]);
	SimpleAudioEngine::getInstance()->playBackgroundMusic(file, true);
	backgroundVolume = 0.5f;
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(backgroundVolume);
	bSlider->setPercent((int)(backgroundVolume * 100));
	//m_leftSelectItem->setEnabled(false);
}
void PauseMenu::m_rightSelectCallback(Ref* pSender)
{
	char file[20];
	if (curBgm < musics - 1)
	{
		sprintf(file, "music/BGM_%d.mp3", ++curBgm + 1);
		//m_leftSelectItem->setEnabled(true);
	}
	else if (curBgm == musics - 1)
	{
		curBgm = 0;
		sprintf(file, "music/BGM_%d.mp3", curBgm + 1);
	}
	musicLabel->setString(loadbgm[curBgm]);
	SimpleAudioEngine::getInstance()->playBackgroundMusic(file, true);
	backgroundVolume = 0.5f;
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(backgroundVolume);
	bSlider->setPercent((int)(backgroundVolume * 100));
	//m_rightSelectItem->setEnabled(false);
}

void PauseMenu::backgroundVolumeSliderEvent(Ref* pSender, Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(pSender);
		int percent = slider->getPercent();
		backgroundVolume = (float)percent / 100.0f;
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(backgroundVolume);
	}
}

void PauseMenu::effectVolumeSliderEvent(Ref* pSender, Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(pSender);
		int percent = slider->getPercent();
		effectVolume = (float)percent / 100.0f;
		SimpleAudioEngine::getInstance()->setEffectsVolume(effectVolume);
	}
}