#ifndef __BASESPRITE_H__
#define __BASESPRITE_H__

#include "cocos2d.h"
// ������5��״̬��idle���У�walk���ߣ�attack������hurt���ˣ�dead����
typedef enum
{
	ACTION_STATE_NONE = 0,
	ACTION_STATE_IDLE,
	ACTION_STATE_WALK,
	ACTION_STATE_ATTACK,
	ACTION_STATE_HURT,
	ACTION_STATE_DEAD
}ActionState;

// ��ײ��
typedef struct _BoundingBox
{
	cocos2d::Rect actual; // ����Ļ���½�Ϊԭ�㣬��ײ���ʱʹ��
	cocos2d::Rect original; // �Ծ������½�Ϊԭ�㣬��������actual
}BoundingBox;

class BaseSprite : public cocos2d::Sprite
{
public:
	BaseSprite();
	~BaseSprite();
	// ����������Ϊ����Ч����
	void runIdleAction();  // ����
	void runWalkAction();  // ����
	void runAttackAction();  // ����
	void runHurtAction();  // ����
	void runDeadAction();  // ����

	
	// CC_SYNTHESIZE_RETAIN(cocos2d::CCObject*, m_weapon, Weapon);������һ�� Object* ���͵ı��� m_weapon ����ֱ�Ӷ���Ĭ�ϵ� get/set ����������һ������ Weapon �Ƿ�������
	// ��������һ�� cocos2d::CCObject* getWeapon();��һ�� void setWeapon(cocos2d::CCObject* value);
	// �� setWeapon ��ʱ�򣬵���ԭ�� m_weapon �� release�����ҵ�����ֵ�� retain������Ȼ���Ѿ��ų����������������Ȼ���NULL֮��ģ�
	// �� CC_SYNTHESIZE ֮��ֱ�������������߱��������� public
	// ���ﶼ����Ϊָ�����ͱ���������������������Ҫ�� release ��
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, idle, IdleAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, walk, WalkAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, attack, AttackAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, hurt, HurtAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, dead, DeadAction);

	CC_SYNTHESIZE(ActionState, currActionState, CurrActionState);  // ��ǰ״̬

	CC_SYNTHESIZE(cocos2d::Point, velocity, Velocity);  // �ٶ�����
	CC_SYNTHESIZE(int, hp, HP);  // ����ֵ����
	CC_SYNTHESIZE(unsigned int, atk, ATK);  // ������

	std::function<void(void)> pAttack; // ��ʾ void pAttack();

	// ���������ؿ���״̬���ص�����
	cocos2d::CallFunc* createIdleCallbackFunc();



    CC_SYNTHESIZE(BoundingBox, m_bodyBox, BodyBox);
	CC_SYNTHESIZE(BoundingBox, m_hitBox, HitBox);

	virtual void setPosition(const cocos2d::Point &position);
	BoundingBox createBoundingBox(cocos2d::Point origin, cocos2d::Size size);
	void updateBoxes();

protected:
	// ����ͼƬ·����֡����ÿ����ʾ��֡������������
	static cocos2d::Animation* createAnimation(const char* formatStr, int frameCount, int fps);
//private:
	// �����жϵ�ǰ״̬ currActionState �ܷ�ת���� actionState
	bool changeState(ActionState actionState);
};
#endif

