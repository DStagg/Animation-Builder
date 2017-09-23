#ifndef UTILITY_H
#define UTILITY_H

#define Pi 3.14159265358979323846264f

#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>

std::string IntToString(int i);

std::string FloatToString(float f);

int StringToInt(std::string s);

float StringToFloat(std::string s);

float DegreeToRad(float d);

float RadToDegree(float r);

int Random(int min = 0, int max = RAND_MAX, bool inczero = true);

int RandomSign();

float CalcHeading(float startx, float starty, float endx, float endy);

float CalcAngle(float startx, float starty, float endx, float endy);

float Strip(float in, float factor = 100.f);

float FRound(float f);

template <class T>
bool IsOdd(T a)
{
	if ((((int)a) % 2) == 0)
		return false;
	return true;
};

template <class T>
bool IsEven(T a)
{
	return !IsOdd(a);
};

template <class T>
T Min(T a, T b)
{
	if (a <= b)
		return a;
	else
		return b;
};

template <class T>
T Max(T a, T b)
{
	if (a >= b)
		return a;
	else
		return b;
};

template <class T>
int Sign(T a)
{
	if (a < 0)
		return -1;
	if (a > 0)
		return 1;

	return 0;
};

template <class T>
T Abs(T a)
{
	if (a < 0)
		return -a;
	return a;
};

#endif