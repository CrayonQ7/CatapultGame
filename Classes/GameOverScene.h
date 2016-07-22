#ifndef __GameOverScene__H__
#define __GameOverScene__H__
#include "cocos2d.h"
#include <string>
USING_NS_CC;
class GameOverScene : public cocos2d::Layer {
public:
	virtual bool init();
	static cocos2d::Scene* scene(RenderTexture* sqr, int p, int d);
	CREATE_FUNC(GameOverScene);
	// ���¿�ʼ��Ϸ
	void menuRestartCallBack(cocos2d::Ref* pSender);
	// �ص����˵�
	void menuBackCallBack(cocos2d::Ref* pSender);
private:
};



#endif

#pragma once
