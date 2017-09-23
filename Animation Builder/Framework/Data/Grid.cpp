#include "Grid.h"

Grid::Grid(int w, int h, int value)
{
	Create(w, h, value);
};
Grid::~Grid()
{

};

void Grid::Create(int w, int h, int value)
{
	Resize(w, h);

	for (int x = 0; x < GetWidth(); x++)
		for (int y = 0; y < GetHeight(); y++)
			SetCell(x, y, value);
};

int Grid::GetCell(int x, int y)
{
	if (x < 0) x = 0;
	if (x >= GetWidth()) x = GetWidth() - 1;
	if (y < 0) y = 0;
	if (y >= GetHeight()) y = GetHeight() - 1;

	return _Cells[x][y];
};
void Grid::SetCell(int x, int y, int value)
{
	if (x < 0) x = 0;
	if (x >= GetWidth()) x = GetWidth() - 1;
	if (y < 0) y = 0;
	if (y >= GetHeight()) y = GetHeight() - 1;

	_Cells[x][y] = value;
};

int Grid::GetWidth()
{
	return (int)_Cells.size();
};
int Grid::GetHeight()
{
	if (GetWidth() == 0) return 0;
	return (int)_Cells[0].size();
};

void Grid::Resize(int w, int h)
{
	if (w < 1) w = 1;
	if (h < 1) h = 1;

	//	Add/Remove Columns to new Width
	if (GetWidth() < w)
	{
		std::vector<int> newCol;
		for (int y = 0; y < h; y++)
			newCol.push_back(0);
		while (GetWidth() < w)
			_Cells.push_back(newCol);
	}
	else
	{
		while (GetWidth() > w)
			_Cells.pop_back();
	}

	//	Resize Existing Columns to new Height
	while (GetHeight() > h)
	{
		for (int x = 0; x < GetWidth(); x++)
			_Cells[x].pop_back();
	}
	while (GetHeight() < h)
	{
		for (int x = 0; x < GetWidth(); x++)
			_Cells[x].push_back(0);
	}
	
};