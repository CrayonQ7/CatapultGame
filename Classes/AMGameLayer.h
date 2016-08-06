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
	static AMGameLayer* create(int pl, int bg, int bgm); // ������ǳ�ʼ���ĸ�hero���Լ������ĸ�tmx���Լ���������bgm
	virtual bool init(int pl, int bg, int bgm);
	// ���� AMHero* ���ͱ��� amHero����ֻ�������� get ����
	CC_SYNTHESIZE_READONLY(AMHero*, amHero, AMHero);

	// ��ײ���
	bool collisionDetection(const BoundingBox &hitBox, const BoundingBox &bodyBox);

	// GameLayer������Ӣ�۵�����ƶ���
	void onHeroWalk(cocos2d::Point direction);
	void onHeroAttack();
	void onHeroStop();
	void update(float dt);
	void updateHero(float dt);
	void updateEnemies(float dt);
	void addEnemy();
	void onEnemyAttack(BaseSprite *pSprite);

	// ��ʾÿ����Ƭ�Ŀ�ߣ���������Ӣ�۵���������
	float tileWidth;
	float tileHeight;

	float screenWidth;
	float screenHeight;
	cocos2d::Point origin;
	cocos2d::Size visibleSize;

	int count;
	//CREATE_FUNC(GameLayer);  // �Զ�����һ������������ create ��̬����������һ�� GameLayer* ����ָ�롣�Զ�������init��autorelease����
private:
	cocos2d::TMXTiledMap* tmx;
	cocos2d::Vector<Enemy*> enemies;
};
#endif
