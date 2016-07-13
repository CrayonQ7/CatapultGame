#include "GameLayer.h"

USING_NS_CC;

GameLayer::GameLayer() : tmx(NULL)
{
}


GameLayer::~GameLayer()
{
}

GameLayer * GameLayer::create(int pl1, int pl2, int bg)
{
	GameLayer* pRet = new(std::nothrow) GameLayer();
	if (pRet && pRet->init(pl1, pl2, bg))
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


bool GameLayer::init(int pl1, int pl2, int bg)
{
	if (!Layer::init()) return false;
	this->visibleSize = Director::getInstance()->getVisibleSize();
	this->origin = Director::getInstance()->getVisibleOrigin();
	this->screenWidth = visibleSize.width;
	this->screenHeight = visibleSize.height;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/GameLayer.plist");
	// 左边的英雄
	hero1 = Hero::create(pl1, Vec2(origin + Point(100, 100)), 1);
	hero1->setFlippedX(false);
	//hero1->setPosition(origin + Point(100, 100));
	hero1->runIdleAction();
	hero1->setZOrder(screenHeight - hero1->getPositionY());
	addChild(hero1);
	hero1->createHpBar(pl1);
	// 右边的英雄
	hero2 = Hero::create(pl2, Vec2(origin.x + visibleSize.width - 100, origin.y + 100), 2);
	//hero2->playerarrow->setRotation(-M_PI/2);
	//hero2->setPosition(origin.x + visibleSize.width - 100, origin.y + 100);
	hero2->runIdleAction();
	hero2->setZOrder(screenHeight - hero2->getPositionY());
	addChild(hero2);
	hero2->createHpBar(pl2);
	// * ---------------------------------背景图片---------------------------- *
	switch (bg)
	{
	case 1:
		tmx = TMXTiledMap::create("map1.tmx");
		break;
	case 2:
		tmx = TMXTiledMap::create("map.tmx");
		break;
	case 3:
		tmx = TMXTiledMap::create("map3.tmx");
	default:
		break;
	}
	//tmx = TMXTiledMap::create("map.tmx");
	this->addChild(tmx, -1);
	tileHeight = tmx->getTileSize().height;
	tileWidth = tmx->getTileSize().width;

	hero1->pAttack = CC_CALLBACK_0(GameLayer::onHero1Attack, this);
	hero1->pStop = CC_CALLBACK_0(GameLayer::onHero1Stop, this);
	hero1->pWalk = CC_CALLBACK_1(GameLayer::onHero1Walk, this);

	hero2->pAttack = CC_CALLBACK_0(GameLayer::onHero2Attack, this);
	hero2->pStop = CC_CALLBACK_0(GameLayer::onHero2Stop, this);
	hero2->pWalk = CC_CALLBACK_1(GameLayer::onHero2Walk, this);

	this->scheduleUpdate();
	return true;
}

void GameLayer::onHero1Walk(cocos2d::Point direction)
{
	if (direction != Point(0, 0))
	{
		if (direction.x != 0)
		    hero1->setFlippedX(direction.x < 0 ? false : true);  // 如果英雄要向左，就翻转一下
		hero1->runWalkAction();
	}
	hero1->setVelocity(direction);
}

void GameLayer::onHero1Attack()
{
	hero1->runAttackAction();
}

void GameLayer::onHero1Stop()
{
	hero1->runIdleAction();
}

void GameLayer::onHero2Walk(cocos2d::Point direction)
{
	if (direction != Point(0, 0))
	{
		if (direction.x != 0)
		    hero2->setFlippedX(direction.x < 0 ? false : true);  // 如果英雄要向右，就翻转一下
		hero2->runWalkAction();
	}

	hero2->setVelocity(direction);
}

void GameLayer::onHero2Attack()
{
	hero2->runAttackAction();
}

void GameLayer::onHero2Stop()
{
	hero2->runIdleAction();
}

void GameLayer::update(float dt)
{
	this->updateHero(dt);
	if (!hero1->bullets.empty())
	{
		for (Vector<Sprite*>::iterator it = hero1->bullets.begin(); it != hero1->bullets.end();)
		{
			if (hero2->getPosition().getDistance((*it)->getPosition()) < 30)
			{
				(*it)->removeFromParentAndCleanup(true);
				hero2->runHurtAction();
				hero2->setHP(hero2->getHP() - hero1->getATK());
				if (hero2->getHP() < 0) {
					hero2->setHP(0);
				}// 其实是gameover
				//ProgressTo *progressTo = ProgressTo::create(1, hero2->getHP());
				//hero2->hpBar->runAction(RepeatForever::create(progressTo));
				hero2->hpBar->setPercentage(hero2->getHP());
				it = hero1->bullets.erase(it);
				break;
			}
			else if (this->convertToWorldSpace((*it)->getPosition()).x > (visibleSize.width + origin.x)
				|| this->convertToWorldSpace((*it)->getPosition()).y > (visibleSize.height + origin.y)
				|| this->convertToWorldSpace((*it)->getPosition()).y < origin.y+(*it)->getContentSize().height/2 + tileHeight)
			{
				(*it)->removeFromParentAndCleanup(true);
				it = hero1->bullets.erase(it);
				break;
			}
			else {
				it++;
			}
		}
	}
	if (!hero2->bullets.empty())
	{
		for (Vector<Sprite*>::iterator itr = hero2->bullets.begin(); itr != hero2->bullets.end();)
		{
			if (hero1->getPosition().getDistance((*itr)->getPosition()) < 30)
			{
				(*itr)->removeFromParentAndCleanup(true);
				hero1->runHurtAction();
				// HP--;
				hero1->setHP(hero1->getHP() - hero2->getATK());
				if (hero1->getHP() < 0) hero1->setHP(0); // 其实是gameover
				//ProgressTo *progressTo = ProgressTo::create(1, hero1->getHP());
				//hero1->hpBar->runAction(RepeatForever::create(progressTo));
				hero1->hpBar->setPercentage(hero1->getHP());
				itr = hero2->bullets.erase(itr);
				break;
			}
			else if (this->convertToWorldSpace((*itr)->getPosition()).x < origin.x
				|| this->convertToWorldSpace((*itr)->getPosition()).y >(visibleSize.height + origin.y)
				|| this->convertToWorldSpace((*itr)->getPosition()).y < origin.y + (*itr)->getContentSize().height / 2+tileHeight)
			{
				(*itr)->removeFromParentAndCleanup(true);
				itr = hero2->bullets.erase(itr);
				break;
			}
			else {
				itr++;
			}
		}
	}
}

void GameLayer::updateHero(float dt)
{
	
	onMove(hero1);
	onMove(hero2);
}

void GameLayer::onMove(Hero * hero)
{
	if (hero->getCurrActionState() == ACTION_STATE_WALK)
	{
		auto halfHeroFrameHeight = (hero->getDisplayFrame()->getRect().size.height) / 2;  // 半个英雄高度
		auto expectP = hero->getPosition() + hero->getVelocity();  // 预测下一个移动到的位置
		auto actualP = expectP;  // 实际将要移动到的位置
								 // 确保不会移出地图或在墙上，其中tilemap只有3格是可以走人的
		if (expectP.y < halfHeroFrameHeight || expectP.y >(tileHeight * 6 + halfHeroFrameHeight))
		{
			actualP.y = hero->getPositionY();
		}
		float mapWidth = tmx->getContentSize().width;  // 整张地图宽度，地图可能是比屏幕宽的
		float halfWinWidth = screenWidth / 2;  // 屏幕一半宽
		float halfHeroFrameWidth = (hero->getDisplayFrame()->getRect().size.width) / 2;  // 半个英雄宽度
		if (expectP.x > halfWinWidth && expectP.x <= (mapWidth - halfWinWidth))  // 
		{
			this->setPositionX(this->getPositionX() - hero->getVelocity().x);
		}
		else if (expectP.x < halfHeroFrameWidth || expectP.x >= mapWidth - halfHeroFrameWidth)
		{
			actualP.x = hero->getPositionX();
		}
		hero->setPosition(actualP);
		hero->setZOrder(screenHeight - hero->getPositionY());
	}
}

