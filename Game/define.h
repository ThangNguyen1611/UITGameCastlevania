#pragma once

#include <Windows.h>  
#include <d3d9.h>
#include <d3dx9.h>
#include <map>
#include "debug.h" 

#include <fstream> 
#include <string>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <iomanip>
#include <vector>
#include <iostream>

#define WIN_NAME L"NewbieGame"
#define WIN_TITLE L"NewbieGame"

#define BGColor D3DCOLOR_XRGB(0,0,0)
#define SCREEN_WIDTH 525	//530
#define SCREEN_HEIGHT 490	//480

#define MaxFrameRate 100	//default Frame Rate is the truth

#define SCENEGAME_GAMETIMEMAX		300

#define DIRECTINPUT_VERSION 0x0800
#define KEYBOARD_BUFFER_SIZE 1024

#define MAX_SCENE_LINE 1024

#define STAGE_1						1
#define STAGE_2_1					2
#define STAGE_2_2					3
#define STAGE_3_1					4
#define STAGE_3_2					5

#define STAGE_1_MAX_WIDTH			1250
#define STAGE_2_1_MAX_WIDTH			262
#define STAGE_2_2_MAX_WIDTH			776
#define STAGE_3_1_MAX_WIDTH			1282
#define STAGE_3_2_MAX_WIDTH			1282

#define SCENE_SECTION_UNKNOWN		-1
#define SCENE_SECTION_OBJECTS		1


//Nen define thanh nhieu lop type
//Vd Zombie thuoc EntityType, EnemyType
enum EntityType
{
	NONE = -1,

	BBOX = 0,

	PLAYER = 1,

	BRICK = 2,

	BAT = 3,

	ZOMBIE = 4,

	MORNINGSTAR = 5,

	PLAYERHP = 6,

	SMALLHEART = 7,

	BIGHEART = 8,

	YUMMICHICKENLEG = 9,

	MONEYBAGS = 10,

	MONEYBAGRED = 11,

	MONEYBAGWHITE = 12,

	MONEYBAGBLUE = 13,

	UPGRADEMORNINGSTAR = 14,

	CRYSTALBALL = 15,

	INVIPOTION = 16,

	ITEMDAGGER = 17,

	STOPWATCH = 18,

	CROSS = 19,

	AXE = 20,

	BOOMERANG = 21,

	WATERPOTION = 22,

	TORCH = 23,

	CANDLE = 24,

	TEXTS = 25,

	BLACKBOARD = 26,

	FIREEFFECT = 27,

	HITEFFECT = 28,

	BUBBLESEFFECT = 29,

	BRICKEXPLODEEFFECT = 30,

	ADDSCOREEFFECT = 31,

	DAGGER = 32,

	GATE = 33,

	TITLESCENE = 34,

	TITLEBAT = 35,

	STARTTEXT = 36,
	
	INTROSCENE = 37,

	INTROSIMON = 38,

	PLAYSCENE = 39,

	MAPSTAGE1 = 40,

	MAPSTAGE2_1 = 41,

	MAPSTAGE2_2 = 42,

	STAIRS = 43,

	DARKENBAT = 44,

	KNIGHT = 45,

	GHOST = 46,

	RAVEN = 47,

	HUNCHMAN = 48,

	EAGLE = 49,

	BREAKABLEBRICK = 50,

	CROWN = 51,

	ITEMEXTRASHOT = 52,

	MOVINGPLATFORM = 53,

	MAPSTAGE3_1 = 54,

	MAPSTAGE3_2 = 55,

	ITEMBOOMERANG = 56
};

class define
{
};

