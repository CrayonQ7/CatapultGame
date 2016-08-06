#ifndef __AMGAMELAYER_H__
#define __AMGAMELAYER_H__

#include "cocos2d.h"
#include "AMHero.h"
#include "Enemy.h"

#define MIN_ENEMY_COUNT 5
class AMGameLayer : public cocos2d::Layer
{
public:
	AMGameLayer();
	~AMGameLayer();
	static AMGameLayer* create(int pl, int bg, int bgm); // 传入的是初始化哪个hero，以及加载哪副tmx，以及播放哪首bgm
	virtual bool init(int pl, int bg, int bgm);
	// 定义 AMHero* 类型变量 amHero，并只声明了其 get 方法
	CC_SYNTHESIZE_READONLY(AMHero*, amHero, AMHero);

	// 碰撞检测
	bool collisionDetection(const BoundingBox &hitBox, const BoundingBox &bodyBox);

	// GameLayer设置了英雄的如何移动等
	void onHeroWalk(cocos2d::Point direction);
	void onHeroAttack();
	void onHeroStop();
	void update(float dt);
	void updateHero(float dt);
	void updateEnemies(float dt);
	void addEnemy();
	void onEnemyAttack(BaseSprite *pSprite);

	// 表示每个瓦片的宽高，用来控制英雄的行走区域
	float tileWidth;
	float tileHeight;

	float screenWidth;
	float screenHeight;
	cocos2d::Point origin;
	cocos2d::Size visibleSize;

	int count;
	//CREATE_FUNC(GameLayer);  // 自动生成一个不带参数的 create 静态方法，返回一个 GameLayer* 类型指针。自动调用了init和autorelease方法
private:
	cocos2d::TMXTiledMap* tmx;
	cocos2d::Vector<Enemy*> enemies;
};
#endif
