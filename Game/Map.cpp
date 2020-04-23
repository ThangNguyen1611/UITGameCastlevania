#include "Map.h"

Map::Map(){}	

Map::~Map(){}

void Map::LoadMap(int id,
	LPCWSTR mapFilePath,
	int RowMap,
	int ColumnMap,
	LPCWSTR mapFileTexture,
	int RowTile,
	int ColumnTile,
	int TileFrameWidth,
	int TileFrameHeight)
{
	idMap = id;
	this->mapFilePath = mapFilePath;
	this->RowMap = RowMap;
	this->ColumnMap = ColumnMap;

	CTextures * mapTexture = CTextures::GetInstance();
	mapTexture->Add(idMap, mapFileTexture, D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 tex = mapTexture->Get(idMap);

	int TilesetRow = RowTile;
	int TilesetColumn = ColumnTile;

	FrameWidthTexture = TileFrameWidth;
	FrameHeightTexture = TileFrameHeight;

	int idSpriteIns = 0;
	for (UINT i = 0; i < TilesetRow; i++)
	{
		for (UINT j = 0; j < TilesetColumn; j++)
		{
			int idSprite = idMap + idSpriteIns;
			tileMapSprite->Add(idSprite, FrameWidthTexture * j, FrameHeightTexture * i, FrameWidthTexture * (j + 1), FrameHeightTexture * (i + 1), tex);
			idSpriteIns++;
		}
	}

	Load();
}

void Map::Load()
{
	DebugOut(L"[INFO] Start loading map resources from : %s \n", mapFilePath);

	ifstream f(mapFilePath, ios::in);

	for (int i = 0; i < RowMap; i++)
	{
		for (int j = 0; j < ColumnMap; j++)
		{
			f >> TileMap[i][j];
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading map resources %s\n", mapFilePath);

}

void Map::Draw()
{
	int RowScreen = SCREEN_HEIGHT / FrameHeightTexture;

	//Tinh trong tam ve la tu tam nen posX, posY co bien doi toa do ve tam
	float originX = FrameWidthTexture / 2;
	float originY = FrameHeightTexture / 2;

	//Cot dau tien cua tile, camera de duy tri tinh thuc te' trong game 
	//camera o dau game co pos = 0, di chuyen theo truc ngang thi cameraPosX thay doi se tang firstCol theo frame tilemap mong muon
	int firstColumn = (int)Camera::GetInstance()->GetCamPosX() / FrameWidthTexture;
	int lastColumn = firstColumn + SCREEN_WIDTH / FrameWidthTexture;

	for (UINT i = 0; i < RowScreen; i++)	//chay tung totalRow tu tren xuong
	{
		for (UINT j = firstColumn; j <= lastColumn; j++)	//chay tung totalColumn tu trai qua
		{
			//pos cua 1 vien tile
			//FrameWidth * (j - firstCol) de xac dinh vien tile can ve~ trong file tileset.text
			//CameraPosX de dat vi tri camera o ngay giua 
			//Do lech CameraPosX % FrameWidth de tinh so du cua phan thua` phia sau tung tile 
			//(vi firstCol la int nen se co 1 doan du* o giua thisColumn va nextColumn, day la de can bang dieu do)
			float tileMapPosX = (float)FrameWidthTexture * (j - firstColumn) + Camera::GetInstance()->GetCamPosX() - (float)((int)Camera::GetInstance()->GetCamPosX() % FrameWidthTexture) + originX;
			float tileMapPosY = (float)FrameHeightTexture * i + BLACKBOARDHEIGHT + originY ;

			tileMapSprite->Get(TileMap[i][j] + idMap)->Draw(-1, tileMapPosX, tileMapPosY);
		}
	}
}