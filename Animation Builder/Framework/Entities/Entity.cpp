#include "Entity.h"

//	BaseEntity	////////////////////
BaseEntity::BaseEntity(Level* lvl)
{
	SetLevel(lvl);
};
PairFloat& BaseEntity::GetPosition()
{
	return _Position;
};
PairFloat& BaseEntity::GetVelocity()
{
	return _Velocity;
};
PairFloat& BaseEntity::GetSize()
{
	return _Size;
};
void BaseEntity::SetLevel(Level* lvl)
{
	_Level = lvl;
};
Level* BaseEntity::GetLevel()
{
	return _Level;
};
bool& BaseEntity::Alive()
{
	return _Alive;
};
//////////////////
AABB GenBoundBox(BaseEntity* ent)
{
	return AABB((int)ent->GetPosition()._X, (int)ent->GetPosition()._Y, (int)ent->GetSize()._X, (int)ent->GetSize()._Y);
};
void DebugDrawEntity(BaseEntity* ent, sf::RenderWindow* target, sf::Color col)
{
	sf::RectangleShape rect;
	rect.setPosition(floor(ent->GetPosition()._X), floor(ent->GetPosition()._Y));
	rect.setFillColor(sf::Color(0, 0, 0, 0));
	rect.setOutlineColor(col);
	rect.setOutlineThickness(1.f);
	rect.setSize(sf::Vector2f(ent->GetSize()._X, ent->GetSize()._Y));
	target->draw(rect);
};
////////////////////////////////////

//	Entity	////////////////////////
Entity::Entity(Level* lvl) : BaseEntity(lvl)
{
	Alive() = true;
};

float& Entity::GetHeading()
{
	return _Heading;
};
int& Entity::GetDirection()
{
	return _Direction;
};

Graphic& Entity::GetGraphic()
{
	return _Graphic;
};
////////////////////////////////////


//	BasicEnt	////////////////////
BasicEnt::BasicEnt(Level* lvl) : BaseEntity(lvl)
{

};
BasicEnt::BasicEnt(Level* lvl, PairFloat pos, PairFloat vel, PairFloat size) : BaseEntity(lvl)
{
	GetPosition() = pos;
	GetSize() = size;
	GetVelocity() = vel;
};

void BasicEnt::Update(float dt)
{
	GetPosition()._X = GetPosition()._X + (dt * GetVelocity()._X);
	GetPosition()._Y = GetPosition()._Y + (dt * GetVelocity()._Y);
};

void BasicEnt::Draw(sf::RenderWindow* rw)
{
	DebugDrawEntity(this, rw, sf::Color::White);
};
////////////////////////////////////

//	SFXEnt		////////////////////
SFXEnt::SFXEnt(Level* lvl) : Entity(lvl)
{

};

void SFXEnt::Update(float dt)
{
	GetPosition()._X = GetPosition()._X + (dt * GetVelocity()._X);
	GetPosition()._Y = GetPosition()._Y + (dt * GetVelocity()._Y);
	GetGraphic().Play(dt);
	if ((GetGraphic().GetCurrentAnim()._CurrentFrame == (int)GetGraphic().GetCurrentAnim()._Frames.size() - 1) && (GetGraphic().GetCurrentAnim()._Time > GetGraphic().GetCurrentFrame()._FrameTime))
		Alive() = false;
};
////////////////////////////////////

//	EntList	////////////////////////
EntList::EntList()
{

};
EntList::~EntList()
{
	Cull(0);
};

void EntList::AddEnt(BaseEntity* ent)
{
	if (ent == 0)
		return;
	if (std::find(_Entities.begin(), _Entities.end(), ent) != _Entities.end())
		return;
	_Entities.push_back(ent);
};
void EntList::DelEnt(BaseEntity* ent)
{
	if (ent == 0)
		return;
	if (std::find(_Entities.begin(), _Entities.end(), ent) != _Entities.end())
	{
		delete ent;
		_Entities.erase(std::find(_Entities.begin(), _Entities.end(), ent));
	}
};
void EntList::Cull(int limit)
{
	if (limit < 0)
		return;

	while (CountEnts() > limit)
	{
		delete GetEnt(0);
		_Entities.erase(_Entities.begin());
	}

	for (int i = 0; i < CountEnts(); i++)
	{
		if (!GetEnt(i)->Alive())
		{
			delete GetEnt(i);
			_Entities.erase(_Entities.begin() + i);
			i--;
		}
	}
};

int EntList::CountEnts()
{
	return (int)_Entities.size();
};
BaseEntity* EntList::GetEnt(int i)
{
	if (i < 0)
		i = 0;
	if (i >= CountEnts())
		i = CountEnts() - 1;

	return _Entities[i];
};
////////////////////////////////////

