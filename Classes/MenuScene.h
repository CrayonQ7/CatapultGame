#ifndef __MENUSCENE_H__
#define __MENUSCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;

class MenuScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	//virtual void onEnter();
	//virtual void onEnterTransitionDidFinish();
	//
 //   float backgroundVolume, effectVolume;  // 교쒼稜있稜좆，稜槻稜좆
	//int curBgm;  //뎠품朞嶝돨교쒼稜있긍뵀乞多
	//
	//		//零객큐
	////Button* configItem;
	//	//역폘稜/쓰稜객큐꽉데섟꽉데淃
	//Menu* soundState;
	//MenuItemToggle* soundStateToggle;
	//MenuItemImage* soundOn;
	//MenuItemImage* soundOff;

	void menuCallback(cocos2d::Ref* pSender);
	void versusMenuCallback(cocos2d::Ref* pSender);
	void adventureMenuCallback(cocos2d::Ref* pSender);

	//void configMenuCallback(cocos2d::Ref* pSender);
	//void soundCallback(cocos2d::Ref*pSender);

	CREATE_FUNC(MenuScene);
private:
	//cocos2d::MenuItemImage*  versusMode;
	//cocos2d::MenuItemImage*  adventureMode;
	cocos2d::MenuItemSprite*  startMenuItem;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
};

#endif
