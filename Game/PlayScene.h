#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>

#include "Scene.h"
#include "Game.h"
#include "GameTime.h"
#include "Camera.h"
#include "Timer.h"
#include "UI.h"
#include "Map.h"
#include "Grid.h"
#include "SmallHeart.h"
#include "BigHeart.h"
#include "MoneyBags.h"
#include "YummiChickenLeg.h"
#include "UpgradeMorningStar.h"
#include "Cross.h"
#include "ItemDagger.h"
#include "ItemBoomerang.h"
#include "ItemAxe.h"
#include "ItemWaterPotion.h"
#include "ItemStopWatch.h"
#include "Hit.h"
#include "Fire.h"
#include "Score.h"
#include "Crown.h"
#include "ExtraShot.h"

#include "Player.h"
#include "Brick.h"
#include "Bat.h"
#include "Zombie.h"
#include "Torch.h"
#include "Gate.h"
#include "Stairs.h"
#include "DarkenBat.h"
#include "Knight.h"
#include "Ghost.h"
#include "Hunchman.h"
#include "Raven.h"
#include "Skeleton.h"
#include "BreakableBrick.h"
#include "Candle.h"
#include "MovingPlatform.h"

#include <iostream>
#include <fstream>

//tam thoi, co the thay the = EntityType
#define OBJECT_TYPE_BRICK				1
#define OBJECT_TYPE_TORCH				2
#define OBJECT_TYPE_GATE				3
#define OBJECT_TYPE_STAIRS				4
#define OBJECT_TYPE_DARKENBAT			5
#define OBJECT_TYPE_KNIGHT				6
#define OBJECT_TYPE_BREAKABLEBRICK		7
#define OBJECT_TYPE_CANDLE				8
#define OBJECT_TYPE_MOVING_PLATFORM		9
#define OBJECT_TYPE_HUNCHMAN			10
#define OBJECT_TYPE_RAVEN				11
#define OBJECT_TYPE_SKELETON			12

using namespace std;

#define SPAWNING_ZOMBIE_DELAY				3000
#define SPAWNING_DELAY_BETWEEN_2_ZOMBIE		450	
#define SPAWNING_BAT_DELAY					3000

#define HIT_EFFECT_CUSTOMIZED_POS			8

class PlayScene : public Scene
{
protected:
	Player* player;
	std::vector<LPGAMEENTITY> listObjects;
	std::vector<LPGAMEENTITY> listObjectsToGrid;	//Parse Object from file to this, Grid receive this list
	std::vector<LPGAMEENTITY> listObjectsFromGrid;	//temp list to transfer from Grid to listObj
	std::vector<LPGAMEEFFECT> listEffects;
	std::vector<LPGAMEITEM> listItems;
	std::vector<LPCWSTR> listSceneFilePath;
	std::vector<LPGAMEENTITY> listStairs;
	std::vector<LPGAMEENTITY> listStairsEx;
	UI* gameUI;
	GameTime* gameTime;		
	Camera* gameCamera;
	Map* gameMap;
	Grid* gameGrid;

	int idStage; 
	int mapWidth, mapHeight;
	int camMaxWidth;

	int counterZombie;
	bool isTimeToSpawnZombie;
	bool triggerSpawnZombie;
	Timer* spawningZombieTimer = new Timer(SPAWNING_ZOMBIE_DELAY);
	Timer* delaySpawningZombieTimer = new Timer(SPAWNING_DELAY_BETWEEN_2_ZOMBIE);
	bool isTimeToSpawnBat;
	bool triggerSpawnBat;
	Timer* spawningBatTimer = new Timer(SPAWNING_BAT_DELAY);
	bool triggerSpawnGhost;
	//testing Scan
	//bool isScanned;
	//Timer* scanningGameTimer = new Timer(SCANING_GAME_DELAY);
	bool triggerResetGame;

	int easterEgg_Stage2_1;	//bien dem khi pha gach stage 2-1
	int easterEgg_Stage2_2;
	int easterEgg_Stage3_2;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);

	//Get stage objects' link and tilemap resources
	void _ParseSection_SCENEFILEPATH(string line);
	void _ParseSection_TILEMAP(string line);

public:
	PlayScene();

	void LoadBaseObjects();
	void LoadBaseTextures();
	void ChooseMap(int whatStage);
	virtual void LoadSceneObjects();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	void GetObjectFromGrid();

	Effect* CreateEffect(EntityType createrType, EntityType effectType, float posX, float posY);
	Item* RandomItem(float posX, float posY);
	Item* DropItem(EntityType createrType, float posX, float posY, int idCreater = 0);
	void WeaponInteractObj(UINT i, Weapon* weapon);
	void SlayEnemies(UINT i, Weapon* weapon, int scoreGive);
	void WeaponCollision();
	void PlayerCollideItem();
	void SetSubWeaponDone(UINT i);
	bool PlayerPassingStage(float DistanceXWant, int directionGo);
	void PlayerGotGate();
	void EasterEggEvent();	//EEE
	void PlayerFailDown();
	void PlayerInSightGhost();
	void ResetGame();
	void PlayerCollideBone();
	void CountingZombie();
	void SpawnZombie();
	void SpawnBat();

	std::vector<LPGAMEENTITY> GetListStairs() { return listStairs; }
	std::vector<LPGAMEENTITY> GetListStairsEx() { return listStairsEx; }
	bool PlayerCollideStairs();
	bool PlayerCollideStairsEx();

	friend class PlayScenceKeyHandler;
};


class PlayScenceKeyHandler : public ScenceKeyHandler
{
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	PlayScenceKeyHandler(Scene *s) :ScenceKeyHandler(s) {};
};


