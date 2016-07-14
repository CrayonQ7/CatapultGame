#include "Hero.h"
USING_NS_CC;
Hero::Hero()
{
	hpBar = NULL;
	playerarrow = NULL;
	power = 1;
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
	switch (pl)
	{
	case 1:
		/*CC_BREAK_IF(!this->initWithSpriteFrameName("Gate_1_Idle_0.png"));*/
		CC_BREAK_IF(!this->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_1_Idle_0.png")));
		ret = true;
		loadGate_1();
		break;
	case 2:
		//CC_BREAK_IF(!this->initWithSpriteFrameName("Gate_2_Idle_0.png"));
		CC_BREAK_IF(!this->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_2_Idle_0.png")));
		ret = true;
		loadGate_2();
		break;
	case 3:
		//CC_BREAK_IF(!this->initWithSpriteFrameName("Gate_3_Idle_0.png"));
		CC_BREAK_IF(!this->initWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_3_Idle_0.png")));
		ret = true;
		loadGate_3();
		break;
	}
	return ret;
}

// * ------------------------------------------ 调整炮口角度 -------------------------------------- *
    // π/6  ~  π/3 
void Hero::rotateArrow(float angle)
{
	//auto playerPos = this->getPosition();
	//auto pos = playerPos + playerarrow->getPosition();

	//Point vector = touchPoint - pos;
	
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
	//Sprite* arrow = Sprite::createWithSpriteFrameName("arrow1.png");
	if (d == 1) {
		//auto arrow = Sprite::create("arrow1.png");
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
		/*auto arrow = Sprite::create("arrow2.png");*/
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

void Hero::loadGate_1()
{
	hp = 100;
	atk = 5;
	auto playerSize = Size(this->getContentSize().width / 2, this->getContentSize().height / 3 * 2);
	this->setAnchorPoint(Vec2(0.7f, 0.4f));
	this->setPosition(Vec2(playerPos.x /*+ GameManager::getInstance()->objectPosOffX*/, playerPos.y + playerSize.height * 0.4f));

	auto idleAnimation = this->createAnimation("Gate_1_Idle_%d.png", 2, 4);  // 空闲动画只有两帧  每秒4帧
	this->setIdleAction(RepeatForever::create(Animate::create(idleAnimation)));

	auto walkAnimation = this->createAnimation("Gate_1_Walk_%d.png", 3, 6);  // 行走动画只有7帧  每秒14帧
	this->setWalkAction(RepeatForever::create(Animate::create(walkAnimation)));

	auto attackAnimation = this->createAnimation("Gate_1_Attack_%d.png", 2, 4);  // 攻击动画只有7帧  每秒14帧
	this->setAttackAction(Sequence::create(Animate::create(attackAnimation), BaseSprite::createIdleCallbackFunc(), NULL));  // 攻击之后立马变为空闲状态

	auto hurtAnimation = this->createAnimation("Gate_1_Hurt_%d.png", 2, 4);  // 受伤动画只有两帧  每秒4帧
	this->setHurtAction(Sequence::create(Animate::create(hurtAnimation), BaseSprite::createIdleCallbackFunc(), NULL));  // 受伤之后立马变为空闲状态

	auto deadAnimation = this->createAnimation("Gate_1_Dead_%d.png", 2, 4);  // 死亡动画只有两帧  每秒4帧
	this->setDeadAction(Sequence::create(Animate::create(deadAnimation), Blink::create(3, 9), NULL));  // 死亡之后立马闪烁




	if (d == 1) {
		/*playerarrowBg = Sprite::create("paoBg1.png");*/
		playerarrowBg = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("paoBg1.png"));
		playerarrowBg->setPosition(Vec2(playerarrowBg->getContentSize().width, playerarrowBg->getContentSize().height));
		playerarrowBg->setAnchorPoint(Vec2(0.125f, 0.45f));
		this->addChild(playerarrowBg, 2);
		/*auto playerarrowSp = Sprite::create("pao.png");*/
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
	else if (d == 2)
	{
		/*playerarrowBg = Sprite::create("paoBg2.png");*/
		playerarrowBg = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("paoBg2.png"));
		playerarrowBg->setPosition(Vec2(-playerarrowBg->getContentSize().width / 4, playerarrowBg->getContentSize().height));
		playerarrowBg->setAnchorPoint(Vec2(0.875f, 0.45f));
		this->addChild(playerarrowBg, 2);

		/*auto playerarrowSp = Sprite::create("pao2.png");*/
		auto playerarrowSp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("pao2.png"));
		playerarrow = ProgressTimer::create(playerarrowSp);
		playerarrow->setAnchorPoint(Vec2(0.875f, 0.45f));
		playerarrow->setType(ProgressTimer::Type::BAR);
		playerarrow->setMidpoint(Vec2(1, 0.5f));
		playerarrow->setBarChangeRate(Vec2(1, 0));
		playerarrow->setPercentage(0);

		playerarrow->setPosition(Vec2(-playerarrowBg->getContentSize().width / 4, playerarrowBg->getContentSize().height));
		this->addChild(playerarrow, 3);
		//playerarrowBg->setVisible(false);
	}
	
}

void Hero::loadGate_2()
{
	hp = 100;
	atk = 7;
	auto playerSize = Size(this->getContentSize().width / 2, this->getContentSize().height / 3 * 2);
	this->setAnchorPoint(Vec2(0.7f, 0.4f));
	this->setPosition(Vec2(playerPos.x /*+ GameManager::getInstance()->objectPosOffX*/, playerPos.y + playerSize.height * 0.4f));

	auto idleAnimation = this->createAnimation("Gate_2_Idle_%d.png", 2, 4);  // 空闲动画只有两帧  每秒4帧
	this->setIdleAction(RepeatForever::create(Animate::create(idleAnimation)));

	auto walkAnimation = this->createAnimation("Gate_2_Walk_%d.png", 3, 6);  // 行走动画只有7帧  每秒14帧
	this->setWalkAction(RepeatForever::create(Animate::create(walkAnimation)));

	auto attackAnimation = this->createAnimation("Gate_2_Attack_%d.png", 2, 4);  // 攻击动画只有7帧  每秒14帧
	this->setAttackAction(Sequence::create(Animate::create(attackAnimation), BaseSprite::createIdleCallbackFunc(), NULL));  // 攻击之后立马变为空闲状态

	auto hurtAnimation = this->createAnimation("Gate_2_Hurt_%d.png", 2, 4);  // 受伤动画只有两帧  每秒4帧
	this->setHurtAction(Sequence::create(Animate::create(hurtAnimation), BaseSprite::createIdleCallbackFunc(), NULL));  // 受伤之后立马变为空闲状态

	auto deadAnimation = this->createAnimation("Gate_2_Dead_%d.png", 2, 4);  // 死亡动画只有两帧  每秒4帧
	this->setDeadAction(Sequence::create(Animate::create(deadAnimation), Blink::create(3, 9), NULL));  // 死亡之后立马闪烁

	//playerarrow = Sprite::create("pao.png");
	//playerarrow->setPosition(Vec2(playerarrow->getContentSize().width, playerarrow->getContentSize().height));
	//playerarrow->setAnchorPoint(Vec2(0.125f, 0.45f));
	//this->addChild(playerarrow, 2);

	if (d == 1) {
		/*playerarrowBg = Sprite::create("paoBg.png");*/
		playerarrowBg = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("paoBg1.png"));
		playerarrowBg->setPosition(Vec2(playerarrowBg->getContentSize().width, playerarrowBg->getContentSize().height));
		playerarrowBg->setAnchorPoint(Vec2(0.125f, 0.45f));
		this->addChild(playerarrowBg, 2);
		/*auto playerarrowSp = Sprite::create("pao.png");*/
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
	else if (d == 2)
	{
		/*playerarrowBg = Sprite::create("paoBg2.png");*/
		playerarrowBg = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("paoBg2.png"));
		playerarrowBg->setPosition(Vec2(-playerarrowBg->getContentSize().width / 4, playerarrowBg->getContentSize().height));
		playerarrowBg->setAnchorPoint(Vec2(0.875f, 0.45f));
		this->addChild(playerarrowBg, 2);

		/*auto playerarrowSp = Sprite::create("pao2.png");*/
		auto playerarrowSp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("pao2.png"));
		playerarrow = ProgressTimer::create(playerarrowSp);
		playerarrow->setAnchorPoint(Vec2(0.875f, 0.45f));
		playerarrow->setType(ProgressTimer::Type::BAR);
		playerarrow->setMidpoint(Vec2(1, 0.5f));
		playerarrow->setBarChangeRate(Vec2(1, 0));
		playerarrow->setPercentage(0);

		playerarrow->setPosition(Vec2(-playerarrowBg->getContentSize().width / 4, playerarrowBg->getContentSize().height));
		this->addChild(playerarrow, 3);
		//playerarrowBg->setVisible(false);
	}
}

void Hero::loadGate_3()
{

	hp = 100;
	atk = 10;
	auto playerSize = Size(this->getContentSize().width / 2, this->getContentSize().height / 3 * 2);
	this->setAnchorPoint(Vec2(0.7f, 0.4f));
	this->setPosition(Vec2(playerPos.x /*+ GameManager::getInstance()->objectPosOffX*/, playerPos.y + playerSize.height * 0.4f));

	auto idleAnimation = this->createAnimation("Gate_3_Idle_%d.png", 2, 4);  // 空闲动画只有两帧  每秒4帧
	this->setIdleAction(RepeatForever::create(Animate::create(idleAnimation)));

	auto walkAnimation = this->createAnimation("Gate_3_Walk_%d.png", 3, 6);  // 行走动画只有7帧  每秒14帧
	this->setWalkAction(RepeatForever::create(Animate::create(walkAnimation)));

	auto attackAnimation = this->createAnimation("Gate_3_Attack_%d.png", 2, 4);  // 攻击动画只有7帧  每秒14帧
	this->setAttackAction(Sequence::create(Animate::create(attackAnimation), BaseSprite::createIdleCallbackFunc(), NULL));  // 攻击之后立马变为空闲状态

	auto hurtAnimation = this->createAnimation("Gate_3_Hurt_%d.png", 2, 4);  // 受伤动画只有两帧  每秒4帧
	this->setHurtAction(Sequence::create(Animate::create(hurtAnimation), BaseSprite::createIdleCallbackFunc(), NULL));  // 受伤之后立马变为空闲状态

	auto deadAnimation = this->createAnimation("Gate_3_Dead_%d.png", 2, 4);  // 死亡动画只有两帧  每秒4帧
	this->setDeadAction(Sequence::create(Animate::create(deadAnimation), Blink::create(3, 9), NULL));  // 死亡之后立马闪烁



	if (d == 1) {
		/*playerarrowBg = Sprite::create("paoBg.png");*/
		playerarrowBg = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("paoBg1.png"));
		playerarrowBg->setPosition(Vec2(playerarrowBg->getContentSize().width, playerarrowBg->getContentSize().height));
		playerarrowBg->setAnchorPoint(Vec2(0.125f, 0.45f));
		this->addChild(playerarrowBg, 2);
		/*auto playerarrowSp = Sprite::create("pao.png");*/
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
	else if (d == 2)
	{
		/*playerarrowBg = Sprite::create("paoBg2.png");*/
		playerarrowBg = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("paoBg2.png"));
		playerarrowBg->setPosition(Vec2(-playerarrowBg->getContentSize().width / 4, playerarrowBg->getContentSize().height));
		playerarrowBg->setAnchorPoint(Vec2(0.875f, 0.45f));
		this->addChild(playerarrowBg, 2);

		/*auto playerarrowSp = Sprite::create("pao2.png");*/
		auto playerarrowSp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("pao2.png"));
		playerarrow = ProgressTimer::create(playerarrowSp);
		playerarrow->setAnchorPoint(Vec2(0.875f, 0.45f));
		playerarrow->setType(ProgressTimer::Type::BAR);
		playerarrow->setMidpoint(Vec2(1, 0.5f));
		playerarrow->setBarChangeRate(Vec2(1, 0));
		playerarrow->setPercentage(0);

		playerarrow->setPosition(Vec2(-playerarrowBg->getContentSize().width / 4, playerarrowBg->getContentSize().height));
		this->addChild(playerarrow, 3);
		//playerarrowBg->setVisible(false);
	}
}

// 蓄力
void Hero::setPower(float percent)
{
	if (percent > 100) percent = 100;
	if (percent > 36) power = percent / 36;
	else power = 1;
	playerarrow->setPercentage(percent);
}

void Hero::createHpBar(int p)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	switch (p)
	{
	case 1:
		hpBgSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_1_hpBg.png"));
		this->getParent()->addChild(hpBgSprite, 3);
		hpBar = ProgressTimer::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_1_hp.png")));
		hpBar->setType(ProgressTimer::Type::BAR);
		hpBar->setMidpoint(Vec2(0, 0.5f));
		hpBar->setBarChangeRate(Vec2(1, 0));
		hpBar->setPercentage(100);
		this->getParent()->addChild(hpBar, 3);
		if (d == 1)
		{
			hpBgSprite->setPosition(origin.x + hpBgSprite->getContentSize().width / 2, origin.y + visibleSize.height - hpBgSprite->getContentSize().height / 2);
			hpBar->setPosition(origin.x + hpBar->getContentSize().width / 2, origin.y + visibleSize.height - hpBar->getContentSize().height / 2);
		}
		else if (d == 2)
		{
			hpBgSprite->setPosition(origin.x + visibleSize.width - hpBgSprite->getContentSize().width / 2, origin.y + visibleSize.height - hpBgSprite->getContentSize().height / 2);
			hpBar->setPosition(origin.x + visibleSize.width - hpBar->getContentSize().width / 2, origin.y + visibleSize.height - hpBar->getContentSize().height / 2);
		}
		break;
	case 2:
		hpBgSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_2_hpBg.png"));
		this->getParent()->addChild(hpBgSprite, 3);
		hpBar = ProgressTimer::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_2_hp.png")));
		hpBar->setType(ProgressTimer::Type::BAR);
		hpBar->setMidpoint(Vec2(0, 0.5f));
		hpBar->setBarChangeRate(Vec2(1, 0));
		hpBar->setPercentage(100);
		this->getParent()->addChild(hpBar, 3);
		if (d == 1)
		{
			hpBgSprite->setPosition(origin.x + hpBgSprite->getContentSize().width / 2, origin.y + visibleSize.height - hpBgSprite->getContentSize().height / 2);
			hpBar->setPosition(origin.x + hpBar->getContentSize().width / 2, origin.y + visibleSize.height - hpBar->getContentSize().height / 2);
		}
		else if (d == 2)
		{
			hpBgSprite->setPosition(origin.x + visibleSize.width - hpBgSprite->getContentSize().width / 2, origin.y + visibleSize.height - hpBgSprite->getContentSize().height / 2);
			hpBar->setPosition(origin.x + visibleSize.width - hpBar->getContentSize().width / 2, origin.y + visibleSize.height - hpBar->getContentSize().height / 2);
		}
		break;
	case 3:
		hpBgSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_3_hpBg.png"));
		this->getParent()->addChild(hpBgSprite, 3);
		hpBar = ProgressTimer::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_3_hp.png")));
		hpBar->setType(ProgressTimer::Type::BAR);
		hpBar->setMidpoint(Vec2(0, 0.5f));
		hpBar->setBarChangeRate(Vec2(1, 0));
		hpBar->setPercentage(100);
		this->getParent()->addChild(hpBar, 3);
		if (d == 1)
		{
			hpBgSprite->setPosition(origin.x + hpBgSprite->getContentSize().width / 2, origin.y + visibleSize.height - hpBgSprite->getContentSize().height / 2);
			hpBar->setPosition(origin.x + hpBar->getContentSize().width / 2, origin.y + visibleSize.height - hpBar->getContentSize().height / 2);
		}
		else if (d == 2)
		{
			hpBgSprite->setPosition(origin.x + visibleSize.width - hpBgSprite->getContentSize().width / 2, origin.y + visibleSize.height - hpBgSprite->getContentSize().height / 2);
			hpBar->setPosition(origin.x + visibleSize.width - hpBar->getContentSize().width / 2, origin.y + visibleSize.height - hpBar->getContentSize().height / 2);
		}
		break;
	}
}
