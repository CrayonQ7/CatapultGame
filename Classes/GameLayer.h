#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "cocos2d.h"
#include "Hero.h"
//#include "Enemy.h"

//#define MIN_ENEMY_COUNT 5
class GameLayer : public cocos2d::Layer
{
public:
	GameLayer();
	~GameLayer();
	static GameLayer* create(int pl1, int pr1, int pl2, int pr2, int bg , float bv, float ev, int bgm);
	/*CREATE_FUNC(GameLayer);*/
	virtual bool init(int pl1, int pr1, int pl2, int pr2, int bg, float bv, float ev, int bgm);
	/*virtual bool init();*/
	// 定义 Hero* 类型变量 hero1、hero2，并只声明了其 get 方法
	CC_SYNTHESIZE_READONLY(Hero*, hero1, Hero1);
	CC_SYNTHESIZE_READONLY(Hero*, hero2, Hero2);

	// GameLayer设置了英雄的如何移动等,即其移动范围等等
	void onHero1Walk(cocos2d::Point direction);
	void onHero1Attack();
	void onHero1Stop();
	void onHero1UseProp();
	void onHero2Walk(cocos2d::Point direction);
	void onHero2Attack();
	void onHero2Stop();
	void onHero2UseProp();
	void update(float dt);
	void updateHero(float dt);
	void uodateOnce1(float dt);
	void uodateOnce2(float dt);
	void onMove(Hero* hero);

	void isCreatedP1();
	void isCreatedP2();
	//void prop2CallFunc(int d);
	//void prop3CallFunc(int d);
	//void updateEnemies(float dt);

	//void addEnemy();
	//void onEnemyAttack(BaseSprite *pSprite);

	// 表示每个瓦片的宽高，用来控制英雄的行走区域
	float tileWidth;
	float tileHeight;

	float screenWidth;
	float screenHeight;
	cocos2d::Point origin;
	cocos2d::Size visibleSize;
	int p1;
	int p2;

	Sprite* prop1;
	Sprite* prop2;
	bool isCreated1;
	bool isCreated2;
	//cocos2d::Array *enemies;
	//CREATE_FUNC(GameLayer);  // 自动生成一个不带参数的 create 静态方法，返回一个 GameLayer* 类型指针。自动调用了init和autorelease方法

	float backgroundVolume, effectVolume;  // 背景音乐音量，音效音量
	int curBgm;  //当前选择的背景音乐编号索引
private:
	cocos2d::TMXTiledMap* tmx;
};
#endif