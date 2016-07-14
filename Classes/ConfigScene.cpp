#include "ConfigScene.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;
using namespace CocosDenshion;

USING_NS_CC;

Scene* ConfigScene::createScene() {
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = ConfigScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool ConfigScene::init() {
	if (!Layer::init()) {
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	auto backItem = Button::create("BackNormal.png", "BackSelected.png");

	backItem->setTitleText("Back");
	backItem->setTitleFontSize(30);
	backItem->setTitleFontName("fonts/Marker Felt.ttf");
	backItem->addTouchEventListener(CC_CALLBACK_1(ConfigScene::sceneBackCallback, this));
	backItem->setPosition(Vec2(origin.x + backItem->getContentSize().width / 2 ,
		origin.y + backItem->getContentSize().height / 2));

	this->addChild(backItem, 1);

	auto label = Label::createWithTTF("Config", "fonts/Marker Felt.ttf", 32);
	label->setScale(2);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height * 2));

	this->addChild(label, 1);

	auto musicSelectLabel = Label::createWithTTF("BackgroundMusic:", "fonts/Marker Felt.ttf", 30);
	musicSelectLabel->setScale(2);
	musicSelectLabel->setPosition(Vec2(origin.x + musicSelectLabel->getContentSize().width,
		origin.y + visibleSize.height - musicSelectLabel->getContentSize().height * 5));

	this->addChild(musicSelectLabel, 1);

	auto musicControlLabel = Label::createWithTTF("MusicVolume:", "fonts/Marker Felt.ttf", 30);
	musicControlLabel->setScale(2);
	musicControlLabel->setPosition(Vec2(origin.x + musicControlLabel->getContentSize().width,
		origin.y + visibleSize.height - musicControlLabel->getContentSize().height * 9));

	this->addChild(musicControlLabel, 1);

	auto effectControlLabel = Label::createWithTTF("EffectsVolume:", "fonts/Marker Felt.ttf", 30);
	effectControlLabel->setScale(2);
	effectControlLabel->setPosition(Vec2(origin.x + effectControlLabel->getContentSize().width,
		origin.y + visibleSize.height - effectControlLabel->getContentSize().height * 13));

	this->addChild(effectControlLabel, 1);
	
	auto background = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("background.png"));
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	auto scaleX = background->getTextureRect().getMaxX();
	auto scaleY = background->getTextureRect().getMaxY();
    background->setScaleX(visibleSize.width / scaleX);
	background->setScaleY(visibleSize.height / scaleY);
	
	this->addChild(background, 0);

	return true;
}

void ConfigScene::onEnter() {
	Layer::onEnter();

	bSlider = Slider::create();
	bSlider->loadBarTexture("SliderTrack.png");
	bSlider->loadSlidBallTextures("SliderThumb.png", "SliderThumb.png", "");
	bSlider->loadProgressBarTexture("SliderBar.png");
	bSlider->setScale9Enabled(true);
	bSlider->setCapInsets(Rect(0, 0, 0, 0));
	bSlider->setContentSize(Size(400, 30));
	bSlider->setPosition(Vec2(origin.x + visibleSize.width / 1.8f,
		origin.y + visibleSize.height - bSlider->getContentSize().height * 10));
	bSlider->addEventListener(CC_CALLBACK_2(ConfigScene::backgroundVolumeSliderEvent, this));
	bSlider->setPercent((int)(backgroundVolume * 100));
	this->addChild(bSlider, 1);

	eSlider = Slider::create();
	eSlider->loadBarTexture("SliderTrack.png");
	eSlider->loadSlidBallTextures("SliderThumb.png", "SliderThumb.png", "");
	eSlider->loadProgressBarTexture("SliderBar.png");
	eSlider->setScale9Enabled(true);
	eSlider->setCapInsets(Rect(0, 0, 0, 0));
	eSlider->setContentSize(Size(400, 30));
	eSlider->setPosition(Vec2(origin.x + visibleSize.width / 1.8f,
		origin.y + visibleSize.height - eSlider->getContentSize().height * 14));
	eSlider->addEventListener(CC_CALLBACK_2(ConfigScene::effectVolumeSliderEvent, this));
	eSlider->setPercent((int)(effectVolume * 100));
	this->addChild(eSlider, 1);

	musicLabel = Label::createWithTTF(loadbgm[curBgm], "fonts/Marker Felt.ttf", 30);
	musicLabel->setScale(2);
	musicLabel->setPosition(Vec2(origin.x + visibleSize.width / 2 + musicLabel->getContentSize().width * 2.5f,
		origin.y + visibleSize.height - musicLabel->getContentSize().height * 5.5f));
	this->addChild(musicLabel, 1);

	m_leftSelectItem = Button::create("LeftNormal.png", "LeftSelected.png", "LeftDisabled.png");
	m_leftSelectItem->addClickEventListener(CC_CALLBACK_1(ConfigScene::m_leftSelectCallback, this));
	m_leftSelectItem->setPosition(Vec2(origin.x + visibleSize.width / 2 + m_leftSelectItem->getContentSize().width / 2,
		origin.y + visibleSize.height - m_leftSelectItem->getContentSize().height * 1.75f));
	if (curBgm == 0) m_leftSelectItem->setEnabled(false);
	this->addChild(m_leftSelectItem, 1);

	m_rightSelectItem = Button::create("RightNormal.png", "RightSelected.png", "RightDisabled.png");
	m_rightSelectItem->addClickEventListener(CC_CALLBACK_1(ConfigScene::m_rightSelectCallback, this));
	m_rightSelectItem->setPosition(Vec2(origin.x + visibleSize.width / 2 + m_rightSelectItem->getContentSize().width * 4,
		origin.y + visibleSize.height - m_rightSelectItem->getContentSize().height * 1.75f));
	if (curBgm == musics - 1) m_rightSelectItem->setEnabled(false);
	this->addChild(m_rightSelectItem, 1);
}

void ConfigScene::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
}

void ConfigScene::m_leftSelectCallback(Ref* pSender) {
	char file[20];
	if (curBgm > 0) {
		sprintf(file, "music/BGM_%d.mp3", --curBgm + 1);
		musicLabel->setString(loadbgm[curBgm]);
		SimpleAudioEngine::getInstance()->playBackgroundMusic(file, true);
		backgroundVolume = 0.5f;
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(backgroundVolume);
		bSlider->setPercent((int)(backgroundVolume * 100));
		m_rightSelectItem->setEnabled(true);
	}
	if (curBgm == 0) m_leftSelectItem->setEnabled(false);
}
void ConfigScene::m_rightSelectCallback(Ref* pSender) {
	char file[20];
	if (curBgm < musics - 1) {
		sprintf(file, "music/BGM_%d.mp3", ++curBgm + 1);
		musicLabel->setString(loadbgm[curBgm]);
		SimpleAudioEngine::getInstance()->playBackgroundMusic(file, true);
		backgroundVolume = 0.5f;
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(backgroundVolume);
		bSlider->setPercent((int)(backgroundVolume * 100));
		m_leftSelectItem->setEnabled(true);
	}
	if (curBgm == musics - 1) m_rightSelectItem->setEnabled(false);
}

void ConfigScene::sceneBackCallback(Ref* pSender) {
	auto menuScene = MenuScene::createScene();
	auto curLayer = (MenuScene*)menuScene->getChildren().at(1);
	curLayer->backgroundVolume = backgroundVolume;
	curLayer->effectVolume = effectVolume;
	curLayer->curBgm = curBgm;
	Director::getInstance()->replaceScene(CCTransitionMoveInL::create(0.5f, menuScene));
}

void ConfigScene::backgroundVolumeSliderEvent(Ref* pSender, Slider::EventType type) {
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
		Slider* slider = dynamic_cast<Slider*>(pSender);
		int percent = slider->getPercent();
		backgroundVolume = (float)percent / 100.0f;
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(backgroundVolume);
	}
}

void ConfigScene::effectVolumeSliderEvent(Ref* pSender, Slider::EventType type) {
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
		Slider* slider = dynamic_cast<Slider*>(pSender);
		int percent = slider->getPercent();
		effectVolume = (float)percent / 100.0f;
		SimpleAudioEngine::getInstance()->setEffectsVolume(effectVolume);
	}
}
