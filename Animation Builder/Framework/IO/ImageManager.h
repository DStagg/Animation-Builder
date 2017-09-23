#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include "SFML\Graphics.hpp"
#include <algorithm>

struct AnimationFrame
{
	AnimationFrame(int x, int y, int w, int h, float ft);

	int _X, _Y, _Width, _Height;
	float _FrameTime;
};

struct Animation
{
	Animation();

	void Play(float dt);
	AnimationFrame GetCurrFrame();

	bool _Loop;
	float _Rate;
	float _Time;
	int _CurrentFrame;
	std::vector<AnimationFrame> _Frames;
};

class ImageManager
{
public:

	ImageManager();
	~ImageManager();

	bool LoadTextureFromFile(std::string tag, std::string filename);
	sf::Texture* GetTexturePntr(std::string tag);

	void AddAnimation(std::string tag, Animation anim);
	Animation GetAnimation(std::string tag);

	void SetTransMask(sf::Color col = sf::Color(163, 73, 164));
	sf::Color GetTransMask();

	void SetSmooth(bool b);
	bool GetSmooth();

private:

	sf::Color _TransparencyMask;
	bool _Smooth;

	std::map<std::string, sf::Texture> _Textures;
	std::map<std::string, Animation> _Animations;

};

sf::IntRect AnimIntRect(Animation anim);

#endif