#include "AMGameLayer.h"
#include "GameResult.h"
#include "SimpleAudioEngine.h"
//#include "Time.h"
USING_NS_CC;
using namespace CocosDenshion;
AMGameLayer::AMGameLayer() : tmx(NULL)
{
}

AMGameLayer::~AMGameLayer()
{
}

AMGameLayer * AMGameLayer::create(int pl, int bg, int bgm)
{
	AMGameLayer* pRet = new(std::nothrow) AMGameLayer();
	if (pRet && pRet->init(pl, bg, bgm))
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

bool AMGameLayer::init(int pl, int bg, int bgm)
{
	if (!Layer::init()) return false;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/hero.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/enemy.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/resultLayer.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/hero2.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/hero3.plist");
	this->visibleSize = Director::getInstance()->getVisibleSize();
	this->origin = Director::getInstance()->getVisibleOrigin();
	this->screenWidth = visibleSize.width;
	this->screenHeight = visibleSize.height;
	count = 0;
	amHero = AMHero::create(pl);
	amHero->setPosition(origin + Point(200, 200));
	amHero->runIdleAction();
	amHero->setZOrder(screenHeight - amHero->getPositionY());
	addChild(amHero);
	amHero->createHpBar(pl);
	amHero->pAttack = CC_CALLBACK_0(AMGameLayer::onHeroAttack, this);
	amHero->pStop = CC_CALLBACK_0(AMGameLayer::onHeroStop, this);
	amHero->pWalk = CC_CALLBACK_1(AMGameLayer::onHeroWalk, this);

	//enemies = Array::createWithCapacity(MIN_ENEMY_COUNT);
	//enemies->retain();



	for (int i = 0; i < MIN_ENEMY_COUNT; ++i)
	{
		this->addEnemy();
	}

	char c_tmx[20];
	sprintf(c_tmx, "tmxMap/amMap%d.tmx", bg);
	tmx = TMXTiledMap::create(c_tmx);
	this->addChild(tmx, -1);
	tileHeight = tmx->getTileSize().height;
	tileWidth = tmx->getTileSize().width;

	auto audio = SimpleAudioEngine::getInstance();
	audio->preloadEffect("music/attack.mp3");
	audio->preloadEffect("music/enemyAttack.mp3");
	audio->playBackgroundMusic("music/Battle.mp3", true);
	this->scheduleUpdate();


	return true;
}

// 判断攻击 盒子与身体盒子是否有交集
bool AMGameLayer::collisionDetection(const BoundingBox & hitBox, const BoundingBox & bodyBox)
{
	Rect hitRect = hitBox.actual;
	Rect bodyRect = bodyBox.actual;
	if (hitRect.intersectsRect(bodyRect))
	{
		return true;
	}
	return false;
}

void AMGameLayer::onHeroWalk(cocos2d::Point direction)
{
	if (direction != Point(0, 0))
	{
		if (direction.x != 0)
			amHero->setFlippedX(direction.x < 0 ? true : false);  // 如果英雄要向左，就翻转一下
		amHero->runWalkAction();
	}
	amHero->setVelocity(direction);
}

void AMGameLayer::onHeroAttack()
{
	amHero->runAttackAction();
	if (amHero->getCurrActionState() == ACTION_STATE_ATTACK)
	{
		if (!enemies.empty())
		{
			for (Vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end();)
			{
				if (fabsf(amHero->getPosition().y - (*it)->getPosition().y) < 20)
				{
					BoundingBox heroHitBox = amHero->getHitBox();
					BoundingBox enemyBodyBox = (*it)->getBodyBox();
					if (collisionDetection(heroHitBox, enemyBodyBox))
					{
						SimpleAudioEngine::getInstance()->playEffect("music/attack.wav", false, 1.0f, 1.0f, 1.0f);
						int damage = amHero->getATK();
						(*it)->runHurtAction();
						(*it)->setHP((*it)->getHP() - damage);
						(*it)->enemyHpBar->setPercentage((*it)->getHP() * 10 / 3);
						if ((*it)->getHP() <= 0)
						{
							(*it)->setHP(0);
							(*it)->runDeadAction();
							(*it)->removeFromParentAndCleanup(true);
							it = enemies.erase(it);
							break;
						}
						else
						{
							it++;
						}
					}
					else
					{
						it++;
					}
				}
				else
				{
					it++;
				}
			}
		}
	}
}

void AMGameLayer::onHeroStop()
{
	amHero->runIdleAction();
}

void AMGameLayer::update(float dt)
{
	this->updateHero(dt);
	this->updateEnemies(dt);
	if (enemies.empty()) {
		Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
		unschedule(schedule_selector(AMGameLayer::update));
		RenderTexture* renderTexture = RenderTexture::create(origin.x + visibleSize.width, origin.y + visibleSize.height);
		renderTexture->begin();
		this->getParent()->visit();
		renderTexture->end();
		//SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		Director::getInstance()->pushScene(GameResult::scene(renderTexture, 1));
	}
}

void AMGameLayer::updateHero(float dt)
{
	if (amHero->getCurrActionState() == ACTION_STATE_WALK)
	{
		auto halfHeroFrameHeight = (amHero->getDisplayFrame()->getRect().size.height) / 2;
		auto expectP = amHero->getPosition() + amHero->getVelocity();
		auto actualP = expectP;
		// 确保不会移出地图或在墙上
		if (expectP.y < halfHeroFrameHeight || expectP.y >(tileHeight * 12 + halfHeroFrameHeight))
		{
			actualP.y = amHero->getPositionY();
		}
		float mapWidth = tmx->getContentSize().width;
		float halfWinWidth = screenWidth / 2;
		float halfHeroFrameWidth = (amHero->getDisplayFrame()->getRect().size.width) / 2;
		if (expectP.x > halfWinWidth && expectP.x <= (mapWidth - halfWinWidth)) 
		{
			this->setPositionX(this->getPositionX() - amHero->getVelocity().x);
			amHero->hpBar->setPositionX(amHero->hpBar->getPositionX() + amHero->getVelocity().x);
			amHero->hpBgSprite->setPositionX(amHero->hpBgSprite->getPositionX() + amHero->getVelocity().x);
		}
		else if (expectP.x < halfHeroFrameWidth || expectP.x >= mapWidth - halfHeroFrameWidth)
		{
			actualP.x = amHero->getPositionX();
		}
		amHero->setPosition(actualP);
		amHero->setZOrder(screenHeight - amHero->getPositionY());
	}
}

void AMGameLayer::updateEnemies(float dt)
{
	/*Object* obj = NULL;*/
	auto distance = Point::ZERO;
	auto heroPox = amHero->getPosition();
	/*auto removedEnemies = Array::create();*/
	//CCARRAY_FOREACH(enemies, obj)
	//{
	//	auto pEnemy = (Enemy*)obj;
	//	pEnemy->execute(heroPox, amHero->getDisplayFrame()->getRect().size.width);
	//	if (pEnemy->getCurrActionState() == ACTION_STATE_WALK)
	//	{
	//		auto location = pEnemy->getPosition();
	//		auto direction = pEnemy->getMoveDirection();
	//		auto expect = location + direction;
	//		auto halfEnemyFrameHeight = (pEnemy->getDisplayFrame()->getRect().size.height) / 2;
	//		if (expect.y < halfEnemyFrameHeight || expect.y >(tileHeight * 12 + halfEnemyFrameHeight))
	//		{
	//			direction.y = 0;
	//		}
	//		pEnemy->setFlippedX(direction.x < 0 ? true : false);
	//		pEnemy->setPosition(location + direction);
	//		pEnemy->setZOrder(pEnemy->getPositionY());
	//	}
	//}
	if (!enemies.empty())
	{
		for (Vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++)
		{
			(*it)->execute(heroPox, amHero->getDisplayFrame()->getRect().size.width);
			if ((*it)->getCurrActionState() == ACTION_STATE_WALK)
			{
				auto location = (*it)->getPosition();
				auto direction = (*it)->getMoveDirection();
				auto expect = location + direction;
				auto halfEnemyFrameHeight = ((*it)->getDisplayFrame()->getRect().size.height) / 2;
				if (expect.y < halfEnemyFrameHeight || expect.y > (tileHeight * 12 + halfEnemyFrameHeight))
				{
					direction.y = 0;
				}
				(*it)->setFlippedX(direction.x < 0 ? true : false);
				(*it)->setPosition(location + direction);
				(*it)->setZOrder((*it)->getPositionY());
			}
		}
	}
}


void AMGameLayer::addEnemy()
{
	auto winSize = Director::getInstance()->getWinSize();
	auto location = Point::ZERO;
	auto enemy = Enemy::create();
	auto halfEnemyFrameHeight = (enemy->getDisplayFrame()->getRect().size.height) / 2;
	auto heroPosX = amHero->getPositionX();
	auto halfWinWidth = winSize.width / 2;

	time_t tt;
	time(&tt);
	struct tm * now;
	now = localtime(&tt);
	timeval tv;
	gettimeofday(&tv, NULL);
	unsigned long reed = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	srand(reed);

	while (fabsf(heroPosX - location.x) < 250)
	{
		if (heroPosX < halfWinWidth)
		{
			location.x = amHero->getPositionX() + CCRANDOM_0_1() * winSize.width;
		}
		else {
			location.x = amHero->getPositionX() + CCRANDOM_MINUS1_1() * winSize.width;
		}
	}
	auto maxY = tileHeight * 12 + halfEnemyFrameHeight;
	location.y = CCRANDOM_0_1() * maxY;
	if (location.y < halfEnemyFrameHeight)
	{
		location.y = halfEnemyFrameHeight;
	}
	enemy->pAttack = CC_CALLBACK_0(AMGameLayer::onEnemyAttack, this, enemy);
	enemy->setPosition(origin + location);
	enemy->setZOrder(screenHeight - enemy->getPositionY());
	enemy->runIdleAction();
	enemy->setATK(5); // 攻击力为5
	enemy->setHP(30);  // 血量为30
	enemy->setVelocity(Point(0.5f, 0.5f));  // 速度
	enemy->setEyeArea(200); // 视野范围
	enemy->setAttackArea(25); // 攻击距离
	enemies.pushBack(enemy);
	addChild(enemy);
}

void AMGameLayer::onEnemyAttack(BaseSprite * pSprite)
{
	/*Object *enemyObj = NULL;*/
	//CCARRAY_FOREACH(enemies, enemyObj)
	//{
	//	Enemy *pEnemy = (Enemy*)enemyObj;
	//	if (pEnemy->getCurrActionState() == ACTION_STATE_ATTACK)
	//	{
	//		pEnemy->setPositionY(amHero->getPositionY());
	//		BoundingBox heroBodyBox = amHero->getBodyBox();
	//		BoundingBox enemyHitBox = pEnemy->getHitBox();
	//		if (collisionDetection(enemyHitBox, heroBodyBox))
	//		{
	//			SimpleAudioEngine::getInstance()->playEffect("music/enemyAttack.mp3", false, 1.0f, 1.0f, 1.0f);
	//			int damage = pEnemy->getATK();
	//			amHero->runHurtAction();
	//			amHero->setHP(amHero->getHP() - damage);
	//			amHero->hpBar->setPercentage(amHero->getHP());
	//			if (amHero->getHP() <= 0)
	//			{
	//				amHero->runDeadAction();
	//			}
	//		}
	//	}
	//}
	if (!enemies.empty())
	{
		for (Vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++)
		{
			if ((*it)->getCurrActionState() == ACTION_STATE_ATTACK)
			{
				//(*it)->setPositionY(amHero->getPositionY());
				BoundingBox heroBodyBox = amHero->getBodyBox();
				BoundingBox enemyHitBox = (*it)->getHitBox();
				if (collisionDetection(enemyHitBox, heroBodyBox))
				{
					SimpleAudioEngine::getInstance()->playEffect("music/enemyAttack.wav", false, 1.0f, 1.0f, 1.0f);
					int damage = (*it)->getATK();
					amHero->runHurtAction();
					amHero->setHP(amHero->getHP() - damage);
					amHero->hpBar->setPercentage(amHero->getHP());
					if (amHero->getHP() <= 0)
					{
						amHero->setHP(0);
						auto funcall1 = CallFunc::create([&]()
						{
							amHero->runDeadAction();
						});
						auto delayTime = DelayTime::create(0.5f);
						auto funcall2 = CallFunc::create([&]()
						{
							Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
							unschedule(schedule_selector(AMGameLayer::update));
							RenderTexture* renderTexture = RenderTexture::create(origin.x + visibleSize.width, origin.y + visibleSize.height);
							renderTexture->begin();
							this->getParent()->visit();
							renderTexture->end();
							SimpleAudioEngine::getInstance()->stopBackgroundMusic();
							Director::getInstance()->pushScene(GameResult::scene(renderTexture, 2));
						});
						amHero->runAction(Sequence::create(funcall1, delayTime, funcall2, NULL));
						break;
					}
				}
			}
		}
	}
}
