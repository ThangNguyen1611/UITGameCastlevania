#pragma once
#include "define.h"
#include "Entity.h"
#include "Camera.h"
#include <vector>
using namespace std;

#define GRID_CELL_WIDTH		(SCREEN_WIDTH / 2.0f)
#define GRID_CELL_HEIGHT	(SCREEN_HEIGHT / 2.0f)

class Grid
{
	int mapWidth, mapHeight;

	vector<vector<vector<LPGAMEENTITY>>> cells;
public:
	Grid(int mapWidth, int mapHeight);
	~Grid();

	void ClearGrid(int Row, int Col);
	void ResetGrid(vector<LPGAMEENTITY> listObj);
	void PushObjectIntoGrid(vector<LPGAMEENTITY> listObj);
	void AddToGrid(LPGAMEENTITY Obj, int col, int row);
	void GetObjectFromGrid(vector<LPGAMEENTITY> &listObj);
};

