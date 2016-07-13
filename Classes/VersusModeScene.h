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

	int flag;  // �����жϵ�ǰ��ѡplayer1����player2

			   // �����˵�
	SelectGate* selectGateMenu;

	// *-----------------------��Ҫ���´��ݵ�����----------------------------------*

	    // ���ѡ���Ӣ�ۡ����ߡ���ͼ·��
	int player1;
	cocos2d::Sprite* pl1;
	int player2;
	cocos2d::Sprite* pl2;
	const char* prop1;
	cocos2d::Sprite* pr1;
	const char* prop2;
	cocos2d::Sprite* pr2;
	int background;
	cocos2d::Sprite* bg;


	// *-----------------------�ָ���----------------------------------*
	    // ���ͼƬ
	//cocos2d::MenuItemImage* player1MenuItem;
	//cocos2d::MenuItemImage* player2MenuItem;
	cocos2d::MenuItemSprite* player1MenuItem;
	cocos2d::MenuItemSprite* player2MenuItem;
	cocos2d::MenuItemSprite* start;
	cocos2d::MenuItemSprite* restart;

	// *-----------------------�ص�����----------------------------------*
	    // ��һص�
	void player1Callback(Ref* pSender);
	void player2Callback(Ref* pSender);
	    // Ӣ�ۻص�
	void gateOneCallBack(Ref* pSender);
	void gateTwoCallBack(Ref* pSender);
	void gateThreeCallBack(Ref* pSender);
	    // ���߻ص�
	void propOneCallback(Ref* pSender);
	void propTwoCallback(Ref* pSender);
	void propThreeCallback(Ref* pSender);
	    // ��ͼ�ص�
	void mapOneCallback(Ref* pSender);
	void mapTwoCallback(Ref* pSender);
	void mapThreeCallback(Ref* pSender);
	   // ��ť�ص�
	void startCallback(Ref* pSender);
	void restartCallback(Ref* pSender);

	// * -----------------------��ʾͼƬ---------------------------------- *
	void displayPlayer();
	void displayGate();
	void displayPropGate();
	void displayMapGate();
	void displayButton();
};
#endif
