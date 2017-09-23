#ifndef AABB_H
#define AABB_H

class AABB
{
public:

	AABB();
	AABB(int x, int y, int w, int h);	//	Defines an axis-aligned bounding box with top-left (x,y) and dimensions (w,h)
	~AABB();

	int Right();
	int Bottom();

	int _X, _Y, _Width, _Height;

	bool Contains(int x, int y);
	bool Contains(AABB box);
	bool Intersects(AABB box);
};

#endif