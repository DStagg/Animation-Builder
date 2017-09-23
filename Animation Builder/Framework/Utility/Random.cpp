#include "Random.h"

Random* Random::_Instance = 0;
int Random::_Seed = 0;

Random::Random()
{
	
};
Random::~Random()
{
};

Random* Random::R()
{
	if (_Instance == 0)
		_Instance = new Random();
	return _Instance;
};

int Random::Generate(int min, int max)
{
	return (rand() % max) + min;
};

void Random::Seed(int s)
{
	_Seed = s;
	srand(_Seed);
};
void Random::TimeSeed()
{
	Seed((int)time(NULL));
};
int Random::GetSeed()
{
	return _Seed;
};
