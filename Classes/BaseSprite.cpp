#include "BaseSprite.h"
USING_NS_CC;

BaseSprite::BaseSprite() :
	idle(NULL),
	walk(NULL),
	attack(NULL),
	hurt(NULL),
	dead(NULL),
	currActionState(ACTION_STATE_NONE)
{
}

BaseSprite::~BaseSprite()
{
	// 先检查指针 p 是否为 NULL，不为 NULL，则执行 p->release，并且将 p 赋值为 NULL
	CC_SAFE_RELEASE_NULL(idle);
	CC_SAFE_RELEASE_NULL(walk);
	CC_SAFE_RELEASE_NULL(attack);
	CC_SAFE_RELEASE_NULL(hurt);
	CC_SAFE_RELEASE_NULL(dead);

}

void BaseSprite::runIdleAction()
{
	if (changeState(ACTION_STATE_IDLE))
	{
		this->runAction(idle);
	}
}

void BaseSprite::runWalkAction()
{
	if (changeState(ACTION_STATE_WALK))
	{
		this->runAction(walk);
	}
}

void BaseSprite::runAttackAction()
{
	if (changeState(ACTION_STATE_ATTACK))
	{
		this->runAction(attack);
	}
}

void BaseSprite::runHurtAction()
{
	if (changeState(ACTION_STATE_HURT))
	{
		this->runAction(hurt);
	}
}

void BaseSprite::runDeadAction()
{
	if (changeState(ACTION_STATE_DEAD))
	{
		this->runAction(dead);
	}
}



cocos2d::CallFunc * BaseSprite::createIdleCallbackFunc()
{
	return CallFunc::create(CC_CALLBACK_0(BaseSprite::runIdleAction, this));
}

cocos2d::Animation * BaseSprite::createAnimation(const char * formatStr, int frameCount, int fps)
{
	cocos2d::Vector<SpriteFrame*>frames;
	frames.reserve(frameCount);
	for (int i = 0; i < frameCount; ++i)
	{
		//const char* imgName = String::createWithFormat(formatStr, i)->getCString();
		char imgName[100] = { 0 };
		sprintf(imgName, formatStr, i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(imgName);
		frames.pushBack(frame);
	}
	return Animation::createWithSpriteFrames(frames, 1.0f/fps);
}

//cocos2d::Animation * BaseSprite::createAnimation(const char* formatStr, float width, float height, int frameCount, float f)
//{
//	cocos2d::Vector<SpriteFrame*> frames;
//	frames.reserve(frameCount);
//	auto texture = Director::getInstance()->getTextureCache()->addImage(formatStr);
//	width = width / frameCount;
//	for (int i = 0; i < frameCount; i++)
//	{
//		auto frame = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(width * i, 0, width, height)));
//		frames.pushBack(frame);
//	}
//	return Animation::createWithSpriteFrames(frames, f);
//}

bool BaseSprite::changeState(ActionState actionState)
{
	// 英雄死亡后就不能切换到其他四种状态了，并且不建议自己切换到自己
	if (currActionState == ACTION_STATE_DEAD || currActionState == actionState)
	{
		return false;
	}
	// 英雄处于空闲状态时，只能切换到行走、攻击、受伤状态，不会还没受伤就死亡了
	// 英雄处于行走状态时，只能切换到空闲、攻击、受伤状态，不会还没受伤就死亡了
	// 英雄处于攻击状态时，会立即切换到空闲状态
	// 英雄处于受伤状态时，会立即切换到空闲状态
	this->stopAllActions();
	this->currActionState = actionState;
	return true;
}
