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
	// �ȼ��ָ�� p �Ƿ�Ϊ NULL����Ϊ NULL����ִ�� p->release�����ҽ� p ��ֵΪ NULL
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

void BaseSprite::setPosition(const cocos2d::Point & position)
{
	Sprite::setPosition(position);
	this->updateBoxes();
}

BoundingBox BaseSprite::createBoundingBox(cocos2d::Point origin, cocos2d::Size size)
{
	BoundingBox boundingBox;
	boundingBox.original.origin = origin;
	boundingBox.original.size = size;
	boundingBox.actual.origin = this->getPosition() + boundingBox.original.origin;
	boundingBox.actual.size = size;
	return boundingBox;
}

void BaseSprite::updateBoxes()
{
	bool isFlippedX = this->isFlippedX();
	float x = 0.0f;
	if (isFlippedX) {
		x = this->getPosition().x - m_hitBox.original.origin.x;
	}
	else {
		x = this->getPosition().x + m_hitBox.original.origin.x;
	}
	m_hitBox.actual.origin = Point(x, this->getPosition().y + m_hitBox.original.origin.y);
	m_bodyBox.actual.origin = this->getPosition() + m_bodyBox.original.origin;
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
	// Ӣ��������Ͳ����л�����������״̬�ˣ����Ҳ������Լ��л����Լ�
	if (currActionState == ACTION_STATE_DEAD || currActionState == actionState)
	{
		return false;
	}
	// Ӣ�۴��ڿ���״̬ʱ��ֻ���л������ߡ�����������״̬�����ỹû���˾�������
	// Ӣ�۴�������״̬ʱ��ֻ���л������С�����������״̬�����ỹû���˾�������
	// Ӣ�۴��ڹ���״̬ʱ���������л�������״̬
	// Ӣ�۴�������״̬ʱ���������л�������״̬
	this->stopAllActions();
	this->currActionState = actionState;
	return true;
}
