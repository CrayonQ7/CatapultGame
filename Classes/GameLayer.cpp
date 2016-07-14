#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "GameOverScene.h"
USING_NS_CC;
using namespace CocosDenshion;
GameLayer::GameLayer() : tmx(NULL)
{
}


GameLayer::~GameLayer()
{
}

GameLayer * GameLayer::create(int pl1, int pr1, int pl2, int pr2, int bg)
{
	GameLayer* pRet = new(std::nothrow) GameLayer();
	if (pRet && pRet->init(pl1, pr1, pl2, pr2, bg))
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


bool GameLayer::init(int pl1, int pr1, int pl2, int pr2, int bg)
{
	if (!Layer::init()) return false;
	this->visibleSize = Director::getInstance()->getVisibleSize();
	this->origin = Director::getInstance()->getVisibleOrigin();
	this->screenWidth = visibleSize.width;
	this->screenHeight = visibleSize.height;
	isCreated1 = false;
	isCreated2 = false;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/GameLayer.plist");
	// 左边的英雄
	hero1 = Hero::create(pl1, pr1, Vec2(origin + Point(100, 100)), 1);
	hero1->setFlippedX(false);
	//hero1->setPosition(origin + Point(100, 100));
	hero1->runIdleAction();
	hero1->setZOrder(screenHeight - hero1->getPositionY());
	addChild(hero1);
	hero1->createHpBar(pl1);
	// 右边的英雄
	hero2 = Hero::create(pl2, pr2, Vec2(origin.x + visibleSize.width - 100, origin.y + 100), 2);
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
		tmx = TMXTiledMap::create("tmxMap/map1.tmx");
		break;
	case 2:
		tmx = TMXTiledMap::create("tmxMap/map2.tmx");
		break;
	case 3:
		tmx = TMXTiledMap::create("tmxMap/map3.tmx");
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
	hero1->pUseProp = CC_CALLBACK_0(GameLayer::onHero1UseProp, this);

	hero2->pAttack = CC_CALLBACK_0(GameLayer::onHero2Attack, this);
	hero2->pStop = CC_CALLBACK_0(GameLayer::onHero2Stop, this);
	hero2->pWalk = CC_CALLBACK_1(GameLayer::onHero2Walk, this);
	hero2->pUseProp = CC_CALLBACK_0(GameLayer::onHero2UseProp, this);

	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("music/BGM_1.mp3", true);
	audio->preloadEffect("music/Fire1.wav");
	audio->preloadEffect("music/Fire2.wav");
	audio->preloadEffect("music/Fire3.wav");
	audio->preloadEffect("music/Explode.wav");

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

void GameLayer::onHero1UseProp()
{
	isCreated1 = false;
	//auto funcall1 = CallFunc::create(CC_CALLBACK_0(GameLayer::prop1CallFunc, this, 2));
	//auto funcall2 = CallFunc::create(CC_CALLBACK_0(GameLayer::prop2CallFunc, this, 2));
	auto funcall = CallFunc::create(CC_CALLBACK_0(GameLayer::isCreatedP1, this));
	//auto delayTime = DelayTime::create(0.5f);
	switch (hero1->pr)
	{
	case 1:
		prop1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop_1.png"));

		//prop1->runAction(Sequence::create(MoveTo::create(0.5, hero2->getPosition()), funcall1, NULL));
		break;
	case 2:
		prop1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop_2.png"));

		//prop1->runAction(Sequence::create(MoveTo::create(0.5, hero2->getPosition()), funcall2, NULL));
		break;
	case 3:
		prop1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop_3.png"));

		//prop1->runAction(Sequence::create(MoveTo::create(0.5, hero2->getPosition()), funcall3, NULL));
		break;
	default:
		break;
	}
	prop1->setPosition(hero2->getPosition().x, origin.y + visibleSize.height - prop1->getContentSize().height / 2);
	addChild(prop1, hero2->getZOrder() + 1);
	prop1->runAction(Sequence::create(MoveTo::create(0.5, hero2->getPosition()), funcall, NULL));
	schedule(schedule_selector(GameLayer::uodateOnce1), 1.0, 2, 0);
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

void GameLayer::onHero2UseProp()
{
	//auto funcall1 = CallFunc::create(CC_CALLBACK_0(GameLayer::prop1CallFunc, this, 1));
	//auto funcall2 = CallFunc::create(CC_CALLBACK_0(GameLayer::prop2CallFunc, this, 1));
	auto funcall = CallFunc::create(CC_CALLBACK_0(GameLayer::isCreatedP2, this));
	//auto delayTime = DelayTime::create(0.5f);
	switch (hero2->pr)
	{
	case 1:
		prop2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop_1.png"));

		/*prop2->runAction(Sequence::create(MoveTo::create(0.5, hero1->getPosition()), funcall1, NULL));*/
		break;
	case 2:
		prop2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop_2.png"));

		/*prop2->runAction(Sequence::create(MoveTo::create(0.5, hero1->getPosition()), funcall2, NULL));*/
		break;
	case 3:
		prop2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop_3.png"));

		/*prop2->runAction(Sequence::create(MoveTo::create(0.5, hero1->getPosition()), funcall3, NULL));*/
		break;
	default:
		break;
	}
	prop2->setPosition(hero1->getPosition().x, origin.y + visibleSize.height - prop2->getContentSize().height / 2);
	addChild(prop2, hero1->getZOrder() + 1);
	prop2->runAction(Sequence::create(MoveTo::create(0.5, hero1->getPosition()), funcall, NULL));
	schedule(schedule_selector(GameLayer::uodateOnce2), 1.0, 2, 0);
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
				SimpleAudioEngine::getInstance()->playEffect("music/Explode.wav", false, 1.0f, 1.0f, 1.0f);
				auto ex = ParticleSystemQuad::create("plist/explode.plist");
				ex->setPosition((*it)->getPosition());
				ex->setAutoRemoveOnFinish(true);
				ex->setDuration(0.1);
				ex->setScale(0.3f);
				addChild(ex, 5);
				hero2->setHP(hero2->getHP() - hero1->getATK());
				if (hero2->getHP() < 0) {
					hero2->setHP(0);
					RenderTexture* renderTexture = RenderTexture::create(origin.x + visibleSize.width, origin.y + visibleSize.height);
					renderTexture->begin();
					this->getParent()->visit();
					renderTexture->end();
					Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
					SimpleAudioEngine::getInstance()->stopBackgroundMusic();
					unschedule(schedule_selector(GameLayer::update));
					Director::getInstance()->pushScene(GameOverScene::scene(renderTexture, hero1->pl, 1));
				}// 其实是gameover
				

				//ProgressTo *progressTo = ProgressTo::create(1, hero2->getHP());
				//hero2->hpBar->runAction(RepeatForever::create(progressTo));
				hero2->hpBar->setPercentage(hero2->getHP());
				it = hero1->bullets.erase(it);
				break;
			}
			else if (this->convertToWorldSpace((*it)->getPosition()).x > (visibleSize.width + origin.x)
				|| this->convertToWorldSpace((*it)->getPosition()).y > (visibleSize.height + origin.y)
				|| this->convertToWorldSpace((*it)->getPosition()).y < origin.y+(*it)->getContentSize().height + tileHeight)
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
				SimpleAudioEngine::getInstance()->playEffect("music/Explode.wav", false, 1.0f, 1.0f, 1.0f);
				auto ex = ParticleSystemQuad::create("plist/explode.plist");
				ex->setPosition((*itr)->getPosition());
				ex->setAutoRemoveOnFinish(true);
				ex->setDuration(0.1);
				ex->setScale(0.3f);
				addChild(ex, 5);
				// HP--;
				hero1->setHP(hero1->getHP() - hero2->getATK());
				if (hero1->getHP() < 0) {
					hero1->setHP(0);
					RenderTexture* renderTexture = RenderTexture::create(origin.x + visibleSize.width, origin.y + visibleSize.height);
					renderTexture->begin();
					this->getParent()->visit();
					renderTexture->end();
					Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
					SimpleAudioEngine::getInstance()->stopBackgroundMusic();
					unschedule(schedule_selector(GameLayer::update));
					Director::getInstance()->pushScene(GameOverScene::scene(renderTexture, hero2->pl, 2));
				}// 其实是gameover
				//ProgressTo *progressTo = ProgressTo::create(1, hero1->getHP());
				//hero1->hpBar->runAction(RepeatForever::create(progressTo));
				hero1->hpBar->setPercentage(hero1->getHP());
				itr = hero2->bullets.erase(itr);
				break;
			}
			else if (this->convertToWorldSpace((*itr)->getPosition()).x < origin.x
				|| this->convertToWorldSpace((*itr)->getPosition()).y >(visibleSize.height + origin.y)
				|| this->convertToWorldSpace((*itr)->getPosition()).y < origin.y + (*itr)->getContentSize().height+tileHeight)
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
	if (isCreated1 && prop1 != NULL) prop1->setPosition(hero2->getPosition());

	if (isCreated2 && prop2 != NULL) prop2->setPosition(hero1->getPosition());
}

void GameLayer::updateHero(float dt)
{
	
	onMove(hero1);
	onMove(hero2);
}

void GameLayer::uodateOnce1(float dt)
{
	switch (hero1->pr)
	{
	case 1:  // 禁锢
		break;
	case 2:  // 护盾
		break;
	case 3:  // 灼烧
		hero2->setHP(hero2->getHP() - 5);
		if (hero2->getHP() < 0) {
			hero2->setHP(0);
			// 跳转到获胜界面
		}
		hero2->hpBar->setPercentage(hero2->getHP());
		break;
	default:
		break;
	}
}

void GameLayer::uodateOnce2(float dt)
{
	switch (hero2->pr)
	{
	case 1:  // 禁锢
		break;
	case 2:  // 护盾
		break;
	case 3:  // 灼烧
		hero1->setHP(hero1->getHP() - 5);
		if (hero1->getHP() < 0) {
			hero1->setHP(0);
			// 跳转到获胜界面
		}
		hero1->hpBar->setPercentage(hero1->getHP());
		break;
	default:
		break;
	}
}

void GameLayer::onMove(Hero * hero)
{
	if (hero->getCurrActionState() == ACTION_STATE_WALK)
	{
		auto halfHeroFrameHeight = (hero->getDisplayFrame()->getRect().size.height) / 2;  // 半个英雄高度
		auto expectP = hero->getPosition() + hero->getVelocity();  // 预测下一个移动到的位置
		auto actualP = expectP;  // 实际将要移动到的位置
								 // 确保不会移出地图或在墙上，其中tilemap只有15格是可以走人的
		if (expectP.y < halfHeroFrameHeight || expectP.y >(tileHeight * 12 + halfHeroFrameHeight))
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

void GameLayer::isCreatedP1()
{
	isCreated1 = true;
}

void GameLayer::isCreatedP2()
{
	isCreated2 = true;
}


//// 英雄被禁锢
//void GameLayer::prop1CallFunc(int d)
//{
//
//	if (d == 1) return;
//	else if (d == 2)  return;
//}
//
//// 英雄获得一层护盾
//void GameLayer::prop2CallFunc(int d)
//{
//	if (d == 1) hero1->hpBar->setPercentage(0);
//	else if (d == 2)  hero2->hpBar->setPercentage(0);
//}
//
//// 英雄被持续灼烧
//void GameLayer::prop3CallFunc(int d)
//{
//	if (d == 1) {
//		hero1->setHP(hero1->getHP() - 5);
//		hero1->hpBar->setPercentage();
//	}
//	else if (d == 2)  hero2->hpBar->setPercentage(0);
//}

