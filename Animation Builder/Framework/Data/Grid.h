#ifndef GRID_H
#define GRID_H

#include <vector>

class Grid
{
public:

	Grid(int w = 1, int h = 1, int value = 0);
	~Grid();

	void Create(int w, int h, int value);

	int GetCell(int x, int y);
	void SetCell(int x, int y, int value);

	int GetWidth();
	int GetHeight();
	void Resize(int w, int h);

private:

	std::vector<std::vector<int>> _Cells;
	
};

#endif
