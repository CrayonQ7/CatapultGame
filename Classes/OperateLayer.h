#ifndef __OPERATE_LAYER_H__
#define __OPERATE_LAYER_H__

#include "cocos2d.h"
#include "Hero.h"
#include "AMHero.h"

class OperateLayer : public cocos2d::Layer
{
public:
	OperateLayer();
	~OperateLayer();
	static OperateLayer* create(int bgm, int mode);
	virtual bool init(int bgm, int mode);
	CC_SYNTHESIZE(Hero*, hero1, Hero1);
	CC_SYNTHESIZE(Hero*, hero2, Hero2);
	CC_SYNTHESIZE(AMHero*, amHero, AMHero);
	//CREATE_FUNC(OperateLayer);
	void updatePercent1(float f);
	void updatePercent2(float f);
	void updateAngle(float f);
	// OperateLayer设置了如何、用什么控制英雄
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event *event);
	//void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event *event);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event * event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event * event);

	void update(float f);

	void popPauseMenu();

	float backgroundVolume, effectVolume;
	static int curBgm;
private:
	cocos2d::Point move1;  // 角色移动距离
	cocos2d::Point move2;  // 角色移动距离
	float angle;
	//存储键盘是否按下状态
	std::map<EventKeyboard::KeyCode, bool> keys;
	int mode;
};

#endif

