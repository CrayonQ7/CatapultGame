#ifndef __SELECTGATE_H__
#define __SELECTGATE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
class SelectGate : public cocos2d::Layer
{
public:
	// ��ʼ��
	virtual bool init();
	// ��Ӳ˵���
	void addMenuItem(cocos2d::MenuItem *item);
	// ����λ��
	void updatePosition();
	// ����λ�ã��ж���
	void updatePositionWithAnimation();
	// λ�ý��� �޸�λ��forwardΪ�ƶ����� ������ 1/3���� 1
	// true Ϊ������ false Ϊ��
	void rectify(bool forward);
	// ���� ��ʾ����������Ϊ0
	void reset();
	// ���ر�ѡ�е� item
	cocos2d::MenuItem* getCurrentItem();

	void clearGate();
	
	CREATE_FUNC(SelectGate);
private:
	// ���õ�ǰ��ʾ����
	void setIndex(int index);
	// ���õ�ǰ��ʾ�˵����������
	float getIndex();
	// ��ѧ����ʽ width*index/(abs(index)+CALC_A),����CALC_AΪ����
	float calFunction(float index, float width);
	float index;  // ��ǰѡ�еĲ˵��������
	float lastIndex; // ��һ��ѡ�еĲ˵��������
	// �˵���ϣ�_children˳���仯���½����鱣��˳��
	cocos2d::Vector<cocos2d::MenuItem*> items;
	// ��������
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	// ���������ú����������Ҫ��ȷ����һ���˵�����ǰ��
	void actionEndCallback(float dx);
	// ��ǰ��ѡ���item
	cocos2d::MenuItem* selectedItem;
};

#endif

