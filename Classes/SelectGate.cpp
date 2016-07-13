#include "SelectGate.h"
#include <math.h>
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace CocosDenshion;
#define PI acos(-1)
//菜单的缩小比例 最小的比例是1-MENU_SCALE
#define MENU_SCALE 0.3
//菜单的倾斜度 
#define MENU_ASLOPE 60.0
//calFunction(x) 为 x/(x+a),其中a为常数
#define CALC_A 1
//动画运行时间
#define ANIMATION_DURATION  0.3f 
//菜单项的大小与屏幕的比例，当然可以通过setContentSize设置
#define CONTENT_SIZE_SCALE (2.0/3)
//菜单项长度与菜单长度的比例 滑动一个菜单项长度，菜单项变化一个
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
	// 如果希望开始没有移动效果，改成updatePosition函数即可
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
	auto menuSize = getContentSize();  // 菜单大小
	for (int i = 0; i < items.size(); i++)
	{
		// 设置位置
		float x = calFunction(i - index, menuSize.width / 2);
		items.at(i)->setPosition(Point(menuSize.width / 2 + x, menuSize.height / 2));
		// 设置zOrder，即绘制顺序
		items.at(i)->setZOrder(-abs((i - index) * 100));
		// 设置伸缩比例
		items.at(i)->setScale(1.0 - abs(calFunction(i - index, MENU_SCALE)));
		//设置倾斜，Node没有setCamera函数，将OrbitCamera的运行时间设为0来达到效果
		// 这个函数创建一个带有动作运行时间、起始半径、半径差、起始z角、旋转z角的差、起始x角、旋转x角的差
	    // OrbitCamera::create(float t, float radius, float deltaRadius, float angleZ, float deltaAngleZ, float angleX, float deltaAngleX);
		// 该动作过程中，会将参数 deltaAngleZ 和 deltaAngleX 的角度变成弧度（比如deltaAngleZ参数为180，那么转换成弧度就是180*π/180=3.14）
		// 起始半径就是卫星和地球的距离，而半径差是卫星和地球距离的变化可正可负
		// 起始Z角及旋转Z角，我们目前可以理解成摄像机沿着球面的的水平方向旋转。
		// 起始X角及旋转X角，可以理解成摄像机沿着球面的的垂直方向旋转。
		auto orbit1 = OrbitCamera::create(0, 1, 0, calFunction(i - lastIndex, MENU_ASLOPE), calFunction(i - lastIndex, MENU_ASLOPE) - calFunction(i - index, MENU_ASLOPE), 0, 0);
		items.at(i)->runAction(orbit1);
	}
	return;
}

void SelectGate::updatePositionWithAnimation() {
	//先停止所有可能存在的动作
	for (int i = 0; i < items.size(); i++)
		items.at(i)->stopAllActions();
	auto menuSize = getContentSize();
	for (int i = 0; i < items.size(); i++) {
		// 设置位置
		float x = calFunction(i - index, menuSize.width / 2);
		auto moveTo = MoveTo::create(ANIMATION_DURATION, Point(menuSize.width / 2 + x, menuSize.height / 2));
		items.at(i)->runAction(moveTo);
		// 设置zOrder，即绘制顺序
		items.at(i)->setZOrder(-abs((i - index) * 100));
		// 设置伸缩比例
		auto scaleTo = ScaleTo::create(ANIMATION_DURATION, (1.0 - abs(calFunction(i - index, MENU_SCALE))));
		items.at(i)->runAction(scaleTo);
		//设置倾斜
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
		selectedItem->selected();  // 该菜单项被选中，类似于鼠标悬停
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



// 使得只有鼠标在菜单范围内移动时，菜单项才会移动
bool SelectGate::onTouchBegan(Touch* touch, Event* event) {
	//先停止所有可能存在的动作
	for (int i = 0; i < items.size(); i++)
		items.at(i)->stopAllActions();
	if (selectedItem)
		selectedItem->unselected();  // 取消选中状态
	// 将触摸点的坐标转换到菜单所在坐标系
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