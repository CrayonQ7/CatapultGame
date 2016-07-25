#include "Hero.h"
USING_NS_CC;
Hero::Hero()
{
	hpBar = NULL;
	hpBgSprite = NULL;
	playerarrow = NULL;
	playerarrowBg = NULL;  // 武器
	mpBar = NULL;  // 蓝条
	mpBgSprite = NULL;
	cdBar = NULL;  // CD条
	cdBgSprite = NULL;
	power = 1;
	pl = pr = d = 0;
	bezier.controlPoint = Vec2(0, 0);
	bezier.endPosition = Vec2(0, 0);
}


Hero::~Hero()
{
}

Hero * Hero::create(int pl, int pr, Vec2 pos, int d)
{
	Hero* pRet = new(std::nothrow) Hero();
	if (pRet && pRet->init(pl, pr, pos, d))
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

bool Hero::init(int pl, int pr, Vec2 pos, int d)
{
	bool ret = false;
	playerPos = pos;
	this->pl = pl;
	this->pr = pr;
	this->d = d;
	this->canUseProp = true;
	switch (pl)
	{
	case 1:
		CC_BREAK_IF(!this->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_1_Idle_0.png")));
		ret = true;
		loadGate_1();
		break;
	case 2:
		CC_BREAK_IF(!this->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_2_Idle_0.png")));
		ret = true;
		loadGate_2();
		break;
	case 3:
		CC_BREAK_IF(!this->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_3_Idle_0.png")));
		ret = true;
		loadGate_3();
		break;
	}
	return ret;
}




void Hero::loadGate_1()
{
	hp = 100;
	atk = 5;
	this->setPosition(Vec2(playerPos));
	auto idleAnimation = this->createAnimation("Gate_1_Idle_%d.png", 2, 4);  // 空闲动画只有两帧  每秒4帧
	this->setIdleAction(RepeatForever::create(Animate::create(idleAnimation)));

	auto walkAnimation = this->createAnimation("Gate_1_Walk_%d.png", 3, 6);  // 行走动画只有7帧  每秒14帧
	this->setWalkAction(Sequence::create(Animate::create(walkAnimation), BaseSprite::createIdleCallbackFunc(), NULL));

	auto attackAnimation = this->createAnimation("Gate_1_Attack_%d.png", 2, 4);  // 攻击动画只有7帧  每秒14帧
	this->setAttackAction(Sequence::create(Animate::create(attackAnimation), BaseSprite::createIdleCallbackFunc(), NULL));  // 攻击之后立马变为空闲状态

	auto hurtAnimation = this->createAnimation("Gate_1_Hurt_%d.png", 2, 4);  // 受伤动画只有两帧  每秒4帧
	this->setHurtAction(Sequence::create(Animate::create(hurtAnimation), BaseSprite::createIdleCallbackFunc(), NULL));  // 受伤之后立马变为空闲状态

	auto deadAnimation = this->createAnimation("Gate_1_Dead_%d.png", 2, 4);  // 死亡动画只有两帧  每秒4帧
	this->setDeadAction(Sequence::create(Animate::create(deadAnimation), Blink::create(3, 9), NULL));  // 死亡之后立马闪烁

	createWeapon(1);
}

void Hero::loadGate_2()
{
	hp = 100;
	atk = 7;
	this->setPosition(Vec2(playerPos));

	auto idleAnimation = this->createAnimation("Gate_2_Idle_%d.png", 2, 4);  // 空闲动画只有两帧  每秒4帧
	this->setIdleAction(RepeatForever::create(Animate::create(idleAnimation)));

	auto walkAnimation = this->createAnimation("Gate_2_Walk_%d.png", 3, 6);  // 行走动画只有7帧  每秒14帧
	this->setWalkAction(Sequence::create(Animate::create(walkAnimation), BaseSprite::createIdleCallbackFunc(), NULL));

	auto attackAnimation = this->createAnimation("Gate_2_Attack_%d.png", 2, 4);  // 攻击动画只有7帧  每秒14帧
	this->setAttackAction(Sequence::create(Animate::create(attackAnimation), BaseSprite::createIdleCallbackFunc(), NULL));  // 攻击之后立马变为空闲状态

	auto hurtAnimation = this->createAnimation("Gate_2_Hurt_%d.png", 2, 4);  // 受伤动画只有两帧  每秒4帧
	this->setHurtAction(Sequence::create(Animate::create(hurtAnimation), BaseSprite::createIdleCallbackFunc(), NULL));  // 受伤之后立马变为空闲状态

	auto deadAnimation = this->createAnimation("Gate_2_Dead_%d.png", 2, 4);  // 死亡动画只有两帧  每秒4帧
	this->setDeadAction(Sequence::create(Animate::create(deadAnimation), Blink::create(3, 9), NULL));  // 死亡之后立马闪烁

	createWeapon(2);
}

void Hero::loadGate_3()
{

	hp = 100;
	atk = 10;
	this->setPosition(Vec2(playerPos));
	auto idleAnimation = this->createAnimation("Gate_3_Idle_%d.png", 2, 4);  // 空闲动画只有两帧  每秒4帧
	this->setIdleAction(RepeatForever::create(Animate::create(idleAnimation)));

	auto walkAnimation = this->createAnimation("Gate_3_Walk_%d.png", 3, 6);  // 行走动画只有7帧  每秒14帧
	this->setWalkAction(Sequence::create(Animate::create(walkAnimation), BaseSprite::createIdleCallbackFunc(), NULL));

	auto attackAnimation = this->createAnimation("Gate_3_Attack_%d.png", 2, 4);  // 攻击动画只有7帧  每秒14帧
	this->setAttackAction(Sequence::create(Animate::create(attackAnimation), BaseSprite::createIdleCallbackFunc(), NULL));  // 攻击之后立马变为空闲状态

	auto hurtAnimation = this->createAnimation("Gate_3_Hurt_%d.png", 2, 4);  // 受伤动画只有两帧  每秒4帧
	this->setHurtAction(Sequence::create(Animate::create(hurtAnimation), BaseSprite::createIdleCallbackFunc(), NULL));  // 受伤之后立马变为空闲状态

	auto deadAnimation = this->createAnimation("Gate_3_Dead_%d.png", 2, 4);  // 死亡动画只有两帧  每秒4帧
	this->setDeadAction(Sequence::create(Animate::create(deadAnimation), Blink::create(3, 9), NULL));  // 死亡之后立马闪烁

	createWeapon(3);
}

// 蓄力
void Hero::setPower(float percent)
{
	if (percent > 100) percent = 100;
	if (percent > 36) power = percent / 36;
	else power = 1;
	playerarrow->setPercentage(percent);
}

void Hero::createHpBar(int p, int pr)
{

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	// 创建血条
	char hpBg[20];
	char hp[20];
	sprintf(hpBg, "Gate_%d_hpBg.png", p);
	sprintf(hp, "Gate_%d_hp.png", p);
	hpBgSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(hpBg));
	this->getParent()->addChild(hpBgSprite, 3);
	hpBar = ProgressTimer::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(hp)));
	hpBar->setType(ProgressTimer::Type::BAR);
	hpBar->setMidpoint(Vec2(0, 0.5f));
	hpBar->setBarChangeRate(Vec2(1, 0));
	hpBar->setPercentage(100);
	this->getParent()->addChild(hpBar, 3);
	// 创建蓝条
	//mpBgSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_mpBg.png"));
	mpBgSprite = Sprite::create("Gate_mpBg1.png");
	this->getParent()->addChild(mpBgSprite, 3);
	//mpBar = ProgressTimer::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_mp.png")));
	mpBar = ProgressTimer::create(Sprite::create("Gate_mp1.png"));
	mpBar->setType(ProgressTimer::Type::BAR);
	mpBar->setMidpoint(Vec2(0, 0.5f));
	mpBar->setBarChangeRate(Vec2(1, 0));
	mpBar->setPercentage(100);
	this->getParent()->addChild(mpBar, 3);
	// 创建CD条
	char cdBg[20];
	char cd[20];
	sprintf(cdBg, "prop_%d_0.png", pr);
	sprintf(cd, "prop_%d.png", pr);
	//cdBgSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(cdBg));
	cdBgSprite = Sprite::create(cdBg);
	this->getParent()->addChild(cdBgSprite, 3);
	//cdBar = ProgressTimer::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(cd)));
	cdBar = ProgressTimer::create(Sprite::create(cd));
	cdBar->setType(ProgressTimer::Type::BAR);
	cdBar->setMidpoint(Vec2(0.5, 0));
	cdBar->setBarChangeRate(Vec2(0, 1));
	cdBar->setPercentage(100);
	this->getParent()->addChild(cdBar, 3);
	if (d == 1)
	{
		hpBgSprite->setPosition(origin.x + hpBgSprite->getContentSize().width / 2, origin.y + visibleSize.height - hpBgSprite->getContentSize().height / 2);
		hpBar->setPosition(origin.x + hpBar->getContentSize().width / 2, origin.y + visibleSize.height - hpBar->getContentSize().height / 2);
		cdBgSprite->setPosition(hpBgSprite->getPositionX() + hpBgSprite->getContentSize().width/2 + 40, hpBgSprite->getPositionY() - hpBgSprite->getContentSize().height / 2);
		cdBar->setPosition(hpBgSprite->getPositionX() + hpBgSprite->getContentSize().width / 2 + 40, hpBar->getPositionY() - hpBar->getContentSize().height / 2);
	}
	else if (d == 2)
	{
		hpBgSprite->setPosition(origin.x + visibleSize.width - hpBgSprite->getContentSize().width / 2, origin.y + visibleSize.height - hpBgSprite->getContentSize().height / 2);
		hpBar->setPosition(origin.x + visibleSize.width - hpBar->getContentSize().width / 2, origin.y + visibleSize.height - hpBar->getContentSize().height / 2);
		cdBgSprite->setPosition(hpBgSprite->getPositionX() - hpBgSprite->getContentSize().width / 2 - 40, hpBgSprite->getPositionY() - hpBgSprite->getContentSize().height / 2);
		cdBar->setPosition(hpBar->getPositionX() - hpBgSprite->getContentSize().width / 2 - 40, hpBar->getPositionY() - hpBar->getContentSize().height / 2);
	}
	mpBgSprite->setPosition(hpBgSprite->getPositionX(), hpBgSprite->getPositionY() - hpBgSprite->getContentSize().height / 2 - 20);
	mpBar->setPosition(hpBar->getPositionX(), hpBar->getPositionY() - hpBar->getContentSize().height / 2 - 20);

}


// p代表英雄1、2、3，可根据不同英雄，创建不同的武器(目前还没实现)
void Hero::createWeapon(int p)
{
	// 左边的玩家拿pao1
	if (d == 1) {
		playerarrowBg = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("paoBg1.png"));
		playerarrowBg->setPosition(Vec2(playerarrowBg->getContentSize().width, playerarrowBg->getContentSize().height));
		playerarrowBg->setAnchorPoint(Vec2(0.125f, 0.45f));
		this->addChild(playerarrowBg, 2);
		auto playerarrowSp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("pao1.png"));
		playerarrow = ProgressTimer::create(playerarrowSp);
		playerarrow->setAnchorPoint(Vec2(0.125f, 0.45f));
		playerarrow->setType(ProgressTimer::Type::BAR);
		playerarrow->setMidpoint(Vec2(0, 0.5f));
		playerarrow->setBarChangeRate(Vec2(1, 0));
		playerarrow->setPercentage(0);
		playerarrow->setPosition(Vec2(playerarrowBg->getContentSize().width, playerarrowBg->getContentSize().height));
		this->addChild(playerarrow, 3);
	}
	// 右边的玩家拿pao2
	else if (d == 2)
	{
		playerarrowBg = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("paoBg2.png"));
		playerarrowBg->setPosition(Vec2(playerarrowBg->getContentSize().width / 4, playerarrowBg->getContentSize().height));
		playerarrowBg->setAnchorPoint(Vec2(0.875f, 0.45f));
		this->addChild(playerarrowBg, 2);
		auto playerarrowSp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("pao2.png"));
		playerarrow = ProgressTimer::create(playerarrowSp);
		playerarrow->setAnchorPoint(Vec2(0.875f, 0.45f));
		playerarrow->setType(ProgressTimer::Type::BAR);
		playerarrow->setMidpoint(Vec2(1, 0.5f));
		playerarrow->setBarChangeRate(Vec2(1, 0));
		playerarrow->setPercentage(0);
		playerarrow->setPosition(Vec2(playerarrowBg->getContentSize().width / 4, playerarrowBg->getContentSize().height));
		this->addChild(playerarrow, 3);
	}
}


// * ------------------------------------------ 调整炮口角度 -------------------------------------- *
// π/6  ~  π/3 
void Hero::rotateArrow(float angle)
{
	rotateRadians = angle;
	auto rotateDegrees = CC_RADIANS_TO_DEGREES(-1 * rotateRadians);
	// 限定旋转范围  -90°~90°
	if (rotateDegrees >= -180 && rotateDegrees <= -90) {
		rotateDegrees = -90;
	}
	else if (rotateDegrees >= 90 && rotateDegrees <= 180) {
		rotateDegrees = 90;
	}
	auto speed = 0.5 / M_PI;
	auto rotateDuration = fabs(rotateRadians * speed);
	playerarrowBg->runAction(Sequence::create(RotateTo::create(rotateDuration, rotateDegrees),
		NULL));
	playerarrow->runAction(Sequence::create(RotateTo::create(rotateDuration, rotateDegrees),
		NULL));
}

// * ------------------------------------------ 发射子弹 -------------------------------------- *
void Hero::shootArrow()
{
	if (d == 1) {
		auto arrow = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("arrow1.png"));
		arrow->setRotation(playerarrow->getRotation());
		arrow->setAnchorPoint(Vec2(0, 0));
		this->getParent()->addChild(arrow, 1);
		arrow->setPosition(this->convertToWorldSpace(playerarrow->getPosition()));
		auto action = ArrowPathBezier::create(2, bezier);
		arrow->runAction(action);
		bullets.pushBack(arrow);
	}
	else if (d == 2) {
		auto arrow = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("arrow2.png"));
		arrow->setRotation(playerarrow->getRotation());
		arrow->setAnchorPoint(Vec2(1, 0.5));
		this->getParent()->addChild(arrow, 1);
		arrow->setPosition(this->convertToWorldSpace(playerarrow->getPosition()));
		auto action = ArrowPathBezier::create(2, bezier);
		arrow->runAction(action);
		bullets.pushBack(arrow);
	}


}

// * ------------------------------------------ 重载Attack -------------------------------------- *
void Hero::runAttackAction()
{
	if (changeState(ACTION_STATE_ATTACK))
	{
		// 检测路径贝赛尔的控制点和终点
		auto winSize = Director::getInstance()->getWinSize();

		if (d == 1) {
			auto vector = Point(winSize.width / 10, (winSize.width / 10)*tan(rotateRadians)) * power;
			auto x = vector.x;
			auto y = vector.y;
			Point endPoint = Vec2(4 * x, -this->convertToWorldSpace(Vec2(4 * x, y > 0 ? 0 : std::abs(y * 10))).y);
			Point q = Point(2 * x, y * 2);
			bezier.controlPoint = q;
			bezier.endPosition = endPoint;
		}
		else if (d == 2)
		{
			auto vector = Point(winSize.width / 10, (winSize.width / 10)*tan(-rotateRadians)) * power;
			auto x = vector.x;
			auto y = vector.y;
			Point endPoint = Vec2(-4 * x, -this->convertToWorldSpace(Vec2(-4 * x, y > 0 ? 0 : std::abs(y * 10))).y);
			Point q = Point(-2 * x, y * 2);
			bezier.controlPoint = q;
			bezier.endPosition = endPoint;
		}

		isRunAttackAction = true;
		auto funcall1 = CallFunc::create(CC_CALLBACK_0(Hero::shootArrow, this));
		auto funcall2 = CallFunc::create(CC_CALLBACK_0(Hero::finishRunAction, this));
		auto delayTime = DelayTime::create(0.5f);
		this->runAction(getAttackAction());
		this->runAction(Sequence::create(funcall1, delayTime, funcall2, NULL));
	}
}
void Hero::finishRunAction()
{
	isRunAttackAction = false;
}