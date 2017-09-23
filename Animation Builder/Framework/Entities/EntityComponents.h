#ifndef ENTITYCOMPONENTS_H
#define ENTITYCOMPONENTS_H

#include "SFML\Graphics.hpp"
#include "../IO/ImageManager.h"
#include "../Data/Pair.h"

class Graphic
{
public:

	Graphic();
	Graphic(sf::Sprite spr);

	void AddAnimation(std::string tag, Animation anim);

	void Play(float dt);
	void Swap(std::string tag = "Static");

	std::string GetCurrentAnimName();
	Animation& GetCurrentAnim();
	AnimationFrame GetCurrentFrame();

	void SetSprite(sf::Sprite spr);
	sf::Sprite* GetSprPntr();

private:

	std::string _CurrentAnim = "Static";
	std::map <std::string, Animation > _Animations;
	sf::Sprite _Sprite;
};

class Stats
{
public:

	Stats(int hp = 1);

	void SetHP(int hp);
	int GetHP();
	void SetMaxHP(int hp);
	int GetMaxHP();

	void Hurt(int hp);

private:

	int _CurrentHP;
	int _MaximumHP;
};

#endif