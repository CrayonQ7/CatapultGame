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
	virtual bool init(int pl1, int pr1, int pl2, int pr2, int bg, float bv, float ev, int bgm);
	// ���� Hero* ���ͱ��� hero1��hero2����ֻ�������� get ����
	CC_SYNTHESIZE_READONLY(Hero*, hero1, Hero1);
	CC_SYNTHESIZE_READONLY(Hero*, hero2, Hero2);

	// GameLayer������Ӣ�۵�����ƶ���,�����ƶ���Χ�ȵ�
	void onHero1Walk(cocos2d::Point direction);
	void onHero1Attack();
	void onHero1Stop();
	void onHero1UseProp();
	void onHero2Walk(cocos2d::Point direction);
	void onHero2Attack();
	void onHero2Stop();
	void onHero2UseProp();
	void onMove(Hero* hero);

	// ������
	void update(float dt);
	void updateHero(float dt);
	void uodateOnce1(float dt);
	void uodateOnce2(float dt);
	void updateOnce(float dt);
	

	void isCreatedP1();
	void isCreatedP2();

	// ��ʾÿ����Ƭ�Ŀ�ߣ���������Ӣ�۵���������
	float tileWidth;
	float tileHeight;

	float screenWidth;
	float screenHeight;
	cocos2d::Point origin;
	cocos2d::Size visibleSize;
	int p1;
	int p2;

	ParticleFire* fire;
	ParticleFire* fire2;
	Sprite* shield;
	Sprite* shield2;
	Sprite* sludge;
	Sprite* sludge2;
	Sprite* prop1;
	Sprite* prop2;
	bool isCreated1;
	bool isCreated2;
	bool hasShield1;
	bool hasShield2;
	bool hasSludge1;
	bool hasSludge2;
	//CREATE_FUNC(GameLayer);  // �Զ�����һ������������ create ��̬����������һ�� GameLayer* ����ָ�롣�Զ�������init��autorelease����

	float backgroundVolume, effectVolume;  // ����������������Ч����
	int curBgm;  //��ǰѡ��ı������ֱ������

	void gameRuleCallback(Ref* pSender);
private:
	cocos2d::TMXTiledMap* tmx;
};
#endif