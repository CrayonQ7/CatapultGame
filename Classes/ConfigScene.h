#ifndef __CONFIG_SCENE_H__
#define __CONFIG_SCENE_H__

#include <vector>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;

class ConfigScene : public Layer {
public:
	static Scene* createScene();
	Size visibleSize;
	Vec2 origin;

	//背景音乐选择双向按钮
	cocos2d::MenuItemImage* m_leftSelectItem;
	cocos2d::MenuItemImage* m_rightSelectItem;
	//用来观察音效声音
	cocos2d::MenuItemImage* testItem;
	//当前音乐显示板
	Label* musicLabel;
	//背景音乐音量调节滑动条
	Slider* bSlider;
	//音效音量调节滑动条
	Slider* eSlider;

	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();

	//背景音乐音量，音效音量
	float backgroundVolume, effectVolume;
	//选定的背景音乐编号索引
	int curBgm;
	//背景音乐数量
	static const int musics = 6;
	std::vector<std::string> loadbgm = { "MUSIC1", "MUSIC2", "MUSIC3", "MUSIC4", "MUSIC5", "MUSIC6" };

	//回调函数
	void sceneBackCallback(Ref* pSender);
	void m_leftSelectCallback(Ref* pSender);
	void m_rightSelectCallback(Ref* pSender);
	void backgroundVolumeSliderEvent(Ref* pSender, Slider::EventType type);
	void effectVolumeSliderEvent(Ref* pSender, Slider::EventType type);

	// implement the "static create()" method manually
	CREATE_FUNC(ConfigScene);
};

#endif // __CONFIG_SCENE_H__


