#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "GameOverScene.h"
#include "GameRuleLayer.h"
USING_NS_CC;
using namespace CocosDenshion;
GameLayer::GameLayer() : tmx(NULL)
{
}


GameLayer::~GameLayer()
{
}

GameLayer * GameLayer::create(int pl1, int pr1, int pl2, int pr2, int bg, float bv, float ev, int bgm)
{
	GameLayer* pRet = new(std::nothrow) GameLayer();
	if (pRet && pRet->init(pl1, pr1, pl2, pr2, bg, bv, ev, bgm))
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


bool GameLayer::init(int pl1, int pr1, int pl2, int pr2, int bg, float bv, float ev, int bgm)
{
	if (!Layer::init()) return false;
	this->visibleSize = Director::getInstance()->getVisibleSize();
	this->origin = Director::getInstance()->getVisibleOrigin();
	this->screenWidth = visibleSize.width;
	this->screenHeight = visibleSize.height;
	isCreated1 = false;
	isCreated2 = false;
	hasShield1 = false;
	hasShield2 = false;
	hasSludge1 = false;
	hasSludge2 = false;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/GameLayer.plist");
	// ��ߵ�Ӣ��
	hero1 = Hero::create(pl1, pr1, Vec2(origin + Point(100, 100)), 1);
	hero1->setFlippedX(false);
	//hero1->setPosition(origin + Point(100, 100));
	hero1->runIdleAction();
	hero1->setZOrder(screenHeight - hero1->getPositionY());
	addChild(hero1);
	hero1->createHpBar(pl1);
	// �ұߵ�Ӣ��
	hero2 = Hero::create(pl2, pr2, Vec2(origin.x + visibleSize.width - 100, origin.y + 100), 2);
	//hero2->playerarrow->setRotation(-M_PI/2);
	//hero2->setPosition(origin.x + visibleSize.width - 100, origin.y + 100);
	hero2->runIdleAction();
	hero2->setZOrder(screenHeight - hero2->getPositionY());
	addChild(hero2);
	hero2->createHpBar(pl2);
	// * ---------------------------------����ͼƬ---------------------------- *
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

	backgroundVolume = bv;
	effectVolume = ev;
	curBgm = bgm;
	auto audio = SimpleAudioEngine::getInstance();
	char file[20];
	sprintf(file, "music/BGM_%d.mp3", curBgm + 1);
	audio->playBackgroundMusic(file, true);
	audio->setBackgroundMusicVolume(backgroundVolume);
	audio->preloadEffect("music/Fire1.mp3");
	audio->preloadEffect("music/Fire2.mp3");
	audio->preloadEffect("music/Fire3.mp3");
	audio->preloadEffect("music/Explode.mp3");
	audio->setEffectsVolume(effectVolume);

	auto gameRuleItem = MenuItemFont::create("Game Rule", CC_CALLBACK_1(GameLayer::gameRuleCallback, this));
	gameRuleItem->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - gameRuleItem->getContentSize().height / 2));
	auto menu = Menu::create(gameRuleItem, NULL);
	menu->setPosition(Vec2::ZERO);
	addChild(menu, 1);

	this->scheduleUpdate();
	this->scheduleOnce(schedule_selector(GameLayer::updateOnce), 1.0f);
	return true;
}

void GameLayer::onHero1Walk(cocos2d::Point direction)
{
	if (direction != Point(0, 0))
	{
		if (direction.x != 0)
		    hero1->setFlippedX(direction.x < 0 ? false : true);  // ���Ӣ��Ҫ���󣬾ͷ�תһ��
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
	auto funcall = CallFunc::create(CC_CALLBACK_0(GameLayer::isCreatedP1, this));
	switch (hero1->pr)
	{
	case 1:  // �Ƶ�hero2��λ��
		prop1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop_1.png"));
		prop1->setPosition(hero2->getPosition().x, origin.y + visibleSize.height - prop1->getContentSize().height / 2);
		addChild(prop1, hero2->getZOrder() + 1);
		prop1->runAction(Sequence::create(MoveTo::create(0.5, hero2->getPosition()), funcall, NULL));
		break;
	case 2:  // �Ƶ�hero1��λ��
		prop1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop_2.png"));
		prop1->setPosition(hero1->getPosition().x, origin.y + visibleSize.height - prop1->getContentSize().height / 2);
		addChild(prop1, hero1->getZOrder() + 1);
		prop1->runAction(Sequence::create(MoveTo::create(0.5, hero1->getPosition()), funcall, NULL));
		break;
	case 3:  // �Ƶ�hero2��λ��
		prop1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop_3.png"));
		prop1->setPosition(hero2->getPosition().x, origin.y + visibleSize.height - prop1->getContentSize().height / 2);
		addChild(prop1, hero2->getZOrder() + 1);
		prop1->runAction(Sequence::create(MoveTo::create(0.5, hero2->getPosition()), funcall, NULL));
		break;
	default:
		break;
	}
}

// ������Ч���Լ�ɾ��ԭ����ͼƬ
void GameLayer::isCreatedP1()
{
	prop1->removeFromParent();
	switch (hero1->pr)
	{
	case 1:  // ��hero2���²�����̶
		sludge = Sprite::create("sludge.png");
		sludge->setPosition(Vec2(hero2->getPositionX(), hero2->getPositionY() - hero2->getContentSize().height / 2+10));
		this->addChild(sludge, hero2->getZOrder()-1);
		hasSludge1 = true;
		break;
	case 2:  // ��hero1��ǰ��������
			shield = Sprite::create("shield.png");
			shield->setFlippedX(true);
			shield->setPosition(hero1->getPositionX() + 30, hero1->getPositionY());
			this->addChild(shield, hero1->getZOrder() + 1);
			hasShield1 = true;
		break;
	case 3:  // ��hero2��������
		fire = ParticleFire::create();
		fire->setTexture(TextureCache::getInstance()->addImage("fire3.jpg"));
		fire->setPosition(hero2->getPosition());
		this->addChild(fire, hero2->getZOrder() + 1);
		fire->setDuration(2);
		fire->setScale(0.5f);
		break;
	default:
		break;
	}
	isCreated1 = true;
	schedule(schedule_selector(GameLayer::uodateOnce1), 1.0, 2, 0);
}

void GameLayer::uodateOnce1(float dt)
{
	static int count = 0;
	count += dt;
	if (count == 3) {
		isCreated1 = false;
		count = 0;
		if (hero1->pr == 1) {
			sludge->removeFromParent();
			hasSludge1 = false;
		}
		else if (hero1->pr == 2) {
			shield->removeFromParent();
			hasShield1 = false;
		}
		else if (hero1->pr == 3) fire->removeFromParent();
	}

	if (hero1->pr == 3) { // ����
		hero2->setHP(hero2->getHP() - 5);
		if (hero2->getHP() < 0) {
			hero2->setHP(0);
			// ��ת����ʤ����
		}
		hero2->hpBar->setPercentage(hero2->getHP());
	}
}

void GameLayer::onHero2Walk(cocos2d::Point direction)
{
	if (direction != Point(0, 0))
	{
		if (direction.x != 0)
		    hero2->setFlippedX(direction.x < 0 ? false : true);  // ���Ӣ��Ҫ���ң��ͷ�תһ��
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
	auto funcall = CallFunc::create(CC_CALLBACK_0(GameLayer::isCreatedP2, this));
	switch (hero2->pr)
	{
	case 1:  // �Ƶ�hero1��λ��
		prop2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop_1.png"));
		prop2->setPosition(hero1->getPosition().x, origin.y + visibleSize.height - prop2->getContentSize().height / 2);
		addChild(prop2, hero1->getZOrder() + 1);
		prop2->runAction(Sequence::create(MoveTo::create(0.5, hero1->getPosition()), funcall, NULL));
		break;
	case 2:  // �Ƶ�hero2��λ��
		prop2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop_2.png"));
		prop2->setPosition(hero2->getPosition().x, origin.y + visibleSize.height - prop2->getContentSize().height / 2);
		addChild(prop2, hero2->getZOrder() + 1);
		prop2->runAction(Sequence::create(MoveTo::create(0.5, hero2->getPosition()), funcall, NULL));
		break;
	case 3:  // �Ƶ�hero1��λ��
		prop2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("prop_3.png"));
		prop2->setPosition(hero1->getPosition().x, origin.y + visibleSize.height - prop2->getContentSize().height / 2);
		addChild(prop2, hero1->getZOrder() + 1);
		prop2->runAction(Sequence::create(MoveTo::create(0.5, hero1->getPosition()), funcall, NULL));
		break;
	default:
		break;
	}
}

void GameLayer::isCreatedP2()
{
	prop2->removeFromParent();
	switch (hero2->pr)
	{
	case 1:  // ��hero1���²�����̶
		sludge2 = Sprite::create("sludge.png");
		sludge2->setPosition(Vec2(hero1->getPositionX(), hero1->getPositionY() - hero1->getContentSize().height / 2 + 10));
		this->addChild(sludge2, hero1->getZOrder() - 1);
		hasSludge2 = true;
		break;
	case 2:  // ��hero2��ǰ��������
		shield2 = Sprite::create("shield.png");
		//shield2->setFlippedX(true);
		shield2->setPosition(hero2->getPositionX() - 30, hero2->getPositionY());
		this->addChild(shield2, hero2->getZOrder() + 1);
		hasShield2 = true;
		break;
	case 3:  // ��hero1��������
		fire2 = ParticleFire::create();
		fire2->setTexture(TextureCache::getInstance()->addImage("fire3.jpg"));
		fire2->setPosition(hero1->getPosition());
		this->addChild(fire2, hero1->getZOrder() + 1);
		fire2->setDuration(2);
		fire2->setScale(0.5f);
		break;
	default:
		break;
	}
	isCreated2 = true;
	schedule(schedule_selector(GameLayer::uodateOnce2), 1.0, 2, 0);
}

void GameLayer::uodateOnce2(float dt)
{
	static int count2 = 0;
	count2 += dt;
	if (count2 == 3) {
		isCreated2 = false;
		count2 = 0;
		if (hero2->pr == 1) {
			sludge2->removeFromParent();
			hasSludge2 = false;
		}
		else if (hero2->pr == 2) {
			shield2->removeFromParent();
			hasShield2 = false;
		}
		else if (hero2->pr == 3) fire2->removeFromParent();
	}

	if (hero2->pr == 3) { // ����
		hero1->setHP(hero1->getHP() - 5);
		if (hero1->getHP() < 0) {
			hero1->setHP(0);
			// ��ת����ʤ����
		}
		hero1->hpBar->setPercentage(hero1->getHP());
	}
}

void GameLayer::update(float dt)
{
	this->updateHero(dt);
	if (!hero1->bullets.empty())
	{
		for (Vector<Sprite*>::iterator it = hero1->bullets.begin(); it != hero1->bullets.end();)
		{
			auto dis = 40;
			if (hasShield2) dis = 60;
			if (hero2->getPosition().getDistance((*it)->getPosition()) < dis)
			{
				// �ӵ���ʧ��������ը��Ч�Լ����ű�ը����
				(*it)->removeFromParentAndCleanup(true);
				SimpleAudioEngine::getInstance()->playEffect("music/Explode.mp3", false, 1.0f, 1.0f, 1.0f);
				auto ex = ParticleSystemQuad::create("plist/explode.plist");
				ex->setPosition((*it)->getPosition());
				ex->setAutoRemoveOnFinish(true);
				ex->setDuration(0.1);
				ex->setScale(0.3f);
				addChild(ex, 5);
				if (!hasShield2) {
					hero2->runHurtAction();
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
					}// ��ʵ��gameover
					//ProgressTo *progressTo = ProgressTo::create(1, hero2->getHP());
					//hero2->hpBar->runAction(RepeatForever::create(progressTo));
					hero2->hpBar->setPercentage(hero2->getHP());
				}
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
			auto dis = 40;
			if (hasShield1) dis = 60;

			if (hero1->getPosition().getDistance((*itr)->getPosition()) < dis)
			{
				// �ӵ���ʧ��������ը��Ч�Լ����ű�ը����
				(*itr)->removeFromParentAndCleanup(true);
				SimpleAudioEngine::getInstance()->playEffect("music/Explode.mp3", false, 1.0f, 1.0f, 1.0f);
				auto ex = ParticleSystemQuad::create("plist/explode.plist");
				ex->setPosition((*itr)->getPosition());
				ex->setAutoRemoveOnFinish(true);
				ex->setDuration(0.1);
				ex->setScale(0.3f);
				addChild(ex, 5);
				if (!hasShield1) {
					// HP--;
					hero1->runHurtAction();
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
					}// ��ʵ��gameover
					//ProgressTo *progressTo = ProgressTo::create(1, hero1->getHP());
					//hero1->hpBar->runAction(RepeatForever::create(progressTo));
					hero1->hpBar->setPercentage(hero1->getHP());
				}
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
	if (isCreated1)
	{
		if (hero1->pr == 2) shield->setPosition(hero1->getPositionX() + 20, hero1->getPositionY());
		else if (hero1->pr == 3) fire->setPosition(hero2->getPosition());
	}
	if (isCreated2)
	{
		if (hero2->pr == 2) shield2->setPosition(hero2->getPositionX() - 30, hero2->getPositionY());
		else if (hero2->pr == 3) fire2->setPosition(hero1->getPosition());
	}
}

// ����Ӣ���ƶ���Χ
void GameLayer::updateHero(float dt)
{
	if (hasSludge1)
	{
		hero2->setVelocity(Point(0, 0));
	}
	if (hasSludge2)
	{
		hero1->setVelocity(Point(0, 0));
	}
	onMove(hero1);
	onMove(hero2);
}


// �ս�����Ϸ���棬�Զ�������Ϸ����˵������
void GameLayer::updateOnce(float dt)
{
	RenderTexture* renderTexture = RenderTexture::create(origin.x + visibleSize.width, origin.y + visibleSize.height);
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();

	Director::getInstance()->pushScene(GameRuleLayer::createScene(renderTexture, true));
}

void GameLayer::onMove(Hero * hero)
{
	if (hero->getCurrActionState() == ACTION_STATE_WALK)
	{
		auto halfHeroFrameHeight = (hero->getDisplayFrame()->getRect().size.height) / 2;  // ���Ӣ�۸߶�
		auto expectP = hero->getPosition() + hero->getVelocity();  // Ԥ����һ���ƶ�����λ��
		auto actualP = expectP;  // ʵ�ʽ�Ҫ�ƶ�����λ��
								 // ȷ�������Ƴ���ͼ����ǽ�ϣ�����tilemapֻ��15���ǿ������˵�
		if (expectP.y < halfHeroFrameHeight || expectP.y >(tileHeight * 12 + halfHeroFrameHeight))
		{
			actualP.y = hero->getPositionY();
		}
		float mapWidth = tmx->getContentSize().width;  // ���ŵ�ͼ��ȣ���ͼ�����Ǳ���Ļ���
		float halfWinWidth = screenWidth / 2;  // ��Ļһ���
		float halfHeroFrameWidth = (hero->getDisplayFrame()->getRect().size.width) / 2;  // ���Ӣ�ۿ��
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


void GameLayer::gameRuleCallback(Ref * pSender)
{
	RenderTexture* renderTexture = RenderTexture::create(origin.x + visibleSize.width, origin.y + visibleSize.height);
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();

	Director::getInstance()->pushScene(GameRuleLayer::createScene(renderTexture, false));
}
