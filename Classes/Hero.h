#ifndef __HERO_H__
#define __HERO_H__

#include "cocos2d.h"
#include "BaseSprite.h"
#include "ArrowPathBezier.h"

class Hero : public BaseSprite
{
public:
	Hero();
	~Hero();
	bool init(int pl, int pr, Vec2 pos, int d);
	static Hero* create(int pl, int pr, Vec2 pos, int d);  // p代表哪个英雄，d代表哪个玩家

	int pl;  // 代表哪个英雄
	int pr;  // 代表哪个道具
	int d;  // 代表哪个玩家操控

	void  rotateArrow(float angle);  // 旋转武器
	void shootArrow();  // 发射
	void finishRunAction();
	void runAttackAction();
	/*CREATE_FUNC(Hero);*/
	void loadGate_1();
	void loadGate_2();
	void loadGate_3();
	std::function<void(cocos2d::Point)> pWalk;
	std::function<void(void)> pStop;
	std::function<void(void)> pUseProp;
	float power;  // 蓄力
	bool isRunAttackAction;
	
	void setPower(float p);
	void createHpBar(int p, int pr);
	void createWeapon(int p);


	cocos2d::Vector<Sprite*> bullets;  // 这个英雄发射的子弹
	ProgressTimer* playerarrow;
	Sprite* playerarrowBg;  // 武器

	ProgressTimer* hpBar;  // 血条
	Sprite* hpBgSprite;
	ProgressTimer* mpBar;  // 蓝条
	Sprite* mpBgSprite;
	ProgressTimer* cdBar;  // CD条
	Sprite* cdBgSprite;

	bool canUseProp;

	/*   在 BaseSprite.h 中还有这三种属性
	CC_SYNTHESIZE(cocos2d::Point, velocity, Velocity);  // 速度属性
	CC_SYNTHESIZE(unsigned int, hp, HP);  // 生命值属性，控制 hpBar
	CC_SYNTHESIZE(unsigned int, atk, ATK);  // 攻击力
	*/

private:
	ccQuadBezierConfig bezier;  // 贝塞尔曲线配置信息



	Vec2 playerPos;  // 英雄位置
	float rotateRadians;
	
	
};

#endif

