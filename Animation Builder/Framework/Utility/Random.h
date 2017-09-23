#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <time.h>

class Random
{
public:

	~Random();

	static Random* R();

	static int Generate(int min, int max);

	static void Seed(int s);
	static void TimeSeed();
	static int GetSeed();

private:

	Random();

	static int _Seed;
	static Random* _Instance;
};

#endif