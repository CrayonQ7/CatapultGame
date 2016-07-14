#ifndef __VERSUS_MODE_SCENE_H__
#define __VERSUS_MODE_SCENE_H__

#include "cocos2d.h"
#include "SelectGate.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
class VersusModeScene : cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(VersusModeScene);
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	int flag;  // 用来判断当前是选player1还是player2

			   // 滑动菜单
	SelectGate* selectGateMenu;

	// *-----------------------需要向下传递的数据----------------------------------*

	    // 玩家选择的英雄、道具、地图编号
	int player1;
	int prop1;
	int player2;
	int prop2;
	int background;

	cocos2d::Sprite* pl1;
	cocos2d::Sprite* pr1;
	cocos2d::Sprite* pl2;
	cocos2d::Sprite* pr2;
	cocos2d::Sprite* bg;


	// *-----------------------分割线----------------------------------*
	    // 玩家图片
	//cocos2d::MenuItemImage* player1MenuItem;
	//cocos2d::MenuItemImage* player2MenuItem;
	cocos2d::MenuItemSprite* player1MenuItem;
	cocos2d::MenuItemSprite* player2MenuItem;
	cocos2d::MenuItemSprite* start;
	cocos2d::MenuItemSprite* restart;

	// *-----------------------回调函数----------------------------------*
	    // 玩家回调
	void player1Callback(Ref* pSender);
	void player2Callback(Ref* pSender);
	    // 英雄回调
	void gateOneCallBack(Ref* pSender);
	void gateTwoCallBack(Ref* pSender);
	void gateThreeCallBack(Ref* pSender);
	    // 道具回调
	void propOneCallback(Ref* pSender);
	void propTwoCallback(Ref* pSender);
	void propThreeCallback(Ref* pSender);
	    // 地图回调
	void mapOneCallback(Ref* pSender);
	void mapTwoCallback(Ref* pSender);
	void mapThreeCallback(Ref* pSender);
	   // 按钮回调
	void startCallback(Ref* pSender);
	void restartCallback(Ref* pSender);

	// * -----------------------显示图片---------------------------------- *
	void displayPlayer();
	void displayGate();
	void displayPropGate();
	void displayMapGate();
	void displayButton();
};
#endif
