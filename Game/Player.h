#pragma once

#include "Entity.h"
#include "MorningStar.h"
#include "Dagger.h"
#include "Boomerang.h"
#include "Timer.h"
#include <map>

#define PLAYER_WALKING_SPEED					0.20f	//0.25
#define PLAYER_PASSING_STAGE_SPEED				0.035f
#define PLAYER_JUMP_SPEED_Y						0.55f	//0.8
#define PLAYER_GRAVITY							0.002f	//0.025
#define PLAYER_DEFLECT_SPEED_X					0.8f
#define PLAYER_DEFLECT_SPEED_Y					0.3f
#define PLAYER_MAXHEALTH						16
#define PLAYER_ON_STAIRS_SPEED_X				0.05f
#define PLAYER_ON_STAIRS_SPEED_Y				0.05f

#define PLAYER_BBOX_WIDTH						45		//60
#define PLAYER_BBOX_HEIGHT						63		//66

#define PLAYER_STATE_DIE						-1
#define PLAYER_STATE_IDLE						0
#define PLAYER_STATE_WALKING_RIGHT				100
#define PLAYER_STATE_WALKING_LEFT				200
#define PLAYER_STATE_JUMP						300
#define PLAYER_STATE_ATTACK						400
#define PLAYER_STATE_SITTING					500
#define PLAYER_STATE_HURTING					600
#define PLAYER_STATE_UPGRADING					700
#define PLAYER_STATE_SUPWEAPON_ATTACK			800
#define PLAYER_STATE_PASSING_STAGE				900
#define PLAYER_STATE_GOING_UP_STAIRS			1000
#define PLAYER_STATE_GOING_DOWN_STAIRS			1100

#define PLAYER_ANI_DIE							28
#define PLAYER_ANI_IDLE							0
#define PLAYER_ANI_WALKING_BEGIN				1
#define PLAYER_ANI_WALKING_END					3
#define PLAYER_ANI_JUMPING						4
#define PLAYER_ANI_ATTACK_BEGIN					5
#define PLAYER_ANI_ATTACK_END					7
#define PLAYER_ANI_HURTING						8
#define PLAYER_ANI_SITTING						29
#define PLAYER_ANI_SITTING_ATTACK_BEGIN			15
#define PLAYER_ANI_SITTING_ATTACK_END			17
#define PLAYER_ANI_UPGRADING_BEGIN				24
#define PLAYER_ANI_UPGRADING_END				27	
#define PLAYER_ANI_GOING_UP_STAIRS_BEGIN		12
#define PLAYER_ANI_GOING_UP_STAIRS_END			13
#define PLAYER_ANI_GOING_DOWN_STAIRS_BEGIN		10
#define PLAYER_ANI_GOING_DOWN_STAIRS_END		11
#define PLAYER_ANI_ATTACK_UP_STAIRS_BEGIN		21
#define PLAYER_ANI_ATTACK_UP_STAIRS_END			23
#define PLAYER_ANI_ATTACK_DOWN_STAIRS_BEGIN		18
#define PLAYER_ANI_ATTACK_DOWN_STAIRS_END		20

#define PLAYER_ATTACKING_DELAY					110
#define PLAYER_HURTING_DELAY					600
#define PLAYER_IMMORTAL_TIMECOUNTER				1200
#define PLAYER_UPGRADING_DELAY					100
#define PLAYER_UPGRADING_TIMECOUNTER			1200
#define PLAYER_RESPAWNING_TIMECOUNTER			2400

class Player : public Entity
{
	bool isWalking,
		isJumping,
		isAllowJump,
		isAttacking,
		isSitting,
		isHurting,
		isImmortaling,		//not a state, a sub-state from hurt
		isUpgrading,
		isPassingStage,
		isRespawning,
		isOnStairs;

	bool triggerAuto;	//trigger make player cant use input
	float targetPosX;
	float targetPosY;
	float processAutoSpeedX;
	float processAutoSpeedY;

	int directionY;	//1 = up, -1 = down

	int currentStageLiving;

	Timer* hurtingTimer = new Timer(PLAYER_HURTING_DELAY);
	Timer* immortalTimer = new Timer(PLAYER_IMMORTAL_TIMECOUNTER);
	//Immortal != Invincible !!!!! You may be Immortal, but you are not Invincible! - a Prince of Persia said.
	Timer* upgradeTimer = new Timer(PLAYER_UPGRADING_TIMECOUNTER);
	Timer* respawningTimer = new Timer(PLAYER_RESPAWNING_TIMECOUNTER);

	Weapon* mainWeapon;
	Weapon* supWeapon;
	EntityType currentSupWeaponType;
public:
	Player(float posX, float posY);
	~Player();

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEENTITY> *colliable_objects = NULL);
	void Render();
	void SetState(int state);

	void Attack(EntityType weaponType);	
	bool IsWalking() { return isWalking; }
	bool IsJumping() { return isJumping; }
	bool IsAllowJump() { return isAllowJump; }
	bool IsAttacking() { return isAttacking; }
	bool IsSitting() { return isSitting; }
	bool IsHurting() { return isHurting; }
	bool IsImmortaling() { return isImmortaling; }
	bool IsUpgrading() { return isUpgrading; }
	bool IsPassingStage() { return isPassingStage; }
	bool IsRespawning() { return isRespawning; }
	bool IsOnStairs() { return isOnStairs; }

	bool IsProcessingAuto() { return triggerAuto; }

	int GetDirectionY() { return directionY; }
	void SetOnStair(bool onStair) { isOnStairs = onStair; }
	
	Weapon* GetPlayerMainWeapon() { return mainWeapon; }
	Weapon* GetPlayerSupWeapon() { return supWeapon; }

	void UpgradingMorningStar();

	EntityType GetPlayerSupWeaponType() { return currentSupWeaponType; }
	void SetPlayerSupWeaponType(EntityType supWeaponType);

	void ReceiveCurrentStage(int info) { currentStageLiving = info; }

	void Respawn();

	void KnownTargetMovement(float targetX, float targetY, float speedX, float speedY, int directionX = 1, int directionY = 1);
	//1 co che khong duoc dieu khien
	//target Pos nen la 1 cap vector de khi su dung khong xay ra nhung loi lien quan nhap lieu
};

