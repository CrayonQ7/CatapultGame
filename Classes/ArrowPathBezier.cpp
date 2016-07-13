#include "ArrowPathBezier.h"

// 原来贝赛尔曲线的计算公式
// Bezier cubic formula:
//    ((1 - t) + t)3 = 1
// Expands to
//   (1 - t)3 + 3t(1-t)2 + 3t2(1 - t) + t3 = 1
static inline float bezierat(float a, float b, float c, float d, float t)
{
	return (powf(1 - t, 3) * a +
		3.0f*t*(powf(1 - t, 2))*b +
		3.0f*powf(t, 2)*(1 - t)*c +
		powf(t, 3)*d);
}

// 二次贝赛尔计算公式
static inline float bezierat1(float a, float b, float d, float t)
{
	return (powf(1 - t, 2) * a +
		2.0f*t*(1 - t)*b +
		powf(t, 2)*d);
}

ArrowPathBezier::ArrowPathBezier()
{
}

// 参数是持续时间跟配置信息
ArrowPathBezier* ArrowPathBezier::create(float t, const ccQuadBezierConfig& c)
{
	ArrowPathBezier *pBezierBy = new(std::nothrow) ArrowPathBezier();
	pBezierBy->initWithDuration(t, c);
	pBezierBy->autorelease();

	return pBezierBy;
}

bool ArrowPathBezier::initWithDuration(float t, const ccQuadBezierConfig& c)
{
	bool bRet = false;
	// BezierBy继承自ActionInterval
	if (CCActionInterval::initWithDuration(t))
	{
		// BezierBy的protected属性，ccBezierConfig _config，保存贝塞尔曲线的配置信息
		_config = c;
		return true;
	}

	return bRet;
}

void ArrowPathBezier::update(float time)
{
	// 继承自 Action 的 protected 属性  _target，action动作的执行目标
	if (_target) {
		float xa = 0;
		float xb = _config.controlPoint.x;  // 控制点横坐标
		float xd = _config.endPosition.x;  // 运动终点横坐标

		float ya = 0;
		float yb = _config.controlPoint.y;
		float yd = _config.endPosition.y;

		float x = bezierat1(xa, xb, xd, time);
		float y = bezierat1(ya, yb, yd, time);

		/* 开启这个宏的效果在于，当多个动作作用于一个精灵的时候，

		* 这个精灵的运动方式为多个动作的组合效果。

		* 举个例子，MoveBy::create(1, Vec2(100, 0))和MoveBy::create(1, Vec2(-90, 0))

		* 同时作用于一个精灵，那么效果是该精灵只会在1s内向右移动10个像素。

		* 不开启此宏，还是上面的例子，那么这个精灵只会执行最后配置的MoveBy的动作。

		* 这个宏在2.0之后的版本都是默认开启的，为了兼容之前的版本需要关闭该宏。

		*/

#if CC_ENABLE_STACKABLE_ACTIONS
		Vec2 currentPos = _target->getPosition();
		Vec2 diff = currentPos - _previousPosition;
		_startPosition = _startPosition + diff;

		Vec2 newPos = _startPosition + Vec2(x, y);
		_target->setPosition(newPos);

		_previousPosition = newPos;

		if (0 != time) {
			Vec2 vector = currentPos - newPos;
			float radians = vector.getAngle();
			float degrees = CC_RADIANS_TO_DEGREES(-1 * radians);
			_target->setRotation(degrees - 180);
		}

#else
		_target->setPosition(_startPosition + Vec2(x, y));
#endif // !CC_ENABLE_STACKABLE_ACTIONS

	}
}