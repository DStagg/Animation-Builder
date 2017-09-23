#ifndef GUI_H
#define GUI_H

#define GenID (__LINE__)

#include "../Data/Pair.h"
#include <string>
#include "SFML\Graphics.hpp"

struct GUIState
{
	GUIState(int x = 0, int y = 0, int hot = 0, int active = 0, bool down = false);

	int _MouseX;
	int _MouseY;

	int _HotItem;
	int _ActiveItem;

	bool _MouseDown;
};

class GUI
{
public:

	static void RegisterWindow(sf::RenderWindow* rw);
	static void RegisterFont(sf::Font f);

	static void StartFrame();
	static void EndFrame();

	static bool DoButton(int id, PairInt pos, PairInt size, std::string label);
	static void DoFrame(int id, PairInt pos, PairInt size, sf::Color col);
	static void DoSlider(int id, PairInt pos, PairInt size, float& value, float max);
	
	static void Draw();

	static PairInt& GetSize();		
	static sf::RenderTexture& GetTargetTexture();
	static GUIState& GetState();

private:

	static PairInt _Size;			
	static sf::RenderWindow* _Window;
	static sf::Font _Font;
	static sf::RenderTexture _TargetTexture;
	static GUIState _State;
};

//	Helper Functions	//
bool MouseInRect(PairInt pos, PairInt size);

#endif