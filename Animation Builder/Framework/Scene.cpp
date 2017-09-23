#include "Scene.h"

Scene::Scene()
{
	_ParentPntr = 0;
	_ChildPntr = 0;
	_ManagerPntr = 0;
	_Running = true;
};
Scene::~Scene() {};

void Scene::SetRunning(bool b)
{
	_Running = b;
};
bool Scene::IsRunning()
{
	return _Running;
};

Scene* Scene::GetParent()
{
	return _ParentPntr;
};
Scene* Scene::GetChild()
{
	return _ChildPntr;
};
void Scene::SetParent(Scene* sc)
{
	_ParentPntr = sc;
};
void Scene::SetChild(Scene* sc)
{
	_ChildPntr = sc;
};

SceneManager* Scene::GetManager()
{
	return _ManagerPntr;
};
void Scene::SetManager(SceneManager* sm)
{
	_ManagerPntr = sm;
};

///

SceneManager::SceneManager()
{
	_RootScenePntr = 0;
};
SceneManager::~SceneManager()
{

};

void SceneManager::PushScene(Scene* new_scene)
{
	if (new_scene == 0)
		return;
	new_scene->SetManager(this);
	if (_RootScenePntr == 0)
	{
		_RootScenePntr = new_scene;
	}
	else
	{
		new_scene->SetParent(GetActiveScenePntr());
		GetActiveScenePntr()->Pause();
		GetActiveScenePntr()->SetChild(new_scene);
	}
	GetActiveScenePntr()->Begin();
};

void SceneManager::CullScenes()
{
	if (_RootScenePntr == 0)
		return;
	while (GetActiveScenePntr() != 0)
	{
		if (!GetActiveScenePntr()->IsRunning())
		{
			Scene* newActive = GetActiveScenePntr()->GetParent();
			GetActiveScenePntr()->End();
			delete GetActiveScenePntr();
			if (newActive == 0)
				_RootScenePntr = 0;
			else
			{
				newActive->SetChild(0);
				newActive->Resume();
			}
		}
		else
			break;
	}
};

void SceneManager::Quit(int i)
{
	Scene* curr = GetActiveScenePntr();
	while (curr != 0)
	{
		if (i == 0)
			break;
		i -= 1;
		curr->SetRunning(false);
		curr = curr->GetParent();
	}
};

Scene* SceneManager::GetActiveScenePntr()
{
	if (_RootScenePntr == 0)
		return 0;
	Scene* currScene = _RootScenePntr;
	while (currScene->GetChild() != 0)
		currScene = currScene->GetChild();
	return currScene;
};

Scene* SceneManager::GetRootScenePntr()
{
	return _RootScenePntr;
};