#pragma once
#include "Texture2dManager.h"
#include "Sprite.h"
#include "Camera.h"

#define BLACKBOARDHEIGHT		72

#define STAGE1_ROWMAP			12
#define STAGE1_COLUMNMAP		48
#define STAGE1_BOTTOMDIST		18

#define STAGE2_1_ROWMAP			12
#define STAGE2_1_COLUMNMAP		16
#define STAGE2_1_BOTTOMDIST		24

#define STAGE2_2_ROWMAP			12
#define STAGE2_2_COLUMNMAP		32
#define STAGE2_2_BOTTOMDIST		48

#define STAGE3_1_ROWMAP			12
#define STAGE3_1_COLUMNMAP		48
#define STAGE3_1_BOTTOMDIST		24

#define STAGE3_2_ROWMAP			12
#define STAGE3_2_COLUMNMAP		48
#define STAGE3_2_BOTTOMDIST		48

class Map
{
	Texture2d* tileMapTexture;	//Tileset
	Sprite* tileMapSprite;

	LPCWSTR mapFilePath;

	int ColumnMap, RowMap;	//So cot, hang cua map, Khoang cach voi day screen cua map

	int FrameWidthTexture, FrameHeightTexture;

	int TileMap[100][100];
	//So cot va hang toi da phai lon hon Screen Resolution chia cho do cao/dai cua frame tile
	//So cot va hang toi da cua Map (thay doi tuy y, Castlevania khong qua lon nen 100 is ok)
public:
	Map();
	~Map();

	void LoadMap(EntityType typeMap);
	void Load();
	//void Update(DWORD dt); co the se co map dung update
	void Draw();
};

