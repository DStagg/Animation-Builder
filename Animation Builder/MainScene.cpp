#include "MainScene.h"

MainScene::MainScene(sf::RenderWindow* rw)
{
	_Window = rw;
};
MainScene::~MainScene()
{

};

void MainScene::Begin()
{
	//	Setup GUI
	_Font.loadFromFile("Roboto-Regular.ttf");
	GUI::RegisterFont(_Font);
	GUI::RegisterWindow(_Window);

	//	Save camera view for sheet area
	_DefaultView = _Window->getDefaultView();
	_DefaultView.setCenter(_Window->getDefaultView().getCenter().x, _Window->getDefaultView().getCenter().y - _TopBarHeight);
};
void MainScene::End()
{
	
};
void MainScene::Pause()
{

};
void MainScene::Resume()
{

};
void MainScene::Update(float dt)
{
	GUI::StartFrame();

	sf::Event Event;
	while (_Window->pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
			SetRunning(false);				
		else if (Event.type == sf::Event::MouseMoved)
		{
			//	Update GUI Input
			GUI::GetState()._MouseX = sf::Mouse::getPosition(*_Window).x;
			GUI::GetState()._MouseY = sf::Mouse::getPosition(*_Window).y;

			//	Pan Camera
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
			{
				float factor = _DefaultView.getSize().x / _Window->getView().getSize().x;
				sf::View v = _Window->getView();
				sf::Vector2i newpos = sf::Mouse::getPosition(*_Window);
				v.move((float)(_OldMouse._X - newpos.x) / factor, (float)(_OldMouse._Y - newpos.y) / factor);
				_Window->setView(v);
			}

			//	Move Selection
			if ((_Loaded) && (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)))
			{
				float factor = _DefaultView.getSize().x / _Window->getView().getSize().x;
				sf::Vector2i newpos = sf::Mouse::getPosition(*_Window);
				PairInt move((_OldMouse._X - newpos.x) / (int)factor, (_OldMouse._Y - newpos.y) / (int)factor);
				_DragA.Set(_DragA._X - move._X, _DragA._Y - move._Y);
				_DragB.Set(_DragB._X - move._X, _DragB._Y - move._Y);
			}
		}
		else if ((Event.type == sf::Event::MouseButtonPressed) && (Event.mouseButton.button == sf::Mouse::Left))
		{
			//	Update GUI Input
			GUI::GetState()._MouseDown = true;
		}
		else if ((Event.type == sf::Event::MouseButtonReleased) && (Event.mouseButton.button == sf::Mouse::Left))
		{
			//	Update GUI Input
			GUI::GetState()._MouseDown = false;
		}
		else if (Event.type == sf::Event::KeyPressed)
		{
			//	Reset Camera View
			if (Event.key.code == sf::Keyboard::BackSpace)
				_Window->setView(_DefaultView);
			//	Fine-tune Selection Placement
			else if (Event.key.code == sf::Keyboard::Up)
			{
				_DragA._Y -= 1;
				_DragB._Y -= 1;
			}
			else if (Event.key.code == sf::Keyboard::Down)
			{
				_DragA._Y += 1;
				_DragB._Y += 1;
			}
			else if (Event.key.code == sf::Keyboard::Left)
			{
				_DragA._X -= 1;
				_DragB._X -= 1;
			}
			else if (Event.key.code == sf::Keyboard::Right)
			{
				_DragA._X += 1;
				_DragB._X += 1;
			}
			//	Fine-tune Selection Size
			else if (Event.key.code == sf::Keyboard::W)
				_DragB._Y -= 1;
			else if (Event.key.code == sf::Keyboard::S)
				_DragB._Y += 1;
			else if (Event.key.code == sf::Keyboard::A)
				_DragB._X -= 1;
			else if (Event.key.code == sf::Keyboard::D)
				_DragB._X += 1;
		}
	}

	//	Draw Bars
	GUI::DoFrame(GenID, PairInt(_Window->getSize().x - _SideBarWidth, 0), PairInt(_SideBarWidth, _Window->getSize().y), sf::Color(90, 90, 90));
	GUI::DoFrame(GenID, PairInt(0, 0), PairInt(_Window->getSize().x, _TopBarHeight), sf::Color(100,100,100));

	//	Top Bar Buttons
	if (GUI::DoButton(GenID, PairInt(2, 2), PairInt(160, 32), "Open Sheet"))
	{
		std::string name;
		if (GetLoadFile(name, "Open", GetCurrDir()))
		{
			if (_Sheet.loadFromFile(name))
			{
				_Sheet.setSmooth(false);
				_Window->setView(_DefaultView);
				_Loaded = true;
				_SheetName = name.substr(name.find_last_of("/\\") + 1, std::string::npos);
			}
		}
	}
	if (GUI::DoButton(GenID, PairInt(166, 2), PairInt(160, 32), "Close Sheet"))
	{
		_Sheet.~Texture();
		_CurrAnim._Frames.clear();
		_AnimName = "";
		_SheetName = "";
		_Loaded = false;
	}
	if (GUI::DoButton(GenID, PairInt(_Window->getSize().x - 34, 2), PairInt(32, 32), "+"))
	{
		sf::View v = _Window->getView();
		v.zoom(0.5f);
		_Window->setView(v);
	}
	if (GUI::DoButton(GenID, PairInt(_Window->getSize().x - 68, 2), PairInt(32, 32), "-"))
	{
		if (_DefaultView.getSize().x != _Window->getView().getSize().x)
		{
			sf::View v = _Window->getView();
			v.zoom(2.f);
			_Window->setView(v);
		}
	}
	if (GUI::DoButton(GenID, PairInt(_Window->getSize().x - 350,2), PairInt(160,32), "Zoom"))
	{
		sf::View v = _Window->getView();
		v.setCenter(Min(_DragA._X, _DragB._X) + (Abs(_DragA._X - _DragB._X) / 2.f), Min(_DragA._Y, _DragB._Y) + (Abs(_DragA._Y - _DragB._Y) / 2.f));
		_Window->setView(v);
	}
	if (GUI::DoButton(GenID, PairInt(_Window->getSize().x - 166, 2), PairInt(96, 32) , "Reset"))
		_Window->setView(_DefaultView);
	if (GUI::DoButton(GenID, PairInt(350, 2), PairInt(160, 32), "+ Frame"))
	{
		_CurrAnim._Frames.push_back(AnimationFrame(Min(_DragA._X, _DragB._X), Min(_DragA._Y, _DragB._Y), Abs(_DragA._X - _DragB._X), Abs(_DragA._Y - _DragB._Y), 0.1f));
		_CurrFrame = -1;
	}
	if (GUI::DoButton(GenID, PairInt(350, 40), PairInt(160, 32), "Overwrite"))
	{
		if (_CurrFrame != -1)
		{
			_CurrAnim._Frames[_CurrFrame] = AnimationFrame(Min(_DragA._X, _DragB._X), Min(_DragA._Y, _DragB._Y), Abs(_DragA._X - _DragB._X), Abs(_DragA._Y - _DragB._Y), 0.1f);
		}
	}
	if (GUI::DoButton(GenID, PairInt(166, 40), PairInt(160, 32), "Save Anim"))
	{
		if ((int)_CurrAnim._Frames.size() > 0)
		{
			std::string name;
			GetSaveFile(name, "Save to...", GetCurrDir(), "Animation\0*.anim\0\0");
			SaveAnim(name, _CurrAnim);
		}
	}
	if (GUI::DoButton(GenID, PairInt(2, 40), PairInt(160, 32), "Load Anim"))
	{
		std::string name;
		if (GetLoadFile(name, "Load from...", GetCurrDir(), "Animation\0*.anim\0\0"))
		{
			_CurrAnim._Frames.clear();
			LoadAnim(name, _CurrAnim);
			_AnimName = name.substr(name.find_last_of("/\\") + 1, std::string::npos);
		}
	}
	if (GUI::DoButton(GenID, PairInt(534, 40), PairInt(160, 32), "Clear Anim"))
	{
		_CurrAnim._Frames.clear();
		_AnimName = "";
	}
	if (GUI::DoButton(GenID, PairInt(718, 40), PairInt(160, 32), "Del Frame"))
	{
		if (_CurrFrame != -1)
		{
			_CurrAnim._Frames.erase(_CurrAnim._Frames.begin() + _CurrFrame);
			_DragA.Set(0, 0);
			_DragB.Set(0, 0);
			_CurrFrame = -1;
		}
	}
	
	//	Side Bar Buttons
	if (((int)_CurrAnim._Frames.size() > 0) && (GUI::DoButton(GenID, PairInt(_Window->getSize().x - (_SideBarWidth - 2), _TopBarHeight + 2), PairInt(_SideBarWidth - 4, 32), (_CurrAnim._Loop ? "Loop" : "Single" ))))
		_CurrAnim._Loop = !_CurrAnim._Loop;
	if (_CurrFrame != -1)
		GUI::DoFrame(GenID, PairInt(_Window->getSize().x - _SideBarWidth, _TopBarHeight + 2 + (36 * (_CurrFrame+1))), PairInt(_SideBarWidth, 32), sf::Color::Red);
	for (int i = 0; i < (int)_CurrAnim._Frames.size(); i++)
	{
		if (GUI::DoButton(GenID * ((i + 1) * 50), PairInt(_Window->getSize().x - (_SideBarWidth - 2), _TopBarHeight + 2 + (36*(i+1))), PairInt(_SideBarWidth - 4, 32), IntToString(i)))
		{
			_DragA.Set(_CurrAnim._Frames[i]._X, _CurrAnim._Frames[i]._Y);
			_DragB.Set(_CurrAnim._Frames[i]._X + _CurrAnim._Frames[i]._Width, _CurrAnim._Frames[i]._Y + _CurrAnim._Frames[i]._Height);
			_CurrFrame = i;
		}
	}

	//	Drag Selection
	if ((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && (sf::Mouse::getPosition(*_Window).y >= (float)_TopBarHeight) && (sf::Mouse::getPosition(*_Window).x < _Window->getSize().x - (float)_SideBarWidth))
	{
		if (!_Dragging)
		{
			_Dragging = true;
			sf::Vector2f pos = _Window->mapPixelToCoords(sf::Mouse::getPosition(*_Window));
			_DragA.Set((int)pos.x, (int)pos.y);
		}
		sf::Vector2f pos = _Window->mapPixelToCoords(sf::Mouse::getPosition(*_Window));
		_DragB.Set((int)pos.x, (int)pos.y);
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		_Dragging = false;

	//	Preview Animation
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		_CurrAnim.Play(dt);
	else
	{
		_CurrAnim._CurrentFrame = 0;
		_CurrAnim._Time = 0.f;
	}

	//	Store mouse position for next frame's panning
	sf::Vector2i newpos = sf::Mouse::getPosition(*_Window);
	_OldMouse.Set(newpos.x, newpos.y);

	GUI::EndFrame();
};
void MainScene::DrawScreen()
{
	if (_Loaded)
	{
		sf::Sprite spr(_Sheet);
		_Window->draw(spr);

		PairFloat origin((float)Min(_DragA._X, _DragB._X), (float)Min(_DragA._Y, _DragB._Y));
		PairFloat size((float)Abs(_DragB._X - _DragA._X), (float)Abs(_DragB._Y - _DragA._Y));

		sf::RectangleShape rect;
		rect.setPosition(origin._X, origin._Y);
		rect.setSize(sf::Vector2f(size._X, size._Y));
		if (_DrawSelectionOutline)
		{
			rect.setFillColor(sf::Color(0, 0, 0, 0));
			rect.setOutlineColor(sf::Color::Cyan);
			rect.setOutlineThickness(1.f);
		}
		else
			rect.setFillColor(sf::Color(255, 255, 0, 100));
		_Window->draw(rect);

		sf::RectangleShape pixel;
		sf::Vector2f world = _Window->mapPixelToCoords(sf::Mouse::getPosition(*_Window));
		pixel.setPosition(floor(world.x), floor(world.y));
		pixel.setSize(sf::Vector2f(1.f, 1.f));
		pixel.setFillColor(sf::Color(255, 0, 0, 100));
		_Window->draw(pixel);
	}


	sf::View temp = _Window->getView();
	_Window->setView(_Window->getDefaultView());
	GUI::Draw();
	if (_Loaded)
	{
		sf::Text sheetname(_SheetName, _Font);
		sheetname.setPosition(2.f, _Window->getSize().y - (7.f + sheetname.getLocalBounds().height));
		_Window->draw(sheetname);

		sf::Text selection;
		selection.setFont(_Font);
		selection.setString("[" + IntToString(Abs(_DragA._X - _DragB._X)) + "," + IntToString(Abs(_DragA._Y - _DragB._Y)) + "] at (" + IntToString(Min(_DragA._X, _DragB._X)) + "," + IntToString(Min(_DragA._Y, _DragB._Y)) + ")");
		selection.setPosition(534.f, 2.f);
		_Window->draw(selection);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			sf::RectangleShape background;
			background.setSize(sf::Vector2f((float)_Window->getSize().x, (float)_Window->getSize().y));
			background.setPosition(0.f, 0.f);
			background.setFillColor(sf::Color(100, 100, 100, 100));
			_Window->draw(background);

			sf::Sprite spr;
			spr.setTexture(_Sheet);
			spr.setTextureRect(sf::IntRect(_CurrAnim.GetCurrFrame()._X, _CurrAnim.GetCurrFrame()._Y, _CurrAnim.GetCurrFrame()._Width, _CurrAnim.GetCurrFrame()._Height));
			float xfactor = (_Window->getSize().x * 0.75f) / spr.getLocalBounds().width;
			float yfactor = (_Window->getSize().y * 0.75f) / spr.getLocalBounds().height;
			spr.setScale(Min(xfactor, yfactor), Min(xfactor, yfactor));
			spr.setPosition((_Window->getSize().x - (spr.getLocalBounds().width * Min(xfactor, yfactor))) / 2.f, (_Window->getSize().y - (spr.getLocalBounds().height * Min(xfactor, yfactor))) / 2.f);
			_Window->draw(spr);
		}

	}
	if (_AnimName != "")
	{
		sf::Text animname(_AnimName, _Font);
		animname.setPosition(_Window->getSize().x - animname.getLocalBounds().width, 40.f);
		_Window->draw(animname);
	}
	_Window->setView(temp);

};

bool GetSaveFile(std::string& name, std::string title, std::string startdir, const char* filter) 
{
	//	Set up the structure to hold the results
	const int BUFSIZE = 1024;
	char buffer[BUFSIZE] = { 0 };
	OPENFILENAME ofns = { 0 };
	if (filter != "")
	{
		ofns.lpstrDefExt = ".anim";
		ofns.lpstrFilter = filter;
	}
	ofns.Flags = OFN_OVERWRITEPROMPT | OFN_CREATEPROMPT;
	ofns.lStructSize = sizeof(ofns);
	ofns.lpstrFile = buffer;
	ofns.nMaxFile = BUFSIZE;
	if (startdir != "") ofns.lpstrInitialDir = startdir.c_str();
	ofns.lpstrTitle = title.c_str();
	//	If the user selects a valid file save the name to the provided std::string reference and return true
	if (GetSaveFileName(&ofns))
	{
		name = std::string(ofns.lpstrFile);
		return true;
	}
	//	Otherwise return false
	name = "";
	return false;
};
bool GetLoadFile(std::string& name, std::string title, std::string startdir, const char* filter)
{
	//	Set up the structure to hold the results
	const int BUFSIZE = 1024;
	char buffer[BUFSIZE] = { 0 };
	OPENFILENAME ofns = { 0 };
	if (filter != "")
	{
		ofns.lpstrFilter = filter;
	}
	ofns.Flags = OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST;
	ofns.lStructSize = sizeof(ofns);
	ofns.lpstrFile = buffer;
	ofns.nMaxFile = BUFSIZE;
	if (startdir != "") ofns.lpstrInitialDir = startdir.c_str();
	ofns.lpstrTitle = title.c_str();
	//	If the user selects a valid file save the name to the provided std::string reference and return true
	if (GetOpenFileName(&ofns))
	{
		name = std::string(ofns.lpstrFile);
		return true;
	}
	//	Otherwise return false
	name = "";
	return false;
};


std::string GetCurrDir()
{
	//	Locate full path of current executable
	TCHAR path[MAX_PATH];
	GetModuleFileName(NULL, path, MAX_PATH);
	std::string res = std::string(path);
	//	Trim off the file name of the executable
	std::size_t found = res.find_last_of("/\\");
	res = res.substr(0, found);
	res.append("\\");
	//	Return the result
	return res;
};

void SaveAnim(std::string animname, Animation& anim)
{
	BinaryFile out(animname, FileMode::IO_OUT, true);
	out.Write<std::string>(animname);
	out.Write<int>((int)anim._Frames.size());
	for (int i = 0; i < (int)anim._Frames.size(); i++)
	{
		out.Write<int>(anim._Frames[i]._X);
		out.Write<int>(anim._Frames[i]._Y);
		out.Write<int>(anim._Frames[i]._Width);
		out.Write<int>(anim._Frames[i]._Height);
		out.Write<float>(anim._Frames[i]._FrameTime);
	}
	out.Write<bool>(anim._Loop);
	out.Close();
};

void LoadAnim(std::string animname, Animation& anim)
{
	BinaryFile in(animname, FileMode::IO_IN);
	std::string name = in.Read<std::string>();
	int count = in.Read<int>();
	for (int i = 0; i < count; i++)
	{
		AnimationFrame temp(0,0,0,0,0.f);
		temp._X = in.Read<int>();
		temp._Y = in.Read<int>();
		temp._Width = in.Read<int>();
		temp._Height = in.Read<int>();
		temp._FrameTime = in.Read<float>();
		anim._Frames.push_back(temp);
	}
	anim._Loop = in.Read<bool>();
	in.Close();
};