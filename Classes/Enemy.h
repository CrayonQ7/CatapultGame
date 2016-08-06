#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
#include "BaseSprite.h"

// �����˵�����״̬�����С�Ѳ�ߡ�����������
typedef enum
{
	AI_IDLE = 0,
    AI_PATROL,
	AI_ATTACK,
	AI_PURSUIT
}AiState;

class Enemy : public BaseSprite
{
public:
	Enemy();
	~Enemy();
	bool init();
	CREATE_FUNC(Enemy);
	CC_SYNTHESIZE(cocos2d::Point, moveDirection, MoveDirection);  // ���߷���
	CC_SYNTHESIZE(float, eyeArea, EyeArea);  // Ѳ�߷�Χ
	CC_SYNTHESIZE(float, attackArea, AttackArea);  // ������Χ
	CC_SYNTHESIZE(AiState, aiState, AiState);  // ��ǰAI״̬
	void execute(const cocos2d::Point& target, float targetBodyWidth);  // ��GameLayer��ʵʱ���»����˵�״̬
	void createHpBar();
	cocos2d::ProgressTimer* enemyHpBar;  // Ѫ��
	cocos2d::Sprite*enemyHpBgSprite;
private:
	void decide(const cocos2d::Point& target, float targetBodyWidth);  // ��������ξ��ߣ������˵���������= =��
	unsigned int nextDecisionTime;  // ������һ�ξ��ߵ�ʱ��
};
#endif
