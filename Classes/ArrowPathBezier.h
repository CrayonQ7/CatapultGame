#ifndef __ArrowPathBezier_H__
#define __ArrowPathBezier_H__

#include <iostream>

#include "cocos2d.h"
USING_NS_CC;


typedef struct _ccQuadBezierConfig {
	Point endPosition;
	Point controlPoint;
} ccQuadBezierConfig;

class ArrowPathBezier : public BezierBy
{
public:
	ArrowPathBezier();
	static ArrowPathBezier* create(float t, const ccQuadBezierConfig& c);
	bool initWithDuration(float t, const ccQuadBezierConfig& c);
	virtual void update(float time);

private:
	ccQuadBezierConfig _config;
};
#endif /* defined(__ArrowPathBezier_H__) */

