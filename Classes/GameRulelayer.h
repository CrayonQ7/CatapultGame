#ifndef __GAME_RULE_LAYER_H__
#define __GAME_RULE_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;
class GameRuleLayer : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene(RenderTexture* sqr, bool isBegin);
	static GameRuleLayer* create(bool isBegin);
	virtual bool init(bool isBegin);
	void updateOnce(float dt);
	void sceneBackCallback(Ref* pSender);
};

#endif
