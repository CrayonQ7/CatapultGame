#include "SelectGate.h"
#include <math.h>
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace CocosDenshion;
#define PI acos(-1)
//�˵�����С���� ��С�ı�����1-MENU_SCALE
#define MENU_SCALE 0.3
//�˵�����б�� 
#define MENU_ASLOPE 60.0
//calFunction(x) Ϊ x/(x+a),����aΪ����
#define CALC_A 1
//��������ʱ��
#define ANIMATION_DURATION  0.3f 
//�˵���Ĵ�С����Ļ�ı�������Ȼ����ͨ��setContentSize����
#define CONTENT_SIZE_SCALE (2.0/3)
//�˵������˵����ȵı��� ����һ���˵���ȣ��˵���仯һ��
#define ITEM_SIZE_SCALE (1.0/4)
USING_NS_CC;

bool SelectGate::init()
{
	if (!Layer::init())
	{
		return false;
	}
	index = 0;
	lastIndex = 0;
	selectedItem = nullptr;
	this->ignoreAnchorPointForPosition(false);
	this->setAnchorPoint(Point(0.5f, 0.5f));
	auto size = Director::getInstance()->getWinSize();
	this->setContentSize(size*CONTENT_SIZE_SCALE);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(SelectGate::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(SelectGate::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(SelectGate::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	return true;
}

void SelectGate::addMenuItem(cocos2d::MenuItem * item)
{
	item->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
	this->addChild(item);
	items.pushBack(item);
	reset();
	// ���ϣ����ʼû���ƶ�Ч�����ĳ�updatePosition��������
	updatePositionWithAnimation();
	return;
}

void SelectGate::clearGate()
{
	if (!items.empty())
	{
		items.clear();
		this->removeAllChildren();
	}
}

void SelectGate::updatePosition()
{
	auto menuSize = getContentSize();  // �˵���С
	for (int i = 0; i < items.size(); i++)
	{
		// ����λ��
		float x = calFunction(i - index, menuSize.width / 2);
		items.at(i)->setPosition(Point(menuSize.width / 2 + x, menuSize.height / 2));
		// ����zOrder��������˳��
		items.at(i)->setZOrder(-abs((i - index) * 100));
		// ������������
		items.at(i)->setScale(1.0 - abs(calFunction(i - index, MENU_SCALE)));
		//������б��Nodeû��setCamera��������OrbitCamera������ʱ����Ϊ0���ﵽЧ��
		// �����������һ�����ж�������ʱ�䡢��ʼ�뾶���뾶���ʼz�ǡ���תz�ǵĲ��ʼx�ǡ���תx�ǵĲ�
	    // OrbitCamera::create(float t, float radius, float deltaRadius, float angleZ, float deltaAngleZ, float angleX, float deltaAngleX);
		// �ö��������У��Ὣ���� deltaAngleZ �� deltaAngleX �ĽǶȱ�ɻ��ȣ�����deltaAngleZ����Ϊ180����ôת���ɻ��Ⱦ���180*��/180=3.14��
		// ��ʼ�뾶�������Ǻ͵���ľ��룬���뾶�������Ǻ͵������ı仯�����ɸ�
		// ��ʼZ�Ǽ���תZ�ǣ�����Ŀǰ���������������������ĵ�ˮƽ������ת��
		// ��ʼX�Ǽ���תX�ǣ����������������������ĵĴ�ֱ������ת��
		auto orbit1 = OrbitCamera::create(0, 1, 0, calFunction(i - lastIndex, MENU_ASLOPE), calFunction(i - lastIndex, MENU_ASLOPE) - calFunction(i - index, MENU_ASLOPE), 0, 0);
		items.at(i)->runAction(orbit1);
	}
	return;
}

void SelectGate::updatePositionWithAnimation() {
	//��ֹͣ���п��ܴ��ڵĶ���
	for (int i = 0; i < items.size(); i++)
		items.at(i)->stopAllActions();
	auto menuSize = getContentSize();
	for (int i = 0; i < items.size(); i++) {
		// ����λ��
		float x = calFunction(i - index, menuSize.width / 2);
		auto moveTo = MoveTo::create(ANIMATION_DURATION, Point(menuSize.width / 2 + x, menuSize.height / 2));
		items.at(i)->runAction(moveTo);
		// ����zOrder��������˳��
		items.at(i)->setZOrder(-abs((i - index) * 100));
		// ������������
		auto scaleTo = ScaleTo::create(ANIMATION_DURATION, (1.0 - abs(calFunction(i - index, MENU_SCALE))));
		items.at(i)->runAction(scaleTo);
		//������б
		auto orbit1 = OrbitCamera::create(ANIMATION_DURATION, 1, 0, calFunction(i - lastIndex, MENU_ASLOPE), calFunction(i - index, MENU_ASLOPE) - calFunction(i - lastIndex, MENU_ASLOPE), 0, 0);
		items.at(i)->runAction(orbit1);
	}
	scheduleOnce(schedule_selector(SelectGate::actionEndCallback), ANIMATION_DURATION);
	return;
}

void SelectGate::actionEndCallback(float dx)
{
	selectedItem = getCurrentItem();
	if (selectedItem)
		selectedItem->selected();  // �ò˵��ѡ�У������������ͣ
}

void SelectGate::reset() {
	if (items.empty())
	{
		lastIndex = 0;
		index = 0;
	}
	else {
		lastIndex = (int)items.size() / 2;
		index = lastIndex;
	}
}

void SelectGate::setIndex(int index) {
	lastIndex = this->index;
	this->index = index;
}
float SelectGate::getIndex() {
	return index;
}

MenuItem * SelectGate::getCurrentItem() {
	if (items.size() == 0)
		return nullptr;
	return items.at(index);
}



// ʹ��ֻ������ڲ˵���Χ���ƶ�ʱ���˵���Ż��ƶ�
bool SelectGate::onTouchBegan(Touch* touch, Event* event) {
	//��ֹͣ���п��ܴ��ڵĶ���
	for (int i = 0; i < items.size(); i++)
		items.at(i)->stopAllActions();
	if (selectedItem)
		selectedItem->unselected();  // ȡ��ѡ��״̬
	// �������������ת�����˵���������ϵ
	auto position = this->convertToNodeSpace(touch->getLocation());
	auto size = this->getContentSize();
	auto rect = Rect(0, 0, size.width, size.height);
	if (rect.containsPoint(position)) {
		return true;
	}
	return false;
}

void SelectGate::onTouchEnded(Touch* touch, Event* event) {
	SimpleAudioEngine::getInstance()->playEffect("music/Page.wav", false, 1.0f, 1.0f, 1.0f);
	auto size = getContentSize();
	auto xDelta = touch->getLocation().x - touch->getStartLocation().x;
	rectify(xDelta>0);
	if (abs(xDelta)<size.width / 24 && selectedItem)
		selectedItem->activate();
	updatePositionWithAnimation();
	return;
}

void SelectGate::rectify(bool forward) {
	auto index = getIndex();
	if (index < 0)
		index = 0;
	if (index>items.size() - 1)
		index = items.size() - 1;
	if (forward) {
		index = (int)(index + 0.4);
	}
	else
		index = (int)(index + 0.6);
	setIndex((int)index);
}

void SelectGate::onTouchMoved(Touch* touch, Event* event) {
	auto xDelta = touch->getDelta().x;
	auto size = getContentSize();
	lastIndex = index;
	index -= xDelta / (size.width *ITEM_SIZE_SCALE);
	updatePosition();
	return;
}
float SelectGate::calFunction(float index, float width) {
	return width*index / (abs(index) + CALC_A);
}