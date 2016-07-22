#ifndef __VERSUS_MODE_SCENE_H__
#define __VERSUS_MODE_SCENE_H__

#include "cocos2d.h"
#include "SelectGate.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
class VersusModeScene : cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void onEnter();
	CREATE_FUNC(VersusModeScene);
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	int flag;  // �����жϵ�ǰ��ѡplayer1����player2

			   // �����˵�
	SelectGate* selectGateMenu;

	// *-----------------------��Ҫ���´��ݵ�����----------------------------------*

	    //���ڱ����������ݣ���δʹ�ã�
	static float backgroundVolume, effectVolume;  // ����������������Ч����
	static int curBgm;  //��ǰѡ��ı������ֱ������

	cocos2d::MenuItemSprite* configItem;  // ���ý�����밴ť
	cocos2d::Menu* soundState;
	cocos2d::MenuItemToggle* soundStateToggle;
	cocos2d::MenuItemSprite* soundOn;
	cocos2d::MenuItemSprite* soundOff;
	    // ���ѡ���Ӣ�ۡ����ߡ���ͼ���
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
	    // ���ûص�
	void configMenuCallback(cocos2d::Ref* pSender);
	    // �����ص�
	void soundCallback(cocos2d::Ref*pSender);

	// * -----------------------��ʾͼƬ---------------------------------- *
	void displayPlayer();
	void displayGate();
	void displayPropGate();
	void displayMapGate();
	void displayButton();
};
#endif
