#ifndef MENULIST_H
#define MENULIST_H

#include <vector>
#include "SFML/Graphics.hpp"

class MenuList
{
public:

	MenuList();
	~MenuList();

	void Populate(std::vector<std::string> list);

	int GetChoice();
	void SetChoice(int choice);
	void IncChoice();
	void DecChoice();

	void SetLoop(bool b);
	bool GetLoop();

	int CountList();
	std::string GetList(int id);
	void SetList(int id, std::string text);

private:

	int _Choice;
	bool _Loop;
	std::vector<std::string> _List;
};

class SFMLMenuList : public MenuList
{
public:

	SFMLMenuList();
	~SFMLMenuList();

	void Format(sf::Font font, float x = 0.f, float y = 0.f, int orientation = SFMLMenuList::Left);

	void SetBuffers(float x, float y);

	void Draw(sf::RenderWindow* rw);

	enum Orientation
	{
		Left,
		Center,
		Right
	};

private:

	float _XBuffer, _YBuffer;
	float _X, _Y;
	sf::Font _Font;
	int _Orientation;
};

#endif