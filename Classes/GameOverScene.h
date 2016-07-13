#ifndef __GameOverScene__H__
#define __GameOverScene__H__
#include <string>
USING_NS_CC;
class GameOverScene : public cocos2d::Layer {
public:
	virtual bool init();
	static cocos2d::Scene* scene(RenderTexture* sqr, int p, int d);
	CREATE_FUNC(GameOverScene);
	// 重新开始游戏
	//void menuRestart(Object* pSender);
private:
};



#endif

#pragma once
