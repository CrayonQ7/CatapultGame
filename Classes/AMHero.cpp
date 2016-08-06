#include "AMHero.h"
USING_NS_CC;
AMHero::AMHero()
{
}

AMHero::~AMHero()
{
}

AMHero * AMHero::create(int pl)
{
	AMHero* pRet = new(std::nothrow) AMHero();
	if (pRet && pRet->init(pl))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool AMHero::init(int pl)
{
	bool ret = false;
	switch (pl)
	{
	case 1:
		CC_BREAK_IF(!this->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("idle0.png")));
		ret = true;
		loadHero_1();
		break;
	case 2:
		CC_BREAK_IF(!this->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Hero_2_Idle_0.png")));
		ret = true;
		loadHero_2();
		break;
	case 3:
		CC_BREAK_IF(!this->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Hero_3_Idle_0.png")));
		ret = true;
		loadHero_3();
		break;
	}
	return ret;
}

void AMHero::loadHero_1()
{
	hp = 100;
	atk = 6;
	auto idleAnimation = this->createAnimation("idle%d.png", 1, 2);  // ���ж���ֻ��1֡  ÿ��2֡
	this->setIdleAction(RepeatForever::create(Animate::create(idleAnimation)));

	auto walkAnimation = this->createAnimation("run%d.png", 6, 12);  // ���߶���ֻ��7֡  ÿ��14֡
	this->setWalkAction(Sequence::create(Animate::create(walkAnimation), BaseSprite::createIdleCallbackFunc(), NULL));

	auto attackAnimation = this->createAnimation("leg%d.png", 5, 10);  // ��������ֻ��7֡  ÿ��14֡
	this->setAttackAction(Sequence::create(Animate::create(attackAnimation), BaseSprite::createIdleCallbackFunc(), NULL));  // ����֮�������Ϊ����״̬

	auto hurtAnimation = this->createAnimation("hurt%d.png", 6, 12);  // ���˶���ֻ����֡  ÿ��4֡
	this->setHurtAction(Sequence::create(Animate::create(hurtAnimation), BaseSprite::createIdleCallbackFunc(), NULL));  // ����֮�������Ϊ����״̬

	auto deadAnimation = this->createAnimation("fist%d.png", 4, 8);  // ��������ֻ����֡  ÿ��4֡
	this->setDeadAction(Sequence::create(Animate::create(deadAnimation), Blink::create(3, 9), NULL));  // ����֮��������˸

	Size heroShowSize = this->getDisplayFrame()->getRect().size;
	this->m_bodyBox = this->createBoundingBox(Point(-heroShowSize.width / 2, -heroShowSize.height / 2), heroShowSize);
	//this->m_bodyBox = this->createBoundingBox(Point(0, 0), heroShowSize);
	this->m_hitBox = this->createBoundingBox(Point(heroShowSize.width / 2, -20), Size(30, 50));
}

void AMHero::loadHero_2()
{
	hp = 100;
	atk = 6;
	auto idleAnimation = this->createAnimation("Hero_2_Idle_%d.png", 4, 8);  // ���ж���ֻ��1֡  ÿ��2֡
	this->setIdleAction(RepeatForever::create(Animate::create(idleAnimation)));

	auto walkAnimation = this->createAnimation("Hero_2_Walk_%d.png", 8, 16);  // ���߶���ֻ��7֡  ÿ��14֡
	this->setWalkAction(Sequence::create(Animate::create(walkAnimation), BaseSprite::createIdleCallbackFunc(), NULL));

	auto attackAnimation = this->createAnimation("Hero_2_Attack_%d.png", 7, 14);  // ��������ֻ��7֡  ÿ��14֡
	this->setAttackAction(Sequence::create(Animate::create(attackAnimation), BaseSprite::createIdleCallbackFunc(), NULL));  // ����֮�������Ϊ����״̬

	auto hurtAnimation = this->createAnimation("Hero_2_Hurt_%d.png", 2, 4);  // ���˶���ֻ����֡  ÿ��4֡
	this->setHurtAction(Sequence::create(Animate::create(hurtAnimation), BaseSprite::createIdleCallbackFunc(), NULL));  // ����֮�������Ϊ����״̬

	auto deadAnimation = this->createAnimation("Hero_2_Dead_%d.png", 3, 6);  // ��������ֻ����֡  ÿ��4֡
	this->setDeadAction(Sequence::create(Animate::create(deadAnimation), Blink::create(3, 9), NULL));  // ����֮��������˸

	Size heroShowSize = this->getDisplayFrame()->getRect().size;
	this->m_bodyBox = this->createBoundingBox(Point(-heroShowSize.width / 2, -heroShowSize.height / 2), heroShowSize);
	//this->m_bodyBox = this->createBoundingBox(Point(0, 0), heroShowSize);
	this->m_hitBox = this->createBoundingBox(Point(heroShowSize.width / 2, -20), Size(30, 50));
}

void AMHero::loadHero_3()
{
	hp = 100;
	atk = 6;
	auto idleAnimation = this->createAnimation("Hero_3_Idle_%d.png", 7, 14);  // ���ж���ֻ��7֡  ÿ��14֡
	this->setIdleAction(RepeatForever::create(Animate::create(idleAnimation)));

	auto walkAnimation = this->createAnimation("Hero_3_Walk_%d.png", 9, 18);  // ���߶���ֻ��7֡  ÿ��14֡
	this->setWalkAction(Sequence::create(Animate::create(walkAnimation), BaseSprite::createIdleCallbackFunc(), NULL));

	auto attackAnimation = this->createAnimation("Hero_3_Attack_%d.png", 8, 16);  // ��������ֻ��8֡  ÿ��16֡
	this->setAttackAction(Sequence::create(Animate::create(attackAnimation), BaseSprite::createIdleCallbackFunc(), NULL));  // ����֮�������Ϊ����״̬

	auto hurtAnimation = this->createAnimation("Hero_3_Hurt_%d.png", 2, 4);  // ���˶���ֻ����֡  ÿ��4֡
	this->setHurtAction(Sequence::create(Animate::create(hurtAnimation), BaseSprite::createIdleCallbackFunc(), NULL));  // ����֮�������Ϊ����״̬

	auto deadAnimation = this->createAnimation("Hero_3_Dead_%d.png", 1, 2);  // ��������ֻ��1֡  ÿ��2֡
	this->setDeadAction(Sequence::create(Animate::create(deadAnimation), Blink::create(3, 9), NULL));  // ����֮��������˸

	//Size heroShowSize = this->getDisplayFrame()->getRect().size;
	Size heroShowSize = this->getContentSize();
	this->m_bodyBox = this->createBoundingBox(Point(-heroShowSize.width / 2, -heroShowSize.height / 2), heroShowSize);

	this->m_hitBox = this->createBoundingBox(Point(heroShowSize.width / 2, -heroShowSize.height / 2), Size(221, 74));


}

void AMHero::createHpBar(int p)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	// ����Ѫ��
	char hpBg[20];
	char hp[20];
	sprintf(hpBg, "Hero_%d_hpBg.png", p);
	sprintf(hp, "Hero_%d_hp.png", p);
	hpBgSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(hpBg));
	this->getParent()->addChild(hpBgSprite, 3);
	hpBar = ProgressTimer::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(hp)));
	hpBar->setType(ProgressTimer::Type::BAR);
	hpBar->setMidpoint(Vec2(0, 0.5f));
	hpBar->setBarChangeRate(Vec2(1, 0));
	hpBar->setPercentage(100);
	this->getParent()->addChild(hpBar, 3);
	hpBgSprite->setPosition(origin.x + hpBgSprite->getContentSize().width / 2, origin.y + visibleSize.height - hpBgSprite->getContentSize().height / 2);
	hpBar->setPosition(origin.x + hpBar->getContentSize().width / 2, origin.y + visibleSize.height - hpBar->getContentSize().height / 2);
}
