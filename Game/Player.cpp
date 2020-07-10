#include "Player.h"
#include "Stairs.h"

Player::Player(float posX, float posY) 
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_PLAYER));
	tag = EntityType::PLAYER;
	this->posX = posX;
	this->posY = posY;
	direction = 1;
	currentStageLiving = 1;

	this->SetState(PLAYER_STATE_IDLE);

	health = PLAYER_MAXHEALTH;
	mana = PLAYER_INIT_MANA;
	score = 0;
	live = PLAYER_INIT_LIVES;
	isDead = false;
	isWalking = false;
	isJumping = false;
	isAllowJump = true;
	isAttacking = false;
	isSitting = false;
	isHurting = false;
	isImmortaling = false;
	isPassingStage = false;
	isRespawning = false;
	isOnStairs = false;
	isAttackingDouble = false;

	mainWeapon = new MorningStar();		//Simon's main/basic weapon is MorningStar
	supWeapon = NULL;
	supWeaponAtDouble = NULL;
	supWeaponAtTriple = NULL;
	currentSupWeaponType = EntityType::NONE;		//	non ((:
}

Player::~Player(){}

void Player::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{	
	if ((health <= 0 || posY > BOTTOM_SCREEN) && !isRespawning)
	{
		live -= 1;
		SetState(PLAYER_STATE_DIE);
		if (live <= 0)
		{
			isDead = true;
		}
		respawningTimer->Start();
		isRespawning = true;
		immortalTimer->Start();
		isImmortaling = true;
	}

	if (!isWalking && !isJumping && !isOnMF && !isOnStairs && !isHurting)	//Attack tren mat dat thi dung yen, attack khi dang jump thi di chuyen duoc
	{
		vX = 0;
		//explain: state_walking: jump false (collision with brick), transfer to state_attack: walking false too -> vX = 0
		//		   state_jumping: jump true (until collision with brick) -> vX != 0
	}

#pragma region Timer
	if (isHurting && hurtingTimer->IsTimeUp()) 
	{
		if(!isRespawning)	//1 bug khi bi hurt -> respawn se duoc idle som hon du kien
			SetState(PLAYER_STATE_IDLE);
		isHurting = false;
		hurtingTimer->Reset();
	}
	if (isImmortaling && immortalTimer->IsTimeUp()) 
	{
		isImmortaling = false;
		immortalTimer->Reset();
	}
	if (isUpgrading && upgradeTimer->IsTimeUp()) 
	{
		if (!isRespawning)
			SetState(PLAYER_STATE_IDLE);
		isUpgrading = false;
		upgradeTimer->Reset();
	}
	if (isRespawning && respawningTimer->IsTimeUp())
	{
		Respawn();
		isRespawning = false;
		respawningTimer->Reset();
	}
	if (isTimeStop && timeStopTimer->IsTimeUp())
	{
		isTimeStop = false;
		timeStopTimer->Reset();
	}
	if (unsighted && invisibleTimer->IsTimeUp() && !isHideOnBush)
	{
		unsighted = false;
		invisibleTimer->Reset();
	}
	if (isAttackingDouble && supWeaponAtDouble->GetIsDone())	//WeaponAtDouble phai Done thi isAttackingDouble moi duoc reset
	{
		isAttackingDouble = false;
	}
	if (isAttackingTriple && supWeaponAtTriple->GetIsDone())
	{
		isAttackingTriple = false;
	}
#pragma endregion

	if (animationSet->at(PLAYER_STATE_SUPWEAPON_ATTACK)->GetCurrentFrame() == 0 || animationSet->at(PLAYER_STATE_SUPWEAPON_SIT_ATTACK)->GetCurrentFrame() == 0)
	{
		if (supWeapon != NULL)
		{
			if (supWeapon->GetType() == EntityType::DAGGER || 
				supWeapon->GetType() == EntityType::BOOMERANG || 
				supWeapon->GetType() == EntityType::AXE ||
				supWeapon->GetType() == EntityType::WATERPOTION)
			{
				supWeapon->ResetDelay();
			}
		}
		if (supWeaponAtDouble != NULL)
		{
			if (supWeaponAtDouble->GetType() == EntityType::DAGGER ||
				supWeaponAtDouble->GetType() == EntityType::BOOMERANG ||
				supWeaponAtDouble->GetType() == EntityType::AXE ||
				supWeaponAtDouble->GetType() == EntityType::WATERPOTION)
			{
				supWeaponAtDouble->ResetDelay();
			}
		}
		if (supWeaponAtTriple != NULL)
		{
			if (supWeaponAtTriple->GetType() == EntityType::DAGGER ||
				supWeaponAtTriple->GetType() == EntityType::BOOMERANG ||
				supWeaponAtTriple->GetType() == EntityType::AXE ||
				supWeaponAtTriple->GetType() == EntityType::WATERPOTION)
			{
				supWeaponAtTriple->ResetDelay();
			}
		}
	}

	if ((state == PLAYER_STATE_ATTACKING && animationSet->at(PLAYER_STATE_ATTACKING)->IsRenderOver()) ||
		(state == PLAYER_STATE_SUPWEAPON_ATTACK && animationSet->at(PLAYER_STATE_SUPWEAPON_ATTACK)->IsRenderOver()) ||
		(state == PLAYER_STATE_SITTING_ATTACK && animationSet->at(PLAYER_STATE_SITTING_ATTACK)->IsRenderOver()) ||
		(state == PLAYER_STATE_SUPWEAPON_SIT_ATTACK && animationSet->at(PLAYER_STATE_SUPWEAPON_SIT_ATTACK)->IsRenderOver()) ||
		(state == PLAYER_STATE_UPSTARIS_ATTACK && animationSet->at(PLAYER_STATE_UPSTARIS_ATTACK)->IsRenderOver()) ||
		(state == PLAYER_STATE_DOWNSTAIRS_ATTACK && animationSet->at(PLAYER_STATE_DOWNSTAIRS_ATTACK)->IsRenderOver()))
	{
		isAttacking = false;
	}

	if (!isAttacking)
	{
		if (isJumping)
			SetState(PLAYER_STATE_JUMPING);
	}
	

	Entity::Update(dt);

	// simple fall down
	if (!isOnStairs && !isWalkingOnStairs && !isRespawning) //Khi chet se reload stage -> mat brick -> tat trong luc de khong bi xet' chet 2 lan
	{
		vY += PLAYER_GRAVITY * dt;
	}

	if (isWalkingOnStairs)
		AutoWalk();

	if (posX <= 15)	//Not go out
		posX = 15;

#pragma region Collide Logic
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	vector<LPGAMEENTITY> listObjMayCollide;			//Khong xet va cham voi torch
	vector<LPGAMEENTITY> listBush;
	coEvents.clear();
	listObjMayCollide.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (coObjects->at(i)->GetType() != EntityType::TORCH &&
			coObjects->at(i)->GetType() != EntityType::STAIRS &&
			coObjects->at(i)->GetType() != EntityType::CANDLE&&
			coObjects->at(i)->GetType() != EntityType::BUSH)
			listObjMayCollide.push_back(coObjects->at(i));
		if (coObjects->at(i)->GetType() == EntityType::BUSH)
			listBush.push_back(coObjects->at(i));
	}

	for (UINT i = 0; i < listBush.size(); i++)
	{
		if (IsCollidingObject(listBush[i]))
		{
			StartInvisible();
			invisibleTimer->AddToTimer(PLAYER_INVISIBLE_DURATION - 1000);	//Khi ra khoi bush thi se co 1s tang hinh
			isHideOnBush = true;
		}
		else
		{
			isHideOnBush = false;
		}
	}

	CalcPotentialCollisions(&listObjMayCollide, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0 && !isWalkingOnStairs)
	{
		posX += dx;
		posY += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		if (!isWalkingOnStairs)
		{
			posX += min_tx * dx + nx * 0.4f;
			if (!isImmortaling && !unsighted && !isHideOnBush)
				posY += min_ty * dy + ny * 0.0001f;
		}
		
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (e->obj->GetType() == EntityType::BRICK || e->obj->GetType() == EntityType::BREAKABLEBRICK)
			{
				if (e->ny != 0)
				{
					if (e->ny == -1 && !isHurting)	
					{
						vY = 0;

						if (isJumping)
						{
							isJumping = false;
							isAllowJump = true;
						}
					}
					else if (e->ny == 1)
					{
						posY += dy;
					}
					if (nx != 0 && !isHurting) vX = 0;	//Chong leo tuong :D
					if (ny == -1 && !isHurting) vY = 0;	//Cham dat -> tat Gravity
				}
				if (state == PLAYER_STATE_GOING_UP_STAIRS || state == PLAYER_STATE_GOING_DOWN_STAIRS)
				{
					if (nx != 0) posX -= nx * 0.4f;
				}
			}
			
			if (!isImmortaling && !unsighted && !isHideOnBush) 
			{
				if (e->obj->GetType() == EntityType::BAT || 
					e->obj->GetType() == EntityType::DARKENBAT ||
					e->obj->GetType() == EntityType::ZOMBIE ||
					e->obj->GetType() == EntityType::KNIGHT ||
					e->obj->GetType() == EntityType::HUNCHMAN ||
					e->obj->GetType() == EntityType::GHOST ||
					e->obj->GetType() == EntityType::RAVEN ||
					e->obj->GetType() == EntityType::SKELETON ||
					e->obj->GetType() == EntityType::TLEBAT)
				{
					if (e->nx != 0 || e->ny != 0)
					{
						if (!e->obj->IsDeadYet())
						{
							this->AddHealth(-3);
							hurtingTimer->Start();
							immortalTimer->Start();
							isImmortaling = true;
							SetState(PLAYER_STATE_HURTING);
							if (e->obj->GetType() == EntityType::BAT ||
								e->obj->GetType() == EntityType::DARKENBAT ||
								e->obj->GetType() == EntityType::RAVEN)
							{
								e->obj->AddHealth(-e->obj->GetHealth());
							}
						}
					}
				}
			}

			if (currentStageLiving == STAGE_2_2)	//little cheat
			{
				if (e->obj->GetType() == EntityType::MOVINGPLATFORM)
				{
					if (e->ny < 0)
					{
						if (!isOnMF)
							backupVx = vX;
						isOnMF = true;
						vX = e->obj->GetVx();
						if (ny == -1)
						{
							vY = 0.1f;
							dy = vY * dt;

							if (isJumping)
							{
								isJumping = false;
								isAllowJump = true;
								isHurting = false;
							}
						}
						if (nx != 0) vX = 0;
						if (ny != 0) vY = 0;
						if (nx != 0 && ny != 0)
						{
							vX = 0;
							vY = 0;
							isHurting = false;
						}
					}
				}
				else
				{
					isOnMF = false;
					vX = backupVx;
				}
			}
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	
#pragma endregion

	if (!mainWeapon->GetIsDone())
	{
		mainWeapon->SetPosition(posX, posY);				//Update pos per player::update
		mainWeapon->ArticulatedPlayerPos(isSitting);		//Fixing weapon pos
		mainWeapon->Update(dt, coObjects);
	}
	SupWeaponUpdate(supWeapon, dt, coObjects);
	SupWeaponUpdate(supWeaponAtDouble, dt, coObjects);
	SupWeaponUpdate(supWeaponAtTriple, dt, coObjects);
}

void Player::Render()
{
	int alpha = ENTITY_ALPHA_RENDER;
	if (isImmortaling && rand() % 2 == 1)
		alpha = PLAYER_IMMORTAL_ALPHA;
	if (unsighted)
		alpha = PLAYER_UNSIGHT_ALPHA;

	animationSet->at(state)->Render(direction, posX, posY, alpha);

	if (!mainWeapon->GetIsDone())
	{
		mainWeapon->Render();
	}
	SupWeaponRender(supWeapon);
	SupWeaponRender(supWeaponAtDouble);
	SupWeaponRender(supWeaponAtTriple);

	RenderBoundingBox();
}

void Player::SetState(int state)
{
	Entity::SetState(state);
	switch (state)
	{
	case PLAYER_STATE_DIE:	
		//isDead = true;
		vX = 0;
		vY = 0;
		break;
	case PLAYER_STATE_IDLE:
		isWalking = false;
		isSitting = false;
		isAttacking = false;
		isAllowJump = true;
		isPassingStage = false;		//set simon not blocking
		isOnStairs = false;
		cannotMoveDown = true;
		break;
	case PLAYER_STATE_WALKING:
		isWalking = true;
		isOnStairs = false;
		cannotMoveDown = true;
		vX = PLAYER_WALKING_SPEED_X * direction;
		break;
	case PLAYER_STATE_GOING_UP_STAIRS:
		vX = PLAYER_ON_STAIRS_SPEED_X * direction;
		vY = -PLAYER_ON_STAIRS_SPEED_Y;
		isOnStairs = true;
		animationSet->at(state)->ResetCurrentFrame();
		animationSet->at(state)->StartAnimation();
		break;
	case PLAYER_STATE_GOING_DOWN_STAIRS:
		vX = PLAYER_ON_STAIRS_SPEED_X * direction;
		vY = PLAYER_ON_STAIRS_SPEED_Y;
		isOnStairs = true;
		animationSet->at(state)->ResetCurrentFrame();
		animationSet->at(state)->StartAnimation();
		break;
	case PLAYER_STATE_UPSTARIS_ATTACK:
		animationSet->at(state)->ResetCurrentFrame();
		animationSet->at(state)->StartAnimation();
		Attack(EntityType::MORNINGSTAR);
		isWalking = false;
		break;
	case PLAYER_STATE_DOWNSTAIRS_ATTACK:
		animationSet->at(state)->ResetCurrentFrame();
		animationSet->at(state)->StartAnimation();
		Attack(EntityType::MORNINGSTAR);
		isWalking = false;
		break;
	case PLAYER_STATE_JUMPING:
		if (!isAllowJump)
			return;
		if (vX != PLAYER_WALKING_SPEED_X * direction)	//MovingFlatform
			vX = 0;
		isJumping = true;
		isAllowJump = false;
		isOnStairs = false;
		vY = -PLAYER_JUMPING_SPEED_Y;
		break;
	case PLAYER_STATE_ATTACKING:
		animationSet->at(state)->ResetCurrentFrame();
		animationSet->at(state)->StartAnimation();
		Attack(EntityType::MORNINGSTAR);
		isWalking = false;
		isOnStairs = false;
		break;
	case PLAYER_STATE_SUPWEAPON_ATTACK:
		animationSet->at(state)->ResetCurrentFrame();
		animationSet->at(state)->StartAnimation();
		Attack(currentSupWeaponType);
		isWalking = false;
		break;
	case PLAYER_STATE_HURTING:
		if (isHurting == true)
			return;
		isHurting = true;
		isWalking = false;
		isJumping = false;
		isAttacking = false;
		if (isSitting)	isSitting = false;
		isOnStairs = false;
		vX = PLAYER_DEFLECT_SPEED_X * -direction;
		vY = -PLAYER_DEFLECT_SPEED_Y;
		break;
	case PLAYER_STATE_SITTING:
		vX = 0;		//Vi phim return khi dang ngoi nen set vX = 0 de khi moving -> sit se khong bi truot
		isSitting = true;
		isWalking = false;
		isOnStairs = false;
		cannotMoveDown = true;
		break;
	case PLAYER_STATE_SITTING_ATTACK:
		animationSet->at(state)->ResetCurrentFrame();
		animationSet->at(state)->StartAnimation();
		Attack(EntityType::MORNINGSTAR);
		vX = 0;		
		isSitting = true;
		isWalking = false;
		isOnStairs = false;
		break;
	case PLAYER_STATE_SUPWEAPON_SIT_ATTACK:
		animationSet->at(state)->ResetCurrentFrame();
		animationSet->at(state)->StartAnimation();
		Attack(currentSupWeaponType);
		vX = 0;		
		isSitting = true;
		isWalking = false;
		break;
	case PLAYER_STATE_UPGRADING:
		if (isAttacking) isAttacking = false;
		isHurting = false;
		isWalking = false;
		isJumping = false;
		if (isSitting)	isSitting = false;
		isOnStairs = false;
		vX = 0;
		vY = 0;
		break;
	case PLAYER_STATE_PASSING_STAGE:
		isWalking = true;
		vX = PLAYER_PASSING_STAGE_SPEED_X * direction;
		posX += dx;	//Khi trong state nay tuc la da va cham voi gate, o ngoai update cua simon khi co va cham kh update posX
		isPassingStage = true;	//block control simon
		isOnStairs = false;
		break;
	}
}

void Player::GetBoundingBox(float &left, float &top, float &right, float &bottom) 
{
	left = posX;
	top = posY;
	right = posX + PLAYER_BBOX_WIDTH;
	bottom = posY + PLAYER_BBOX_HEIGHT;
}

void Player::Attack(EntityType weaponType)
{
	if (isAttacking || isUpgrading )	
		return;
	
	if (unsighted)	//Attack khi dang tang hinh se mat tang hinh
		StopInvisible();

	if (weaponType == EntityType::MORNINGSTAR)
	{
		if (mainWeapon->GetIsDone())
		{
			isAttacking = true;
			mainWeapon->Attack(posX, direction);
		}
	}
	else 
		if (weaponType == EntityType::DAGGER ||
			weaponType == EntityType::BOOMERANG ||
			weaponType == EntityType::AXE ||
			weaponType == EntityType::WATERPOTION)
		{
			if (mana > WEAPON_DEFAULT_MANA_COST - 1)
			{
				if (supWeapon->GetIsDone())
				{
					if ((isGettingDouble && isAttackingDouble) || (isGettingTriple && isAttackingTriple))	//Dang dung WeaponAtDouble thi khong duoc dung Weapon goc'
						return;
					AddMana(-WEAPON_DEFAULT_MANA_COST);
					isAttacking = true;
					supWeapon->Attack(posX, direction);
					if (isGettingDouble)
						doubleAttackDelay->Start();
					return;
				}
				else if (supWeaponAtDouble->GetIsDone() && isGettingDouble && doubleAttackDelay->IsTimeUp())	//A completely NEW and SUPER COMPACT version of double attack :D 
				{
					if (isGettingTriple && isAttackingTriple)
						return;
					AddMana(-WEAPON_DEFAULT_MANA_COST);
					isAttackingDouble = true;
					supWeaponAtDouble->Attack(posX, direction);
					doubleAttackDelay->Reset();
					if (isGettingTriple)
						tripleAttackDelay->Start();
					return;
				}
				else if (supWeaponAtTriple->GetIsDone() && isGettingTriple && tripleAttackDelay->IsTimeUp())
				{
					AddMana(-WEAPON_DEFAULT_MANA_COST);
					isAttackingTriple = true;
					supWeaponAtTriple->Attack(posX, direction);
					tripleAttackDelay->Reset();
					return;
				}
			}
		}
		else
			if (weaponType == EntityType::STOPWATCH)
			{
				if (mana > STOPWATCH_MANA_COST - 1 && timeStopTimer->IsTimeUp())
				{
					AddMana(-STOPWATCH_MANA_COST);
					isTimeStop = true;
					timeStopTimer->Start();
					//SetPlayerSupWeaponType(EntityType::NONE);
				}
			}
			else
				if (weaponType == EntityType::POKEBALL)
				{
					if (mana > PKB_MANA_COST - 1)
						if (supWeapon->GetIsDone())
						{
							AddMana(-0);
							isAttacking = true;
							supWeapon->Attack(posX, direction);
							//SetPlayerSupWeaponType(EntityType::NONE);
							return;
						}
				}

}

void Player::UpgradingMorningStar()
{
	MorningStar* morningStar = dynamic_cast<MorningStar*>(mainWeapon);
	if (morningStar->GetLevel() >= MS_MAX_LEVEL)
		return;

	upgradeTimer->Start();
	isUpgrading = true;
	SetState(PLAYER_STATE_UPGRADING);
}

void Player::SetPlayerSupWeaponType(EntityType supWeaponType)
{
	switch (supWeaponType)
	{
	case EntityType::DAGGER:
		currentSupWeaponType = EntityType::DAGGER;
		supWeapon = new Dagger();
		supWeaponAtDouble = new Dagger();
		supWeaponAtTriple = new Dagger();
		break;
	case EntityType::BOOMERANG:
		currentSupWeaponType = EntityType::BOOMERANG;
		supWeapon = new Boomerang(this);
		supWeaponAtDouble = new Boomerang(this);
		supWeaponAtTriple = new Boomerang(this);
		break;
	case EntityType::AXE:
		currentSupWeaponType = EntityType::AXE;
		supWeapon = new Axe();
		supWeaponAtDouble = new Axe();
		supWeaponAtTriple = new Axe();
		break;
	case EntityType::WATERPOTION:
		currentSupWeaponType = EntityType::WATERPOTION;
		supWeapon = new WaterPotion();
		supWeaponAtDouble = new WaterPotion();
		supWeaponAtTriple = new WaterPotion();
		break;
	case EntityType::STOPWATCH:
		currentSupWeaponType = EntityType::STOPWATCH;
		supWeapon = new StopWatch();
		supWeaponAtDouble = new StopWatch();
		supWeaponAtTriple = new StopWatch();
		break;
	case EntityType::POKEBALL:
		currentSupWeaponType = EntityType::POKEBALL;
		supWeapon = new Pokeball();
		supWeaponAtDouble = new Pokeball();
		supWeaponAtTriple = new Pokeball();
		break;
	default:
		currentSupWeaponType = EntityType::NONE;
		supWeapon = NULL;
		supWeaponAtDouble = NULL;
		supWeaponAtTriple = NULL;
		break;
	}
}

void Player::SupWeaponUpdate(Weapon* weapon, DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	if (weapon != NULL)
	{
		if (!weapon->GetIsDone())
		{
			if (!weapon->GetIsReceivedPos())
			{
				weapon->SetPosition(posX, posY);
				weapon->SetIsReceivedPos(true);			//Chi nhan pos 1 lan sau khi het delay
			}
			weapon->Update(dt, coObjects);
		}
	}
}

void Player::SupWeaponRender(Weapon* weapon)
{
	if (weapon != NULL)
	{
		if (!weapon->GetIsDone())
		{
			weapon->Render();
		}
	}
}

void Player::Respawn()
{
	switch (currentStageLiving)
	{
	case STAGE_1:
		posX = 100;
		posY = 280;
		break;
	case STAGE_2_1:
		posX = 400;
		posY = 150;
		break;
	case STAGE_2_2:
		posX = 800;
		posY = 150;
		break;
	case STAGE_3_1:
		posX = 1440;
		posY = 350;
		break;
	case STAGE_3_2:
		posX = 304;
		posY = 200;
		break;
	default:
		posX = 100;
		posY = 280;
		break;
	}

	vX = 0;
	isJumping = false;
	isHurting = false;
	isImmortaling = false;
	SetState(PLAYER_STATE_IDLE);
	health = PLAYER_MAXHEALTH;
	immortalTimer->Start();
	isImmortaling = true;
	StopInvisible();
}

bool Player::SimonCollideWithStair(vector<LPGAMEENTITY>* listStairs)
{
	float simon_l, simon_t, simon_r, simon_b;
	GetBoundingBox(simon_l, simon_t, simon_r, simon_b);

	simon_t += 50;	
	simon_b += 5;  

	canMoveUp = false;
	canMoveDown = false;

	for (UINT i = 0; i < listStairs->size(); i++)
	{
		float stair_l, stair_t, stair_r, stair_b;
		listStairs->at(i)->GetBoundingBox(stair_l, stair_t, stair_r, stair_b);

		LPSPRITE sprt = animationSet->at(state)->GetAnimationCurrentFrame(0)->GetSprite();
		LPSPRITE coSprt = listStairs->at(i)->GetAnimationSet()->at(0)->GetAnimationCurrentFrame(0)->GetSprite();

		if (Game::GetInstance()->IsCollidingAABB(
			simon_l - (float)sprt->GetFrameWidth() / 2,
			simon_t - (float)sprt->GetFrameHeight() / 2,
			simon_r - (float)sprt->GetFrameWidth() / 2,
			simon_b - (float)sprt->GetFrameHeight() / 2,
			stair_l - (float)coSprt->GetFrameWidth() / 2,
			stair_t - (float)coSprt->GetFrameHeight() / 2,
			stair_r - (float)coSprt->GetFrameWidth(),
			stair_b - (float)coSprt->GetFrameHeight() / 2))
		{
			if (listStairs->at(i)->GetDirection() == 1) 
				stairDirection = 1;
			else 
				stairDirection = -1;

			stairCollided = listStairs->at(i);

			//Simon tren 1 nac thang nao do
			if (stair_b > simon_b) canMoveDown = true;
			//Duoi Simon co thang
			if (posY >= stair_t - STAIRS_BBOX_WIDTH) canMoveUp = true;

			for (UINT j = 0; j < listStairs->size(); j++)
			{
				if (i == j)
					continue;

				float nextStairX, nextStairY;
				listStairs->at(j)->ReceivePos(nextStairX, nextStairY);

				float nextStairDistanceX = abs(nextStairX - stair_l);
				float nextStairDistanceY = nextStairY - stair_t;

				if (nextStairDistanceX == STAIRS_BBOX_WIDTH && nextStairDistanceY == -STAIRS_BBOX_WIDTH)
					canMoveUp = true;
				if (nextStairDistanceX == STAIRS_BBOX_WIDTH && nextStairDistanceY == STAIRS_BBOX_WIDTH)
					canMoveDown = true;
			}
			return true; 
		}
	}
	return false;
}

void Player::TriggerAutoWalk(float nextPos, int nextState, int nextDirection)
{
	isWalkingOnStairs = true;
	posWalkingOnStairs = nextPos;
	stateWalkingOnStairs = nextState;
	directionWalkingOnStairs = nextDirection;
}

void Player::AutoWalk()
{
	posX += dx;
	posY += dy;
	if ((direction == 1 && posX >= posWalkingOnStairs) || (direction == -1 && posX <= posWalkingOnStairs))
	{
		posX = posWalkingOnStairs;
		state = stateWalkingOnStairs;
		direction = directionWalkingOnStairs;
		SetState(state);
		if (state == PLAYER_STATE_GOING_DOWN_STAIRS) posY += 1.0f; 
		isWalkingOnStairs = false;
		posWalkingOnStairs = 0;
		stateWalkingOnStairs = -1;
		directionWalkingOnStairs = 0;
	}
}

void Player::PlayerUpStairs()
{
	if (!canMoveUp)	//Cuoi' thang
	{
		if (isOnStairs)
		{
			float stairPosX, stairPosY;
			stairCollided->ReceivePos(stairPosX, stairPosY);
			if (stairDirection == 1)
				stairPosX += 20;
			else
				stairPosX -= 20;
			this->direction = stairDirection;
			SetState(PLAYER_STATE_GOING_UP_STAIRS);
			TriggerAutoWalk(stairPosX, PLAYER_STATE_IDLE, direction);
		}
		return;
	}
	if (!isOnStairs)	//Duoi chan thang
	{
		float stairPosX, stairPosY, tempPlayerPosX;
		ReceivePos(tempPlayerPosX, stairPosY);
		stairCollided->ReceivePos(stairPosX, stairPosY);
		if (stairDirection == 1)
		{
			stairPosX -= 16.0f;
		}
		else stairPosX += 20.0f;
		if (stairPosX < tempPlayerPosX) direction = -1;
		else if (stairPosX > tempPlayerPosX)  direction = 1;
		vY = 0;
		SetState(PLAYER_STATE_WALKING);
		TriggerAutoWalk(stairPosX, PLAYER_STATE_GOING_UP_STAIRS, stairDirection);
		isOnStairs = true;
		return;
	}
	else
	{
		direction = stairDirection;
		SetState(PLAYER_STATE_GOING_UP_STAIRS);
	}
	return;
}
void Player::PlayerDownStairs()
{
	if (!canMoveDown)	//Cuoi' thang
	{
		if (isOnStairs)
			SetState(PLAYER_STATE_IDLE);
		else
			SetState(PLAYER_STATE_SITTING);
		return;
	}
	if (!isOnStairs)	//Dinh? thang
	{
		float stairPosX, stairPosY, tempPlayerPosX;
		ReceivePos(tempPlayerPosX, stairPosY);
		stairCollided->ReceivePos(stairPosX, stairPosY);
		if (stairDirection == 1)
			stairPosX += 8.0f;
		else stairPosX -= 8.0f;
		if (stairPosX < tempPlayerPosX) direction = -1;
		else if (stairPosX > tempPlayerPosX) direction = 1;
		vY = 0;
		SetState(PLAYER_STATE_WALKING);
		TriggerAutoWalk(stairPosX, PLAYER_STATE_GOING_DOWN_STAIRS, -stairDirection);
		isOnStairs = true;
		return;
	}
	else
	{
		direction = -stairDirection;
		SetState(PLAYER_STATE_GOING_DOWN_STAIRS);
	}
	return;
}
bool Player::PlayerStandOnStairs()
{
	if (state == PLAYER_STATE_GOING_UP_STAIRS || 
		state == PLAYER_STATE_GOING_DOWN_STAIRS || 
		state == PLAYER_STATE_UPSTARIS_ATTACK || 
		state == PLAYER_STATE_DOWNSTAIRS_ATTACK ||
		state == PLAYER_STATE_SUPWEAPON_ATTACK)
	{
		if ((state == PLAYER_STATE_UPSTARIS_ATTACK || state == PLAYER_STATE_SUPWEAPON_ATTACK) && !isAttacking)
		{
			SetState(PLAYER_STATE_GOING_UP_STAIRS);
		}
		else if ((state == PLAYER_STATE_DOWNSTAIRS_ATTACK || state == PLAYER_STATE_SUPWEAPON_ATTACK) && !isAttacking)
		{
			SetState(PLAYER_STATE_GOING_DOWN_STAIRS);
		}
		vX = 0;
		vY = 0;
		animationSet->at(PLAYER_STATE_GOING_DOWN_STAIRS)->ResetCurrentFrame();
		animationSet->at(PLAYER_STATE_GOING_UP_STAIRS)->ResetCurrentFrame();
		return true;
	}
	return false;
}

void Player::StartInvisible()
{
	invisibleTimer->Start();
	unsighted = true;
}

void Player::StopInvisible()
{
	invisibleTimer->Reset();
	unsighted = false;
}