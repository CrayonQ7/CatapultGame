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
	static GameLayer* create(int pl1, int pl2, int bg);
	/*CREATE_FUNC(GameLayer);*/
	virtual bool init(int pl1, int pl2, int bg);
	/*virtual bool init();*/
	// ���� Hero* ���ͱ��� hero1��hero2����ֻ�������� get ����
	CC_SYNTHESIZE_READONLY(Hero*, hero1, Hero1);
	CC_SYNTHESIZE_READONLY(Hero*, hero2, Hero2);

	// GameLayer������Ӣ�۵�����ƶ���,�����ƶ���Χ�ȵ�
	void onHero1Walk(cocos2d::Point direction);
	void onHero1Attack();
	void onHero1Stop();
	void onHero2Walk(cocos2d::Point direction);
	void onHero2Attack();
	void onHero2Stop();
	void update(float dt);
	void updateHero(float dt);
	void onMove(Hero* hero);
	//void updateEnemies(float dt);

	//void addEnemy();
	//void onEnemyAttack(BaseSprite *pSprite);

	// ��ʾÿ����Ƭ�Ŀ�ߣ���������Ӣ�۵���������
	float tileWidth;
	float tileHeight;


	float screenWidth;
	float screenHeight;
	cocos2d::Point origin;
	cocos2d::Size visibleSize;
	int p1;
	int p2;
	//cocos2d::Array *enemies;
	//CREATE_FUNC(GameLayer);  // �Զ�����һ������������ create ��̬����������һ�� GameLayer* ����ָ�롣�Զ�������init��autorelease����
private:
	cocos2d::TMXTiledMap* tmx;
};
#endif