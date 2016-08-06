#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
#include "BaseSprite.h"

// 机器人的四种状态：休闲、巡逻、攻击、跟随
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
	CC_SYNTHESIZE(cocos2d::Point, moveDirection, MoveDirection);  // 行走方向
	CC_SYNTHESIZE(float, eyeArea, EyeArea);  // 巡逻范围
	CC_SYNTHESIZE(float, attackArea, AttackArea);  // 攻击范围
	CC_SYNTHESIZE(AiState, aiState, AiState);  // 当前AI状态
	void execute(const cocos2d::Point& target, float targetBodyWidth);  // 在GameLayer中实时更新机器人的状态
	void createHpBar();
	cocos2d::ProgressTimer* enemyHpBar;  // 血条
	cocos2d::Sprite*enemyHpBgSprite;
private:
	void decide(const cocos2d::Point& target, float targetBodyWidth);  // 机器人如何决策（机器人的内心世界= =）
	unsigned int nextDecisionTime;  // 距离下一次决策的时间
};
#endif
