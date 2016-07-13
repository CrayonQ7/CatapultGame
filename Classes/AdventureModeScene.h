#ifndef _ADVENTURE_MODE_SCENE_H__
#define _ADVENTURE_MODE_SCENE_H__

#include "cocos2d.h"

class AdventureModeScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(AdventureModeScene);
};

#endif