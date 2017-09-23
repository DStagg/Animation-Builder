#include "EntityComponents.h"

//	Graphic

Graphic::Graphic()
{
	
};
Graphic::Graphic(sf::Sprite spr)
{

};

void Graphic::AddAnimation(std::string tag, Animation anim)
{
	_Animations[tag] = anim;
};

void Graphic::Play(float dt)
{
	if (GetCurrentAnimName() == "Static")
		return;
	
	GetCurrentAnim().Play(dt);
	_Sprite.setTextureRect(sf::IntRect(GetCurrentFrame()._X, GetCurrentFrame()._Y, GetCurrentFrame()._Width, GetCurrentFrame()._Height));
};

void Graphic::Swap(std::string tag)
{
	GetCurrentAnim()._CurrentFrame = 0;
	GetCurrentAnim()._Time = 0.f;

	_CurrentAnim = tag;

	if ( tag == "Static" )
		_Sprite.setTextureRect(sf::IntRect(0,0,_Sprite.getTexture()->getSize().x, _Sprite.getTexture()->getSize().y));
}

std::string Graphic::GetCurrentAnimName()
{
	return _CurrentAnim;
};
Animation& Graphic::GetCurrentAnim()
{
	return _Animations[GetCurrentAnimName()];
};
AnimationFrame Graphic::GetCurrentFrame()
{
	if (GetCurrentAnimName() == "Static")
		return AnimationFrame(0, 0, _Sprite.getTexture()->getSize().x, _Sprite.getTexture()->getSize().y, 0.f);
	return _Animations[GetCurrentAnimName()].GetCurrFrame();
};

void Graphic::SetSprite(sf::Sprite spr)
{
	_Sprite = spr;
};

sf::Sprite* Graphic::GetSprPntr()
{
	return &_Sprite;
};




//	Stats		//

Stats::Stats(int hp)
{
	SetHP(hp);
	SetMaxHP(hp);
};

void Stats::SetHP(int hp)
{
	_CurrentHP = hp;
};
int Stats::GetHP()
{
	return _CurrentHP;
};

void Stats::SetMaxHP(int hp)
{
	_MaximumHP = hp;
};
int Stats::GetMaxHP()
{
	return _MaximumHP;
};

void Stats::Hurt(int hp)
{
	SetHP(GetHP() - hp);
};