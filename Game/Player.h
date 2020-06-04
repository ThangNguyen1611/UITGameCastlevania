#pragma once
#include "Entity.h"
#include "MorningStar.h"
#include "Dagger.h"
#include "Boomerang.h"
#include "Axe.h"
#include "WaterPotion.h"
#include "StopWatch.h"
#include "Timer.h"
#include <map>

#define PLAYER_WALKING_SPEED_X					0.20f	//0.25
#define PLAYER_PASSING_STAGE_SPEED_X			0.035f
#define PLAYER_JUMPING_SPEED_Y					0.55f	//0.8
#define PLAYER_GRAVITY							0.002f	//0.025
#define PLAYER_DEFLECT_SPEED_X					0.105f
#define PLAYER_DEFLECT_SPEED_Y					0.3f
#define PLAYER_MAXHEALTH						16
#define PLAYER_INIT_MANA						55
#define PLAYER_INIT_LIVES						3
#define PLAYER_ON_STAIRS_SPEED_X				0.07f
#define PLAYER_ON_STAIRS_SPEED_Y				0.07f
#define PLAYER_IMMORTAL_ALPHA					150
#define PLAYER_UNSIGHT_ALPHA					50

#define PLAYER_BBOX_WIDTH						45		//60
#define PLAYER_BBOX_HEIGHT						63		//66

#define PLAYER_STATE_DIE						0
#define PLAYER_STATE_IDLE						1
#define PLAYER_STATE_WALKING					2
#define PLAYER_STATE_JUMPING					3
#define PLAYER_STATE_ATTACKING					4
#define PLAYER_STATE_HURTING					5
#define PLAYER_STATE_SITTING					6
#define PLAYER_STATE_SITTING_ATTACK				7
#define PLAYER_STATE_UPGRADING					8
#define PLAYER_STATE_SUPWEAPON_ATTACK			9
#define PLAYER_STATE_SUPWEAPON_SIT_ATTACK		10
#define PLAYER_STATE_PASSING_STAGE				11
#define PLAYER_STATE_GOING_UP_STAIRS			12
#define PLAYER_STATE_GOING_DOWN_STAIRS			13
#define PLAYER_STATE_UPSTARIS_ATTACK			14
#define PLAYER_STATE_DOWNSTAIRS_ATTACK			15

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

#define PLAYER_HURT_DURATION					600
#define PLAYER_IMMORTAL_DURATION				2000
#define PLAYER_UPGRADE_DURATION					1500
#define PLAYER_RESPAWN_DURATION					3000
#define PLAYER_TIMESTOP_DURATION				5000
#define PLAYER_INVISIBLE_DURATION				10000

class Player : public Entity
{
	int mana;
	int live;
	int score;
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
		isOnStairs,
		isOnMF,
		isTimeStop,
		isHideOnBush,		//Need ? A fan of Fekar :v
		isAttackingDouble,
		isAttackingTriple;
	float backupVx;

	bool canMoveDown;
	bool canMoveUp;
	bool cannotMoveDown;
	LPGAMEENTITY stairCollided = nullptr;
	int stairDirection;

	bool isWalkingOnStairs;
	float posWalkingOnStairs;
	int stateWalkingOnStairs;
	int directionWalkingOnStairs;

	int currentStageLiving;

	bool isGettingDouble;
	bool isGettingTriple;

	Timer* hurtingTimer = new Timer(PLAYER_HURT_DURATION);
	Timer* immortalTimer = new Timer(PLAYER_IMMORTAL_DURATION);
	//Immortal != Invincible !!!!! You may be Immortal, but you are not Invincible! - a Prince of Persia said.
	Timer* upgradeTimer = new Timer(PLAYER_UPGRADE_DURATION);
	Timer* respawningTimer = new Timer(PLAYER_RESPAWN_DURATION);
	Timer* timeStopTimer = new Timer(PLAYER_TIMESTOP_DURATION);
	Timer* invisibleTimer = new Timer(PLAYER_INVISIBLE_DURATION);

	Weapon* mainWeapon;
	Weapon* supWeapon;
	Weapon* supWeaponAtDouble;
	Weapon* supWeaponAtTriple;
	EntityType currentSupWeaponType;
public:
	Player(float posX, float posY);
	~Player();

	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEENTITY> *colliable_objects = NULL);
	void Render();
	void SetState(int state);

	int GetMana() { return mana; }
	void SetMana(int mana) { this->mana = mana; }
	void AddMana(int BonusMana) { mana += BonusMana; }

	int GetScore() { return score; }
	void AddScore(int BonusScore) { score += BonusScore; }

	int GetLive() { return live; }
	void AddLive(int BonusLive) { live += BonusLive; }

	void Attack(EntityType weaponType);
	void SupWeaponUpdate(Weapon* weapon, DWORD dt, vector<LPGAMEENTITY> *colliable_objects);	//Do khong dung list va khong muon viet lai nen viet ham nay
	void SupWeaponRender(Weapon* weapon);
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
	bool IsTimeStop() { return isTimeStop; }

	bool IsGettingDouble() { return isGettingDouble; }
	void SetGettingDouble(bool b) { isGettingDouble = b; }
	bool IsGettingTriple() { return isGettingTriple; }
	void SetGettingTriple(bool b) { isGettingTriple = b; }

	void SetOnStair(bool onStair) { isOnStairs = onStair; }
	void SetImmortal(bool immo) { isImmortaling = immo; }
	void StartHurtingTimer(){ hurtingTimer->Start(); }
	void StartImmortalingTimer(){ immortalTimer->Start(); }
	
	Weapon* GetPlayerMainWeapon() { return mainWeapon; }
	Weapon* GetPlayerSupWeapon() { return supWeapon; }
	Weapon* GetPlayerSupWeaponAtDouble() { return supWeaponAtDouble; }
	Weapon* GetPlayerSupWeaponAtTriple() { return supWeaponAtTriple; }

	void UpgradingMorningStar();

	EntityType GetPlayerSupWeaponType() { return currentSupWeaponType; }
	void SetPlayerSupWeaponType(EntityType supWeaponType);

	void ReceiveCurrentStage(int info) { currentStageLiving = info; }

	void Respawn();

	bool SimonCollideWithStair(vector<LPGAMEENTITY> *listStairs);
	void TriggerAutoWalk(float nextPos, int nextState, int nextDirection);
	void AutoWalk();
	bool GetCannotMoveDown() { return cannotMoveDown; }
	void SetCannotMoveDown(bool b) { cannotMoveDown = b; }
	int GetStairsDirectionPlayerColliding() { return stairDirection; }
	bool GetIsWalkingOnStairs() { return isWalkingOnStairs; }
	void PlayerUpStairs();
	void PlayerDownStairs();
	bool PlayerStandOnStairs();

	void StartInvisible();
	void StopInvisible();
};

