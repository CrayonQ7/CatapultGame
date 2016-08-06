#ifndef _ADVENTURE_MODE_SCENE_H__
#define _ADVENTURE_MODE_SCENE_H__

#include "cocos2d.h"
#include "SelectGate.h"

class AdventureModeScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(AdventureModeScene);
	void selectHero();
	void heroCallBack(cocos2d::Ref* pSender, int heroNumber);
	void gateCallBack(cocos2d::Ref* pSender, int gateNumber);
	void selectGatemap();
	void startGame();
private:
	SelectGate* selectGateMenu;
	cocos2d::Sprite* selectedHero;
	cocos2d::Sprite* selectedGate;
	cocos2d::MenuItemSprite* confirmItem;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	// 传递给下层的参数 
	int heroNum;  // 英雄序号
	int gateNum;  // 关数
};

#endif