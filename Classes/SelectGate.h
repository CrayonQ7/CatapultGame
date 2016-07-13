#ifndef __SELECTGATE_H__
#define __SELECTGATE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
class SelectGate : public cocos2d::Layer
{
public:
	// 初始化
	virtual bool init();
	// 添加菜单项
	void addMenuItem(cocos2d::MenuItem *item);
	// 更新位置
	void updatePosition();
	// 更新位置，有动画
	void updatePositionWithAnimation();
	// 位置矫正 修改位置forward为移动方向 当超过 1/3，进 1
	// true 为正方向 false 为负
	void rectify(bool forward);
	// 重置 显示索引号设置为0
	void reset();
	// 返回被选中的 item
	cocos2d::MenuItem* getCurrentItem();

	void clearGate();
	
	CREATE_FUNC(SelectGate);
private:
	// 设置当前显示索引
	void setIndex(int index);
	// 设置当前显示菜单项的索引号
	float getIndex();
	// 数学计算式 width*index/(abs(index)+CALC_A),其中CALC_A为常数
	float calFunction(float index, float width);
	float index;  // 当前选中的菜单项的索引
	float lastIndex; // 上一次选中的菜单项的索引
	// 菜单项集合，_children顺序会变化，新建数组保存顺序
	cocos2d::Vector<cocos2d::MenuItem*> items;
	// 监听函数
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	// 动画完结调用函数，这个主要是确定哪一个菜单项在前面
	void actionEndCallback(float dx);
	// 当前被选择的item
	cocos2d::MenuItem* selectedItem;
};

#endif

