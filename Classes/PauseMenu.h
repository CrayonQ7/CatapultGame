#ifndef __PAUSE_MENU_H__
#define __PAUSE_MENU_H__

#include <vector>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;

class PauseMenu : public Layer {
public:
	static Scene* createScene(RenderTexture* sqr);

	Size visibleSize;
	Vec2 origin;

	//��������ѡ��˫��ť
	cocos2d::MenuItemImage* m_leftSelectItem;
	cocos2d::MenuItemImage* m_rightSelectItem;
	//�����۲���Ч����
	cocos2d::MenuItemImage* testItem;
	//��ǰ������ʾ��
	Label* musicLabel;
	//���������������ڻ�����
	Slider* bSlider;
	//��Ч�������ڻ�����
	Slider* eSlider;

	virtual bool init();
	virtual void onEnter();

	//����������������Ч����
	float backgroundVolume, effectVolume;
	//ѡ���ı������ֱ������
	int curBgm;
	//������������
	static const int musics = 6;
	std::vector<std::string> loadbgm = { "MUSIC1", "MUSIC2", "MUSIC3", "MUSIC4", "MUSIC5", "MUSIC6" };

	//�ص�����
	void sceneBackCallback(Ref* pSender);
	void sceneExitCallback(Ref* pSender);
	void sceneHelpCallback(Ref* pSender);

	void m_leftSelectCallback(Ref* pSender);
	void m_rightSelectCallback(Ref* pSender);
	void backgroundVolumeSliderEvent(Ref* pSender, Slider::EventType type);
	void effectVolumeSliderEvent(Ref* pSender, Slider::EventType type);

	// implement the "static create()" method manually
	CREATE_FUNC(PauseMenu);
};

#endif // __PAUSE_MENU_H__