#include "ArrowPathBezier.h"

// ԭ�����������ߵļ��㹫ʽ
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

// ���α��������㹫ʽ
static inline float bezierat1(float a, float b, float d, float t)
{
	return (powf(1 - t, 2) * a +
		2.0f*t*(1 - t)*b +
		powf(t, 2)*d);
}

ArrowPathBezier::ArrowPathBezier()
{
}

// �����ǳ���ʱ���������Ϣ
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
	// BezierBy�̳���ActionInterval
	if (CCActionInterval::initWithDuration(t))
	{
		// BezierBy��protected���ԣ�ccBezierConfig _config�����汴�������ߵ�������Ϣ
		_config = c;
		return true;
	}

	return bRet;
}

void ArrowPathBezier::update(float time)
{
	// �̳��� Action �� protected ����  _target��action������ִ��Ŀ��
	if (_target) {
		float xa = 0;
		float xb = _config.controlPoint.x;  // ���Ƶ������
		float xd = _config.endPosition.x;  // �˶��յ������

		float ya = 0;
		float yb = _config.controlPoint.y;
		float yd = _config.endPosition.y;

		float x = bezierat1(xa, xb, xd, time);
		float y = bezierat1(ya, yb, yd, time);

		/* ����������Ч�����ڣ����������������һ�������ʱ��

		* ���������˶���ʽΪ������������Ч����

		* �ٸ����ӣ�MoveBy::create(1, Vec2(100, 0))��MoveBy::create(1, Vec2(-90, 0))

		* ͬʱ������һ�����飬��ôЧ���Ǹþ���ֻ����1s�������ƶ�10�����ء�

		* �������˺꣬������������ӣ���ô�������ֻ��ִ��������õ�MoveBy�Ķ�����

		* �������2.0֮��İ汾����Ĭ�Ͽ����ģ�Ϊ�˼���֮ǰ�İ汾��Ҫ�رոúꡣ

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