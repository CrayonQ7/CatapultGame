#ifndef __AMHERO_H__
#define __AMHERO_H__

#include "cocos2d.h"
#include "BaseSprite.h"

class AMHero : public BaseSprite
{
public:
	AMHero();
	~AMHero();
	static AMHero* create(int pl);
	bool init(int pl);
	//CREATE_FUNC(AMHero);
	void loadHero_1();
	void loadHero_2();
	void loadHero_3();
	void createHpBar(int p);
	std::function<void(cocos2d::Point)> pWalk;
	std::function<void(void)> pStop;
	cocos2d::ProgressTimer* hpBar;  // ÑªÌõ
	cocos2d::Sprite* hpBgSprite;
};

#endif

