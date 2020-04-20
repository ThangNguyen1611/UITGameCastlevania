#include "Texture2dManager.h"

Texture2dManager* Texture2dManager::__instance = NULL;

Texture2dManager* Texture2dManager::GetInstance() 
{
	if (__instance == NULL) __instance = new Texture2dManager();
	return __instance;
}

Texture2dManager::Texture2dManager()
{
	LoadContent();
}

Texture2dManager::~Texture2dManager(){}

void Texture2dManager::LoadContent()
{
	//BBox
	AddTexture(EntityType::BBOX, new Texture2d("Resources/bbox.png", 1, 679, 765));

	//Player
	AddTexture(EntityType::PLAYER, new Texture2d("Resources/Simon.png", 56, 60, 66, D3DCOLOR_ARGB(255, 255, 0, 255)));

	//Scene
	AddTexture(EntityType::TITLESCENE, new Texture2d("Resources/Scene/TitleScene.png", 1, 514, 450));
	AddTexture(EntityType::TITLEBAT, new Texture2d("Resources/Scene/TitleBat.png", 15, 144, 112));
	AddTexture(EntityType::STARTTEXT, new Texture2d("Resources/Scene/StartText.png", 2, 214, 30, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::INTROSCENE, new Texture2d("Resources/Scene/IntroScene.png", 1, 512, 448));
	AddTexture(EntityType::INTROSIMON, new Texture2d("Resources/Simon.png", 56, 60, 66, D3DCOLOR_ARGB(255, 255, 0, 255)));

	//Map
	AddTexture(EntityType::MAPSTAGE1, new Texture2d("Resources/TileMap/TilesetStage1.png", 68, 32, 32, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::MAPSTAGE2_1, new Texture2d("Resources/TileMap/TilesetStage2.png", 28, 32, 32, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::MAPSTAGE2_2, new Texture2d("Resources/TileMap/TilesetStage2.png", 28, 32, 32, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::MAPSTAGE3_1, new Texture2d("Resources/TileMap/TilesetStage3.png", 60, 32, 32, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::MAPSTAGE3_2, new Texture2d("Resources/TileMap/TilesetStage3.png", 60, 32, 32, D3DCOLOR_ARGB(255, 255, 0, 255)));

	//Static Obj
	AddTexture(EntityType::BRICK, new Texture2d("Resources/Objects/Ground.png", 4, 32, 32));
	AddTexture(EntityType::TORCH, new Texture2d("Resources/Objects/Torch.png", 2, 32, 64, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::CANDLE, new Texture2d("Resources/Objects/Candle.png", 2, 16, 32, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::GATE, new Texture2d("Resources/Objects/Gate.png", 4, 48, 96, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::STAIRS, new Texture2d("Resources/Objects/Stair.png", 2, 32, 32));
	AddTexture(EntityType::BREAKABLEBRICK, new Texture2d("Resources/Objects/Ground.png", 4, 32, 32));
	AddTexture(EntityType::MOVINGPLATFORM, new Texture2d("Resources/Objects/MovingPlatform.png", 1, 64, 16, D3DCOLOR_ARGB(255, 116, 116, 116)));

	//UI
	AddTexture(EntityType::BLACKBOARD, new Texture2d("Resources/UI/BlackBoard.png", 1, 520, 80));
	AddTexture(EntityType::PLAYERHP, new Texture2d("Resources/UI/HP.png", 3, 8, 15));
	AddTexture(EntityType::TEXTS, new Texture2d("Resources/UI/Texts.png", 36, 15, 14, D3DCOLOR_ARGB(255, 255, 0, 255)));

	//Effective
	AddTexture(EntityType::FIREEFFECT, new Texture2d("Resources/Effects/Fire.png", 4, 43, 44, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::HITEFFECT, new Texture2d("Resources/Effects/Hit.png", 2, 16, 20, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::BUBBLESEFFECT, new Texture2d("Resources/Effects/Bubbles.png", 1, 1, 1, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::BRICKEXPLODEEFFECT, new Texture2d("Resources/Effects/BrickExplode.png", 2, 13, 23, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::ADDSCOREEFFECT, new Texture2d("Resources/Effects/Score.png", 8, 38, 18, D3DCOLOR_ARGB(255, 255, 0, 255)));

	//Mobs and Bosses
	AddTexture(EntityType::BAT, new Texture2d("Resources/Enemies/VampireBat.png", 4, 32, 32, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::ZOMBIE, new Texture2d("Resources/Enemies/Zombie.png", 2, 32, 64, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::DARKENBAT, new Texture2d("Resources/Enemies/DarkenBat.png", 4, 32, 32, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::KNIGHT, new Texture2d("Resources/Enemies/Knight.png", 3, 40, 80, D3DCOLOR_ARGB(255, 116, 116, 116)));
	AddTexture(EntityType::RAVEN, new Texture2d("Resources/Enemies/Raven.png", 4, 32, 32, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::HUNCHMAN, new Texture2d("Resources/Enemies/Hunchman.png", 2, 32, 32, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::GHOST, new Texture2d("Resources/Enemies/Ghost.png", 2, 32, 32, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::EAGLE, new Texture2d("Resources/Enemies/Eagle.png", 2, 32, 32, D3DCOLOR_ARGB(255, 255, 0, 255)));


	//Weapons
	AddTexture(EntityType::MORNINGSTAR, new Texture2d("Resources/Weapons/MorningStar.png", 12, 160, 68, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::DAGGER, new Texture2d("Resources/Weapons/Dagger.png", 1, 32, 18, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::BOOMERANG, new Texture2d("Resources/Weapons/Boomerang.png", 3, 28, 28, D3DCOLOR_ARGB(255, 255, 0, 255)));

	//Items
	AddTexture(EntityType::SMALLHEART, new Texture2d("Resources/Items/SmallHeart.png", 1, 16, 16, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::BIGHEART, new Texture2d("Resources/Items/BigHeart.png", 1, 24, 20, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::YUMMICHICKENLEG, new Texture2d("Resources/Items/YummiChickenLeg.png", 1, 32, 26, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::MONEYBAGS, new Texture2d("Resources/Items/MoneyBags.png", 3, 30, 30, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::UPGRADEMORNINGSTAR, new Texture2d("Resources/Items/UpgradeMS.png", 1, 32, 32, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::CRYSTALBALL, new Texture2d("Resources/Items/CrystalBall.png", 2, 28, 32, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::INVIPOTION, new Texture2d("Resources/Items/InviPotion.png", 1, 30, 37, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::STOPWATCH, new Texture2d("Resources/Items/StopWatch.png", 1, 30, 32, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::CROSS, new Texture2d("Resources/Items/Cross.png", 1, 32, 32, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::AXE, new Texture2d("Resources/Items/Axe.png", 1, 30, 28, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::ITEMBOOMERANG, new Texture2d("Resources/Items/Boomerang.png", 1, 30, 28, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::WATERPOTION, new Texture2d("Resources/Items/WaterPotion.png", 1, 32, 32, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::ITEMDAGGER, new Texture2d("Resources/Items/Dagger.png", 1, 32, 18, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::CROWN, new Texture2d("Resources/Items/Crown.png", 2, 32, 32, D3DCOLOR_ARGB(255, 255, 0, 255)));
	AddTexture(EntityType::ITEMEXTRASHOT, new Texture2d("Resources/Items/ExtraShot.png", 2, 32, 32, D3DCOLOR_ARGB(255, 255, 0, 255)));

}