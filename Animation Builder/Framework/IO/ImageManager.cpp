#include "ImageManager.h"

AnimationFrame::AnimationFrame(int x, int y, int w, int h, float ft)
{
	_X = x;
	_Y = y;
	_Width = w;
	_Height = h;
	_FrameTime = ft;
};

Animation::Animation()
{
	_CurrentFrame = 0;
	_Time = 0.f;
	_Rate = 1.f;
	_Loop = true;
};

void Animation::Play(float dt)
{
	if ((int)_Frames.size() == 0)
		return;
	dt = dt * _Rate;
	_Time += dt;
	if (_Time >= GetCurrFrame()._FrameTime)
	{
		if ((_CurrentFrame < (int)_Frames.size() - 1) || (_Loop))
		{
			_Time -= GetCurrFrame()._FrameTime;
			_CurrentFrame++;

			if ((_CurrentFrame >= (int)_Frames.size()) && (_Loop))
				_CurrentFrame = 0;
		}
	}
};

AnimationFrame Animation::GetCurrFrame()
{
	return _Frames[_CurrentFrame];
};

ImageManager::ImageManager()
{
	sf::Image defImg;
	defImg.create(32, 32);
	for (int x = 0; x < 32; x++)
		for (int y = 0; y < 32; y++)
			defImg.setPixel(x, y, sf::Color::Cyan);
	sf::Texture defTex;
	defTex.loadFromImage(defImg);
	_Textures["Default"] = defTex;
	SetTransMask();
	SetSmooth(false);

	AnimationFrame frame(0, 0, 1, 1, 0.f);
	Animation anim;
	anim._Frames.push_back(frame);
	_Animations["Default"] = anim;
};
ImageManager::~ImageManager()
{

};

bool ImageManager::LoadTextureFromFile(std::string tag, std::string filename)
{
	sf::Image img;
	sf::Texture tex;

	if (img.loadFromFile(filename))
	{
		img.createMaskFromColor(GetTransMask());
		tex.loadFromImage(img);
		tex.setSmooth(GetSmooth());
		_Textures[tag] = tex;
		return true;
	}

	//tex.create(32, 32);
	_Textures[tag] = _Textures["Default"];
	return false;
};

sf::Texture* ImageManager::GetTexturePntr(std::string tag)
{
	for (std::map<std::string, sf::Texture>::iterator i = _Textures.begin(); i != _Textures.end(); i++)
	{
		if (i->first == tag)
			return &i->second;
	}

	return &_Textures["Default"];
};

void ImageManager::AddAnimation(std::string tag, Animation anim)
{
	_Animations[tag] = anim;
};
Animation ImageManager::GetAnimation(std::string tag)
{
	for (std::map<std::string, Animation>::iterator i = _Animations.begin(); i != _Animations.end(); i++)
	{
		if (i->first == tag)
			return _Animations[tag];
	}

	return _Animations["Default"];
};

void ImageManager::SetTransMask(sf::Color col)
{
	_TransparencyMask = col;
};
sf::Color ImageManager::GetTransMask()
{
	return _TransparencyMask;
};

void ImageManager::SetSmooth(bool b)
{
	_Smooth = b;
};
bool ImageManager::GetSmooth()
{
	return _Smooth;
};

///

sf::IntRect AnimIntRect(Animation anim)
{
	return sf::IntRect(anim._Frames[anim._CurrentFrame]._X, anim._Frames[anim._CurrentFrame]._Y, anim._Frames[anim._CurrentFrame]._Width, anim._Frames[anim._CurrentFrame]._Height);
};