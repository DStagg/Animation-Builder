#include "GUI.h"

GUIState::GUIState(int x, int y, int hot, int active, bool down)
{
	_MouseX = x;
	_MouseY = y;
	_HotItem = hot;
	_ActiveItem = active;
	_MouseDown = down;
};

/////////////////////

PairInt GUI::_Size;
sf::RenderWindow* GUI::_Window = 0;
sf::Font GUI::_Font;
sf::RenderTexture GUI::_TargetTexture;
GUIState GUI::_State;

void GUI::RegisterWindow(sf::RenderWindow* rw)
{
	_Window = rw;
	_Size.Set((int)rw->getSize().x, (int)rw->getSize().y);
	_TargetTexture.create((int)rw->getSize().x, (int)rw->getSize().y);
};

void GUI::RegisterFont(sf::Font f)
{
	_Font = f;
};


void GUI::StartFrame()
{
	GUI::GetTargetTexture().clear(sf::Color(0, 0, 0, 0));
	GUI::GetState()._HotItem = 0;
};

void GUI::EndFrame()
{
	if (!GUI::GetState()._MouseDown)
		GUI::GetState()._ActiveItem = 0;
	else if (GUI::GetState()._ActiveItem == 0)
		GUI::GetState()._ActiveItem = -1;
};

bool GUI::DoButton(int id, PairInt pos, PairInt size, std::string message)
{
	//	Check if hot & active
	if (MouseInRect(pos,size))
	{
		GUI::GetState()._HotItem = id;
		if ((GUI::GetState()._ActiveItem == 0) && (GUI::GetState()._MouseDown))
			GUI::GetState()._ActiveItem = id;
	}

	//	Render
	sf::RectangleShape rect;
	if ((GUI::GetState()._ActiveItem == id) && (GUI::GetState()._HotItem == id))	//	Clicked
	{
		rect.setSize(sf::Vector2f((float)size._X, (float)size._Y));
		rect.setPosition(sf::Vector2f((float)pos._X+2.f, (float)pos._Y+2.f));
		rect.setFillColor(sf::Color(212,208,200));
	}
	else if (GUI::GetState()._HotItem == id)										//	Hovered
	{
		rect.setSize(sf::Vector2f((float)size._X, (float)size._Y));
		rect.setPosition(sf::Vector2f((float)pos._X, (float)pos._Y));
		rect.setFillColor(sf::Color(202, 198, 190));
	}
	else																			//	Neutral
	{
		rect.setSize(sf::Vector2f((float)size._X, (float)size._Y));
		rect.setPosition(sf::Vector2f((float)pos._X, (float)pos._Y));
		rect.setFillColor(sf::Color(212, 208, 200));
		rect.setOutlineColor(sf::Color(128, 128, 128));
		rect.setOutlineThickness(1.f);
	};
	GetTargetTexture().draw(rect);

	sf::Text text(message, _Font);
	text.setPosition((float)pos._X + (((float)size._X - text.getLocalBounds().width)/2.f), (float)pos._Y + (((float)size._Y - text.getLocalBounds().height) / 2.f));
	text.setScale(0.75f, 0.75f);
	GetTargetTexture().draw(text);

	//	Trigger
	if ((GUI::GetState()._ActiveItem == id) && (GUI::GetState()._HotItem == id) && (!GUI::GetState()._MouseDown))
		return true;
	
	return false;
};

void GUI::DoSlider(int id, PairInt pos, PairInt size, float& value, float max)
{
	//	Check for mouse interaction
	PairInt testPos(pos._X, pos._Y - (size._X / 2));	//	Allows you to drag circle even from outside of the scroller
	PairInt testSize(size._X, size._Y + size._X);		//	Delete these two lines and just test pos and size to revert
	if (MouseInRect(testPos, testSize))
	{
		GUI::GetState()._HotItem = id;
		if ((GUI::GetState()._ActiveItem == 0) && (GUI::GetState()._MouseDown))
			GUI::GetState()._ActiveItem = id;
	}

	//	Calculate mouse progression along bar
	if (GUI::GetState()._ActiveItem == id)
	{
		int yOffset = GUI::GetState()._MouseY - pos._Y;
		if (yOffset < 0) 
			yOffset = 0;
		if (yOffset > size._Y)
			yOffset = size._Y;
		value = ((float)yOffset * max) / (float)size._Y;
	}

	int yPos = (int)((size._Y * value) / max);

	sf::RectangleShape bar;
	bar.setPosition((float)pos._X, (float)pos._Y);
	bar.setSize(sf::Vector2f((float)size._X, 1.f));
	bar.setFillColor(sf::Color::White);
	GUI::GetTargetTexture().draw(bar);

	bar.setPosition(sf::Vector2f((float)pos._X, (float)pos._Y + (float)size._Y));
	GUI::GetTargetTexture().draw(bar);

	bar.setPosition((float)(pos._X + (size._X / 2)), (float)(pos._Y));
	bar.setSize(sf::Vector2f(1.f, (float)size._Y));
	GUI::GetTargetTexture().draw(bar);

	sf::CircleShape point;
	point.setRadius((float)size._X / 2.f);
	point.setPosition((float)pos._X , (float)(pos._Y + yPos - (size._X / 2)));
	point.setFillColor(sf::Color(0, 0, 0, 0));
	point.setOutlineColor(sf::Color::White);
	point.setOutlineThickness(1);
	GUI::GetTargetTexture().draw(point);

};

void GUI::DoFrame(int id, PairInt pos, PairInt size, sf::Color col)
{
	sf::RectangleShape Rect;
	Rect.setPosition((float)pos._X, (float)pos._Y);
	Rect.setSize(sf::Vector2f((float)size._X, (float)size._Y));
	Rect.setFillColor(col);
	GetTargetTexture().draw(Rect);
};

void GUI::Draw()
{
	_TargetTexture.display();
	sf::Sprite Spr(_TargetTexture.getTexture());
	_Window->draw(Spr);
};

PairInt& GUI::GetSize()
{
	return _Size;
};

sf::RenderTexture& GUI::GetTargetTexture()
{
	return _TargetTexture;
};

GUIState& GUI::GetState()
{
	return _State;
};

//	Helper Functions
bool MouseInRect(PairInt pos, PairInt size)
{
	return((GUI::GetState()._MouseX >= pos._X) && (GUI::GetState()._MouseY >= pos._Y) && (GUI::GetState()._MouseX < pos._X + size._X) && (GUI::GetState()._MouseY < pos._Y + size._Y));
};