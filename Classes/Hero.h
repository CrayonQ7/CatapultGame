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
	static Hero* create(int pl, int pr, Vec2 pos, int d);  // p�����ĸ�Ӣ�ۣ�d�����ĸ����

	int pl;  // �����ĸ�Ӣ��
	int pr;  // �����ĸ�����
	int d;  // �����ĸ���Ҳٿ�

	void  rotateArrow(float angle);  // ��ת����
	void shootArrow();  // ����
	void finishRunAction();
	void runAttackAction();
	/*CREATE_FUNC(Hero);*/
	void loadGate_1();
	void loadGate_2();
	void loadGate_3();
	std::function<void(cocos2d::Point)> pWalk;
	std::function<void(void)> pStop;
	std::function<void(void)> pUseProp;
	float power;  // ����
	bool isRunAttackAction;
	
	void setPower(float p);
	void createHpBar(int p);



	cocos2d::Vector<Sprite*> bullets;  // ���Ӣ�۷�����ӵ�
	ProgressTimer* playerarrow;
	Sprite* playerarrowBg;  // ����

	ProgressTimer* hpBar;  // Ѫ��
	Sprite* hpBgSprite;

	/*   �� BaseSprite.h �л�������������
	CC_SYNTHESIZE(cocos2d::Point, velocity, Velocity);  // �ٶ�����
	CC_SYNTHESIZE(unsigned int, hp, HP);  // ����ֵ���ԣ����� hpBar
	CC_SYNTHESIZE(unsigned int, atk, ATK);  // ������
	*/

private:
	ccQuadBezierConfig bezier;  // ����������������Ϣ



	Vec2 playerPos;  // Ӣ��λ��
	float rotateRadians;
	
	
};

#endif

