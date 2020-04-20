#include "Map.h"

Map::Map(){}	//Khong tao texture, sprite o day vi dung type map o LoadMap se tien loi hoi

Map::~Map(){}

void Map::LoadMap(EntityType typeMap)
{
	tileMapTexture = Texture2dManager::GetInstance()->GetTexture(typeMap);
	tileMapSprite = new Sprite(tileMapTexture, MaxFrameRate);

	switch (typeMap)
	{
	case MAPSTAGE1:
	{
		mapFilePath = ToLPCWSTR("Resources/TileMap/TilesetStage1Text.txt");
		RowMap = STAGE1_ROWMAP;
		ColumnMap = STAGE1_COLUMNMAP;
		Load();
		break; 
	}
	case MAPSTAGE2_1:
	{
		mapFilePath = ToLPCWSTR("Resources/TileMap/TilesetStage2-1Text.txt");
		RowMap = STAGE2_1_ROWMAP;
		ColumnMap = STAGE2_1_COLUMNMAP;
		Load();
		break;
	}
	case MAPSTAGE2_2:
	{
		mapFilePath = ToLPCWSTR("Resources/TileMap/TilesetStage2-2Text.txt");
		RowMap = STAGE2_2_ROWMAP;
		ColumnMap = STAGE2_2_COLUMNMAP;
		Load();
		break;
	}
	case MAPSTAGE3_1:
	{
		mapFilePath = ToLPCWSTR("Resources/TileMap/TilesetStage3-1Text.txt");
		RowMap = STAGE3_1_ROWMAP;
		ColumnMap = STAGE3_1_COLUMNMAP;
		Load();
		break;
	}
	case MAPSTAGE3_2:
	{
		mapFilePath = ToLPCWSTR("Resources/TileMap/TilesetStage3-2Text.txt");
		RowMap = STAGE3_2_ROWMAP;
		ColumnMap = STAGE3_2_COLUMNMAP;
		Load();
		break;
	}
	default:
		break;
	}
	FrameWidthTexture = tileMapTexture->getFrameWidth();
	FrameHeightTexture = tileMapTexture->getFrameHeight();
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

			tileMapSprite->Draw1Frame(TileMap[i][j], tileMapPosX, tileMapPosY);
		}
	}
}