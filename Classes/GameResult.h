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
	// ���¿�ʼ��Ϸ
	//void menuRestartCallBack(cocos2d::Ref* pSender);
	// �ص����˵�
	void menuBackCallBack(cocos2d::Ref* pSender);
private:
};
#endif