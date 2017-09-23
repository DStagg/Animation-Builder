#include <SFML/Graphics.hpp>

#include "Framework/Scene.h"
#include "MainScene.h"

int main()
{
	int FramesPerSecond = 60;
	float deltaT = 0.f;
	sf::Clock UpdateClock;

	sf::RenderWindow _Window;
	_Window.create(sf::VideoMode(1200, 800), "Animation Builder");

	SceneManager SCM;
	SCM.PushScene(new MainScene(&_Window));

	UpdateClock.restart();
	while (SCM.GetActiveScenePntr() != 0)
	{
		SCM.GetActiveScenePntr()->Update(UpdateClock.restart().asSeconds());
		_Window.clear();
		SCM.GetActiveScenePntr()->DrawScreen();
		_Window.display();
		SCM.CullScenes();
	}

	return 0;
};