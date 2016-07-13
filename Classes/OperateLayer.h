#ifndef __OPERATE_LAYER_H__
#define __OPERATE_LAYER_H__

#include "cocos2d.h"
#include "Hero.h"

class OperateLayer : public cocos2d::Layer
{
public:
	OperateLayer();
	~OperateLayer();
	virtual bool init();
	CC_SYNTHESIZE(Hero*, hero1, Hero1);
	CC_SYNTHESIZE(Hero*, hero2, Hero2);
	CREATE_FUNC(OperateLayer);
	void updatePercent1(float f);
	void updatePercent2(float f);
	void updateAngle(float f);
	// OperateLayer��������Ρ���ʲô����Ӣ��
	//void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event * event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event * event);

	void update(float f);
private:
	cocos2d::Point move1;  // ��ɫ�ƶ�����
	cocos2d::Point move2;  // ��ɫ�ƶ�����
	float angle;
};

#endif

