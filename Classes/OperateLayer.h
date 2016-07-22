#ifndef __OPERATE_LAYER_H__
#define __OPERATE_LAYER_H__

#include "cocos2d.h"
#include "Hero.h"

class OperateLayer : public cocos2d::Layer
{
public:
	OperateLayer();
	~OperateLayer();
	CC_SYNTHESIZE(Hero*, hero1, Hero1);
	CC_SYNTHESIZE(Hero*, hero2, Hero2);
	static OperateLayer* create(int bgm);
	virtual bool init(int bgm);
	//CREATE_FUNC(OperateLayer);
	void updatePercent1(float f);
	void updatePercent2(float f);
	void updateAngle(float f);
	// OperateLayer设置了如何、用什么控制英雄
	//void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	//void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event * event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event * event);

	void update(float f);

	void popPauseMenu();

	//背景音乐音量，音效音量
	float backgroundVolume, effectVolume;
	//选定的背景音乐编号索引
	static int curBgm;
private:
	cocos2d::Point move1;  // 角色移动距离
	cocos2d::Point move2;  // 角色移动距离
	float angle;
	//存储键盘是否按下状态
	std::map<EventKeyboard::KeyCode, bool> keys;
};

#endif

