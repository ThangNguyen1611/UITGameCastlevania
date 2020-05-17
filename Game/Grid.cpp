#include "Grid.h"

Grid::Grid(int mapWidth, int mapHeight)
{
	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;

	int totalCol = this->mapWidth / GRID_CELL_WIDTH;
	int totalRow = this->mapHeight / GRID_CELL_HEIGHT;

	cells.resize(totalRow);
	for (int i = 0; i < totalRow; i++)
		cells[i].resize(totalCol);

	ClearGrid(totalRow, totalCol);
}

Grid::~Grid(){}

void Grid::ClearGrid(int Row, int Col)
{
	for (int i = 0; i < Row; i++)
		for (int j = 0; j < Col; j++)
			cells[i][j].clear();
}

void Grid::ResetGrid(vector<LPGAMEENTITY> listObj)
{
	ClearGrid((int)this->mapHeight / GRID_CELL_HEIGHT, (int)this->mapWidth / GRID_CELL_WIDTH);

	PushObjectIntoGrid(listObj);
}

void Grid::PushObjectIntoGrid(vector<LPGAMEENTITY> listObj)
{
	for (int i = 0; i < listObj.size(); i++)
	{
		int row = (int)(listObj[i]->GetPosY() / GRID_CELL_HEIGHT);
		int col = (int)(listObj[i]->GetPosX() / GRID_CELL_WIDTH);

		if (listObj[i]->GetHealth() > 0)
			cells[row][col].push_back(listObj[i]);
	}
}

void Grid::GetObjectFromGrid(vector<LPGAMEENTITY> &listObj)
{
	int firstCol = (int)(Camera::GetInstance()->GetCamPosX() / GRID_CELL_WIDTH);
	int lastCol = ceil((Camera::GetInstance()->GetCamPosX() + SCREEN_WIDTH) / GRID_CELL_WIDTH);

	int totalRow = this->mapHeight / GRID_CELL_HEIGHT;

	for (int i = 0; i < totalRow; i++)
		for (int j = firstCol; j < lastCol; j++)
			for (int k = 0; k < cells[i][j].size(); k++)
				listObj.push_back(cells[i][j][k]);
}