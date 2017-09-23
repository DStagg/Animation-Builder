#include "Utility.h"

std::string IntToString(int i)
{

	std::stringstream out;
	out << i;
	return out.str();

};


std::string FloatToString(float f)
{

	std::stringstream out;
	out << f;
	return out.str();

};

int StringToInt(std::string s)
{
	int temp;
	std::stringstream(s) >> temp;

	return temp;
};

float StringToFloat(std::string s)
{
	float temp;
	std::stringstream(s) >> temp;

	return temp;
};

float DegreeToRad(float d)
{
	float Temp = (d / 360.f) * 2.f * (float)Pi;
	return Temp;
};

float RadToDegree(float r)
{
	float TwoPi = 2.f * (float)Pi;
	float Temp = (r / TwoPi) * 360.f;
	return Temp;
};

int Random(int min, int max, bool inczero)
{
	int value = rand() % (max - min + 1) + min;

	if ((inczero == false) && (value == 0))
		return Random(min, max, inczero);
	else
		return value;
};

int RandomSign()
{
	return Random(-1, 1, false);
};

float CalcHeading(float startx, float starty, float endx, float endy)
{
	float Deg = CalcAngle(startx, starty, endx, endy);

	Deg += 90.f;

	if (Deg < 0.f)
		Deg += 360.f;
	if (Deg >= 359.999f)
		Deg = 0.f;

	return Deg;
};

float CalcAngle(float startx, float starty, float endx, float endy)
{
	return RadToDegree(atan2(endy - starty, endx - startx));
};

float Strip(float in, float factor)
{
	return floor(in * factor) / factor;
};

float FRound(float f)
{
	float dump;
	float temp = modf(f, &dump);
	if (temp >= 0.5f)
		return ceil(f);
	else
		return floor(f);
};