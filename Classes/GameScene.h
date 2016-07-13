#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
class GameScene
{
public:
	static cocos2d::Scene* createScene(int pl1, const char* pr1, int pl2, const char* pr2, int bg);  // 对战模式
	static cocos2d::Scene* createScene(const char* pl, const char* pr, const char* bg);  // 冒险模式
};

#endif
