#include "Enemy.h"

USING_NS_CC;

Enemy::Enemy() :
	nextDecisionTime(0)
{
}

Enemy::~Enemy()
{
}
bool Enemy::init()
{
	bool ret = false;
	do
	{
		CC_BREAK_IF(!this->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy_idle_0.png")));
		auto idleAnimation = this->createAnimation("enemy_idle_%d.png", 1, 2);  // ���ж���ֻ��1֡  ÿ��2֡
		this->setIdleAction(RepeatForever::create(Animate::create(idleAnimation)));

		auto walkAnimation = this->createAnimation("enemy_walk_%d.png", 6, 12);  // ���߶���ֻ��6֡  ÿ��12֡
		this->setWalkAction(Sequence::create(Animate::create(walkAnimation), BaseSprite::createIdleCallbackFunc(), NULL));

		auto delayTime = DelayTime::create(5.0f);
		auto attackAnimation = this->createAnimation("enemy_attack_%d.png", 7, 14);  // ��������ֻ��7֡  ÿ��14֡
		this->setAttackAction(Sequence::create(Animate::create(attackAnimation), BaseSprite::createIdleCallbackFunc(),delayTime, NULL));  // ����֮�������Ϊ����״̬

		auto hurtAnimation = this->createAnimation("enemy_hurt_%d.png", 3, 6);  // ���˶���ֻ��3֡  ÿ��6֡
		this->setHurtAction(Sequence::create(Animate::create(hurtAnimation), BaseSprite::createIdleCallbackFunc(), NULL));  // ����֮�������Ϊ����״̬

		auto deadAnimation = this->createAnimation("enemy_dead_%d.png", 1, 2);  // ��������ֻ��1֡  ÿ��2֡
		this->setDeadAction(Sequence::create(Animate::create(deadAnimation), Blink::create(3, 9), NULL));  // ����֮��������˸

		Size enemyShowSize = this->getDisplayFrame()->getRect().size;
		this->m_bodyBox = this->createBoundingBox(Point(-enemyShowSize.width / 2, -enemyShowSize.height / 2), enemyShowSize);
		this->m_hitBox = this->createBoundingBox(Point(enemyShowSize.width / 2, 10), Size(100, 90));

		createHpBar();
		ret = true;
	} while (0);
	return ret;
}

void Enemy::execute(const cocos2d::Point& target, float targetBodyWidth)
{
	if (nextDecisionTime == 0)
	{
		this->decide(target, targetBodyWidth);
	}
	else {
		--nextDecisionTime;
	}
}

void Enemy::createHpBar()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	// ����Ѫ��
	char hpBg[20];
	char hp[20];
	sprintf(hpBg, "enemy_hpBg.png");
	sprintf(hp, "enemy_hp.png");
	enemyHpBgSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(hpBg));
	this->addChild(enemyHpBgSprite, 3);
	auto enemyHpBarSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(hp));
	enemyHpBar = ProgressTimer::create(enemyHpBarSprite);
	enemyHpBar->setType(ProgressTimer::Type::BAR);
	enemyHpBar->setMidpoint(Vec2(0, 0.5f));
	enemyHpBar->setBarChangeRate(Vec2(1, 0));
	enemyHpBar->setPercentage(100);
	this->addChild(enemyHpBar, 3);
	enemyHpBgSprite->setPosition(this->getPositionX(), this->getPositionY() + enemyHpBgSprite->getContentSize().height / 2+this->getContentSize().height);
	enemyHpBar->setPosition(this->getPositionX(), this->getPositionY() + enemyHpBar->getContentSize().height / 2 + this->getContentSize().height);
}

void Enemy::decide(const cocos2d::Point& target, float targetBodyWidth)
{
	auto location = this->getPosition();  // ����λ��
	auto distance = location.getDistance(target);  // ��Ӣ�۵ľ���
	distance = distance - (targetBodyWidth / 2 + this->getDisplayFrame()->getRect().size.width / 2 + 30);
	auto isFlippedX = this->isFlippedX();
	auto isOnTargetLeft = (location.x < target.x ? true : false);
	// ��������������ƶ�������Ӣ����ߣ����� �����������ƶ�������Ӣ���ұߣ���ô������ֻ�����Ѳ�߻�����Ϣ
	if ((isFlippedX && isOnTargetLeft) || (!isFlippedX && !isOnTargetLeft))
	{
		this->aiState = CCRANDOM_0_1() > 0.5f ? AI_PATROL : AI_IDLE;
	}
	else {
		if (distance < eyeArea)  // ����������˷�����
		{
			this->aiState = distance < attackArea ? AI_ATTACK : AI_PURSUIT;  // �ڻ����˹�����Χ�ڣ��ǻ�����ֱ�ӹ���������͸���
		}
		else {  // û�б����֣������˾ͻ�Ѳ�߻�����Ϣ
			this->aiState = CCRANDOM_0_1() > 0.5f ? AI_PATROL : AI_IDLE;
		}
	}

	switch (aiState)
	{
	case AI_ATTACK:  // ����
	{
		this->runAttackAction();
		this->pAttack();
		this->nextDecisionTime = 50;
	}
	break;
	case AI_IDLE:  // x��Ϣ
	{
		this->runIdleAction();
		this->nextDecisionTime = CCRANDOM_0_1() * 100;
	}
	break;
	case AI_PATROL:  // Ѳ��
	{
		this->runWalkAction();
		this->moveDirection.x = CCRANDOM_MINUS1_1();  // ����һ�� [-1, 1] �������
		this->moveDirection.y = CCRANDOM_MINUS1_1();
		moveDirection.x = moveDirection.x > 0 ? (moveDirection.x + velocity.x) : (moveDirection.x - velocity.x);
		moveDirection.y = moveDirection.y > 0 ? (moveDirection.y + velocity.y) : (moveDirection.y - velocity.y);
		this->nextDecisionTime = CCRANDOM_0_1() * 100;
	}
	break;
	case AI_PURSUIT:
	{
		this->runWalkAction();
		this->moveDirection = ccpNormalize(target - location);
		this->setFlippedX(moveDirection.x < 0 ? true : false);
		moveDirection.x = moveDirection.x > 0 ? (moveDirection.x + velocity.x) : (moveDirection.x - velocity.x);
		moveDirection.y = moveDirection.y > 0 ? (moveDirection.y + velocity.y) : (moveDirection.y - velocity.y);
		this->nextDecisionTime = 10;
	}
	break;
	}
}
