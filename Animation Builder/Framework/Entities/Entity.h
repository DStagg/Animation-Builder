#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <algorithm>

#include "../Data/AABB.h"

#include "EntityComponents.h"

enum Direction
{
	North = 0,
	NorthEast,
	East,
	SouthEast,
	South,
	SouthWest,
	West,
	NorthWest
};

class Level;

class BaseEntity
{
public:

	BaseEntity(Level* lvl);

	PairFloat& GetPosition();
	PairFloat& GetVelocity();
	PairFloat& GetSize();

	virtual void Update(float dt) = 0;
	virtual void Draw(sf::RenderWindow* rw) = 0;

	void SetLevel(Level* lvl);
	Level* GetLevel();

	bool& Alive();

private:

	PairFloat	_Position = PairFloat(0.f, 0.f);
	PairFloat	_Velocity = PairFloat(0.f, 0.f);
	PairFloat	_Size = PairFloat(1.f, 1.f);

	Level* _Level = 0;
	bool _Alive = true;
};

AABB GenBoundBox(BaseEntity* ent);
void DebugDrawEntity(BaseEntity* ent, sf::RenderWindow* target, sf::Color col = sf::Color::Red);

////////////////////////////////////

class Entity : public BaseEntity
{
public:

	Entity(Level* lvl);

	float& GetHeading();
	int& GetDirection();

	Graphic& GetGraphic();

private:

	float _Heading = 0.f;
	int _Direction = Direction::North;

	Graphic _Graphic;
	
};

////////////////////////////////////

class BasicEnt : public BaseEntity
{
public:

	BasicEnt(Level* lvl);
	BasicEnt(Level* lvl, PairFloat pos, PairFloat vel, PairFloat size);

	void Update(float dt);
	void Draw(sf::RenderWindow* rw);

};

////////////////////////////////////

class SFXEnt : public Entity
{
public:

	SFXEnt(Level* lvl);

	void Update(float dt);

private:

};

////////////////////////////////////

class EntList
{
public:

	EntList();
	~EntList();

	void AddEnt(BaseEntity* ent);
	void DelEnt(BaseEntity* ent);
	void Cull(int limit);

	int CountEnts();
	BaseEntity* GetEnt(int i);

private:

	std::vector<BaseEntity*> _Entities;
};

#endif