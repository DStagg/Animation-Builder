#ifndef MainScene_H
#define MainScene_H

#include <iostream>
#include <SFML\Graphics.hpp>
#include "Framework/Scene.h"
#include "Framework\IO\ImageManager.h"
#include "Framework\IO\GUI.h"
#include "Framework\Utility\Utility.h"
#include "Framework\Entities\EntityComponents.h"
#include <Windows.h>
#include "Framework\IO\BinarySave.h"

class MainScene : public Scene
{
public:

	MainScene(sf::RenderWindow* rw);
	~MainScene();

	void Begin();
	void End();
	void Pause();
	void Resume();
	void Update(float dt);
	void DrawScreen();

private:

	//	Window
	sf::RenderWindow* _Window = 0;
	sf::View _DefaultView;
	int _TopBarHeight = 100;
	int _SideBarWidth = 100;
	//	Resources
	ImageManager _Manager;
	sf::Texture _Sheet;
	std::string _SheetName;
	std::string _AnimName;
	sf::Font _Font;
	bool _Loaded = false;
	Animation _CurrAnim;
	int _CurrFrame = -1;
	//	Input
	PairInt _OldMouse;
	bool _Dragging = false;
	PairInt _DragA;
	PairInt _DragB;
};

bool GetLoadFile(std::string& name, std::string title, std::string startdir = "", const char* filter = "");
bool GetSaveFile(std::string& name, std::string title, std::string startdir = "", const char* filter = "");
std::string GetCurrDir();
void SaveAnim(std::string animname, Animation& anim);
void LoadAnim(std::string animname, Animation& anim);

#endif