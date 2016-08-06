#ifndef __BASESPRITE_H__
#define __BASESPRITE_H__

#include "cocos2d.h"
// 精灵有5个状态，idle空闲，walk行走，attack攻击，hurt受伤，dead死亡
typedef enum
{
	ACTION_STATE_NONE = 0,
	ACTION_STATE_IDLE,
	ACTION_STATE_WALK,
	ACTION_STATE_ATTACK,
	ACTION_STATE_HURT,
	ACTION_STATE_DEAD
}ActionState;

// 碰撞盒
typedef struct _BoundingBox
{
	cocos2d::Rect actual; // 以屏幕左下角为原点，碰撞检测时使用
	cocos2d::Rect original; // 以精灵左下角为原点，用来更新actual
}BoundingBox;

class BaseSprite : public cocos2d::Sprite
{
public:
	BaseSprite();
	~BaseSprite();
	// 精灵的五个行为动画效果：
	void runIdleAction();  // 空闲
	void runWalkAction();  // 行走
	void runAttackAction();  // 攻击
	void runHurtAction();  // 受伤
	void runDeadAction();  // 死亡

	
	// CC_SYNTHESIZE_RETAIN(cocos2d::CCObject*, m_weapon, Weapon);定义了一个 Object* 类型的变量 m_weapon ，并直接定义默认的 get/set 方法（后面一个参数 Weapon 是方法名）
	// 即声明了一个 cocos2d::CCObject* getWeapon();和一个 void setWeapon(cocos2d::CCObject* value);
	// 在 setWeapon 的时候，调用原有 m_weapon 的 release，并且调用新值的 retain。（当然，已经排除了意外情况，如相等或者NULL之类的）
	// 在 CC_SYNTHESIZE 之后直接声明函数或者变量都会变成 public
	// 这里都声明为指针类型变量，所有在析构函数里要被 release 掉
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, idle, IdleAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, walk, WalkAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, attack, AttackAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, hurt, HurtAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, dead, DeadAction);

	CC_SYNTHESIZE(ActionState, currActionState, CurrActionState);  // 当前状态

	CC_SYNTHESIZE(cocos2d::Point, velocity, Velocity);  // 速度属性
	CC_SYNTHESIZE(int, hp, HP);  // 生命值属性
	CC_SYNTHESIZE(unsigned int, atk, ATK);  // 攻击力

	std::function<void(void)> pAttack; // 表示 void pAttack();

	// “立即返回空闲状态”回调函数
	cocos2d::CallFunc* createIdleCallbackFunc();



    CC_SYNTHESIZE(BoundingBox, m_bodyBox, BodyBox);
	CC_SYNTHESIZE(BoundingBox, m_hitBox, HitBox);

	virtual void setPosition(const cocos2d::Point &position);
	BoundingBox createBoundingBox(cocos2d::Point origin, cocos2d::Size size);
	void updateBoxes();

protected:
	// 根据图片路径，帧数，每秒显示的帧数来创建动画
	static cocos2d::Animation* createAnimation(const char* formatStr, int frameCount, int fps);
//private:
	// 用来判断当前状态 currActionState 能否转换到 actionState
	bool changeState(ActionState actionState);
};
#endif

