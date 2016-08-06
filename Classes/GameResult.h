#ifndef __GameResult__H__
#define __GameResult__H__
#include "cocos2d.h"
#include <string>
USING_NS_CC;
class GameResult : public cocos2d::Layer {
public:
	virtual bool init();
	static cocos2d::Scene* scene(RenderTexture* sqr, int r);
	CREATE_FUNC(GameResult);
	// 重新开始游戏
	//void menuRestartCallBack(cocos2d::Ref* pSender);
	// 回到主菜单
	void menuBackCallBack(cocos2d::Ref* pSender);
private:
};
#endif