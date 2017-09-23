#ifndef PAIR_H
#define PAIR_H

template <class T>
struct Pair
{
	Pair()
	{
		Set(T(), T());
	};
	Pair(T x, T y)
	{
		Set(x, y);
	};

	void Set(T x, T y)
	{
		_X = x;
		_Y = y;
	};

	T Size()
	{
		return sqrt((_X * _X) + (_Y * _Y));
	};

	T Heading()
	{
		float Deg = RadToDegree(atan2(_Y, _X));

		Deg += 90.f;

		if (Deg < 0.f)
			Deg += 360.f;
		if (Deg >= 359.999f)
			Deg = 0.f;

		return Deg;
	};

	T _X;
	T _Y;
};

typedef Pair<float> PairFloat;
typedef Pair<int> PairInt;

#endif