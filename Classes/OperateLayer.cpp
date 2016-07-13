#include "OperateLayer.h"
USING_NS_CC;

OperateLayer::OperateLayer() :move1(Point(0,0)),move2(Point(0,0)), angle(0)
{
}

OperateLayer::~OperateLayer()
{
}

bool OperateLayer::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF(!Layer::init());
		//auto touchListener = EventListenerTouchAllAtOnce::create();  // ´´½¨¶àµã´¥Ãþ¼àÌýÆ÷
		//touchListener->onTouchesBegan = CC_CALLBACK_2(OperateLayer::onTouchesBegan, this);
		//touchListener->onTouchesMoved = CC_CALLBACK_2(OperateLayer::onTouchesMoved, this);
		//touchListener->onTouchesEnded = CC_CALLBACK_2(OperateLayer::onTouchesEnded, this);
		//_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

		//´´½¨¼üÅÌ¼àÌýÆ÷
		auto keyboardListener = EventListenerKeyboard::create();
		keyboardListener->onKeyPressed = CC_CALLBACK_2(OperateLayer::onKeyPressed, this);
		keyboardListener->onKeyReleased = CC_CALLBACK_2(OperateLayer::onKeyReleased, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

		scheduleUpdate();
		ret = true;
	} while (false);
	return ret;
}

void OperateLayer::updatePercent1(float f)
{   
	auto percent = hero1->playerarrow->getPercentage() + 2;
	hero1->setPower(percent);
}

void OperateLayer::updatePercent2(float f)
{
	auto percent = hero2->playerarrow->getPercentage() + 2;
	hero2->setPower(percent);
}

void OperateLayer::updateAngle(float f)
{
	hero1->rotateArrow(angle);
}

//void OperateLayer::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
//{
//	auto winSize = Director::getInstance()->getWinSize();
//	auto touchIter = touches.begin();
//	while (touchIter != touches.end())
//	{
//		auto touch = (Touch*)(*touchIter);
//		auto p = touch->getLocation();
//		if (p.x <= winSize.width / 2)
//		{
//			this->showJoystick(p);
//		}
//		else
//		{
//			hero->pAttack();
//		}
//		++touchIter;
//	}
//	auto touch = (Touch*)(*touchIter);
//	auto p = touch->getLocation();
//	this->showJoystick(p);
//}
//
//void OperateLayer::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
//{
//	auto winSize = Director::getInstance()->getWinSize();
//	auto touchIter = touches.begin();
//	auto touch = (Touch*)(*touchIter);
//	Point start = touch->getStartLocation();
//	if (start.x > winSize.width / 2)
//	{
//		return;
//	}
//	Point dest = touch->getLocation();
//	float distance = start.getDistance(dest);
//	auto direction = ccpNormalize(dest - start);
//	this->updateJoystick(direction, distance);
//
//	hero->pWalk(direction, distance);
//}
//
//void OperateLayer::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event * unused_event)
//{
//	this->hideJoystick();
//	hero->pStop();
//}

void OperateLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event * event)
{
	switch (code)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		keys[code] = true;
		move1 = Point(-5, 0);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		keys[code] = true;
		move2 = Point(-5, 0);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		keys[code] = true;
		move1 = Point(5, 0);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		keys[code] = true;
		move2 = Point(5, 0);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		keys[code] = true;
		move1 = Point(0, 5);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
		keys[code] = true;
		move2 = Point(0, 5);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		keys[code] = true;
		move1 = Point(0, -5);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		keys[code] = true;
		move2 = Point(0, -5);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_J:
		keys[code] = true;
		angle += 0.2;
		if (angle > M_PI / 2) angle = M_PI / 2;
		hero1->rotateArrow(angle);
		//schedule(schedule_selector(OperateLayer::updateAngle, 0.1f));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_K:
		keys[code] = true;
		angle -= 0.2;
		if (angle < -M_PI / 2) angle = -M_PI / 2;
		hero1->rotateArrow(angle);
		//schedule(schedule_selector(OperateLayer::updateAngle, 0.1f));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_9:
		keys[code] = true;
		angle += 0.2;
		if (angle > M_PI / 2) angle = M_PI / 2;
		hero2->rotateArrow(angle);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_8:
		keys[code] = true;
		angle -= 0.2;
		if (angle < -M_PI / 2) angle = -M_PI / 2;
		hero2->rotateArrow(angle);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
		keys[code] = true;
		schedule(schedule_selector(OperateLayer::updatePercent1, 0.1f));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_0:
		keys[code] = true;
		schedule(schedule_selector(OperateLayer::updatePercent2, 0.1f));
		break;
	default:
		keys[code] = true;
		break;
	}
}

void OperateLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event * event)
{
	switch (code)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		keys[code] = false;
		if (keys[EventKeyboard::KeyCode::KEY_RIGHT_ARROW]) move2 = Point(5, 0);
		else move2 = Point(0, 0);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		keys[code] = false;
		if (keys[EventKeyboard::KeyCode::KEY_D]) move1 = Point(5, 0);
		else move1 = Point(0, 0);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		keys[code] = false;
		if (keys[EventKeyboard::KeyCode::KEY_LEFT_ARROW]) move2 = Point(-5, 0);
		else move2 = Point(0, 0);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		keys[code] = false;
		if (keys[EventKeyboard::KeyCode::KEY_A]) move1 = Point(-5, 0);
		else move1 = Point(0, 0);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
		keys[code] = false;
		if (keys[EventKeyboard::KeyCode::KEY_DOWN_ARROW]) move2 = Point(0, -5);
		else move2 = Point(0, 0);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		keys[code] = false;
		if (keys[EventKeyboard::KeyCode::KEY_S]) move1 = Point(0, -5);
		else move1 = Point(0, 0);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		keys[code] = false;
		if (keys[EventKeyboard::KeyCode::KEY_UP_ARROW]) move2 = Point(0, 5);
		else move2 = Point(0, 0);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		keys[code] = false;
		if (keys[EventKeyboard::KeyCode::KEY_W]) move1 = Point(0, 5);
		else move1 = Point(0, 0);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_J:
		keys[code] = false;
		//angle = 0;
		//unschedule(schedule_selector(OperateLayer::updateAngle, 0.1f));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_K:
		keys[code] = false;
		//angle = 0;
		//unschedule(schedule_selector(OperateLayer::updateAngle, 0.1f));
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_8:
		keys[code] = false;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_9:
		keys[code] = false;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
		keys[code] = false;
		unschedule(schedule_selector(OperateLayer::updatePercent1, 0.1f));
		hero1->pAttack();
		hero1->setPower(0);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_0:
		keys[code] = false;
		unschedule(schedule_selector(OperateLayer::updatePercent2, 0.1f));
		hero2->pAttack();
		hero2->setPower(0);
		break;
	default:
		keys[code] = false;
		break;
	}
}

void OperateLayer::update(float f)
{
	hero1->pWalk(move1);
	hero2->pWalk(move2);
}


