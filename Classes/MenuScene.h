#ifndef __MENUSCENE_H__
#define __MENUSCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class MenuScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCallback(cocos2d::Ref* pSender);
	void versusMenuCallback(cocos2d::Ref* pSender);
	void adventureMenuCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(MenuScene);
private:
	//cocos2d::MenuItemImage*  versusMode;
	//cocos2d::MenuItemImage*  adventureMode;
	cocos2d::MenuItemSprite*  startMenuItem;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
};

#endif
