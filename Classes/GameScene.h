#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
class GameScene
{
public:
	static cocos2d::Scene* createScene(int pl1, int pr1, int pl2, int pr2, int bg, float bv, float ev, int bgm);  // ��սģʽ
	static cocos2d::Scene* createScene(const char* pl, const char* pr, const char* bg);  // ð��ģʽ
};

#endif
