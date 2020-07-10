#include "TheLastEverBat.h"

TheLastEverBat::TheLastEverBat(float posX, float posY, LPGAMEENTITY target)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_TLEBAT));
	tag = EntityType::TLEBAT;

	this->posX = posX;
	this->posY = posY;
	directionY = 1;

	this->SetState(TLEBAT_STATE_INACTIVE);

	health = TLEBAT_MAXHEALTH;
	isDead = false;
	this->target = target;
	activated = false;
	waitingTrigger = false;
	//First move go window or not
	if (rand() % 100 <= 50)
		process = TLEBAT_GO_TALLTOWER;
	else
		process = TLEBAT_GO_STAIR;
	isDonePhaseWait = false; 
	isDoneFlyCurve = false;
	isGetDistanceYTarget = false;
	isStartFlyCurve = false;
}

TheLastEverBat::~TheLastEverBat() {}

void TheLastEverBat::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	if (health <= 0)
	{
		SetState(TLEBAT_STATE_DIE);
		return;
	}

	if (waitingTrigger && waitingTimer->IsTimeUp() && state != TLEBAT_STATE_FLYING)
	{
		activated = true;
		SetState(TLEBAT_STATE_FLYING);
		waitingTrigger = false;
		waitingTimer->Reset();
	}

	D3DXVECTOR2 pos = D3DXVECTOR2(posX, posY);
	if (activated)
	{
		if (!isDonePhaseWait)
		{
			if (process == TLEBAT_GO_STAIR)
				pos += RadialMovement(D3DXVECTOR2(TLEBAT_AT_STAIR_POS_X, TLEBAT_AT_STAIR_POS_Y), pos, TLEBAT_GO_PRESET_LOCATION_SPEED);
			else if (process == TLEBAT_GO_TALLTOWER)
				pos += RadialMovement(D3DXVECTOR2(TLEBAT_AT_TALLTOWER_POS_X, TLEBAT_AT_TALLTOWER_POS_Y), pos, TLEBAT_GO_PRESET_LOCATION_SPEED);

			posX = pos.x;
			posY = pos.y;

			//Stop moving and wait
			if ((posX == TLEBAT_AT_STAIR_POS_X &&
				posY == TLEBAT_AT_STAIR_POS_Y) ||
				(posX == TLEBAT_AT_TALLTOWER_POS_X &&
				posY == TLEBAT_AT_TALLTOWER_POS_Y))
			{
				isDonePhaseWait = true;
				waitingTimer->Start();
			}
		}
		if (isDonePhaseWait && waitingTimer->IsTimeUp())
		{
			waitingTimer->Reset();
			//Fly in 2s
			if (!isStartFlyCurve)
			{
				flyCurveTimer->Start();
				isStartFlyCurve = true;
			}
			//Fly until time up
			if (isStartFlyCurve && !flyCurveTimer->IsTimeUp())
			{
				if (process == TLEBAT_GO_STAIR)
				{
					FlyStyle(TLEBAT_AT_STAIR_POS_Y);
				}
				if (process == TLEBAT_GO_TALLTOWER)
				{
					FlyStyle(TLEBAT_AT_TALLTOWER_POS_Y);
				}
				if (process == TLEBAT_GO_WINDOW)
				{
					FlyStyle(TLEBAT_AT_WINDOW_POS_Y, 0.035, 0.004);
				}
				if (process == TLEBAT_GO_SHORTTOWER)
				{
					FlyStyle(TLEBAT_AT_SHORTTOWER_POS_Y);
				}
				//Reach borders
				if (posX == TLEBAT_MIN_POS_X || posX == TLEBAT_MAX_POS_X)
				{
					direction *= -1;
					vX *= -1;
					vY = -0.02;
				}
				if (posY == TLEBAT_MAX_POS_Y)
				{
					directionY = -1;
					vY = -0.02;
				}
				if (posY == TLEBAT_MIN_POS_Y)
				{
					directionY = 1;
					vY = 0.02;
				}
			}
			else
			{
				//Stop flying
				flyCurveTimer->Reset();
				vX = 0;
				vY = 0;
				//And wait 2s
				if (!waitingTrigger)
				{
					//Random new process
					int newProc = rand() % 100;
					if (newProc < 25)
						process = TLEBAT_GO_STAIR;
					else if (25 <= newProc && newProc < 50)
						process = TLEBAT_GO_TALLTOWER;
					else if (50 <= newProc && newProc < 75)
						process = TLEBAT_GO_WINDOW;
					else
						process = TLEBAT_GO_SHORTTOWER;
					waitingTrigger = true;
					waitingTimer->Start();
				}
			}
			if (waitingTrigger && waitingTimer->IsTimeUp() && isStartFlyCurve)
			{
				//Fly to target base on process
				if(process == TLEBAT_GO_STAIR)
					pos += RadialMovement(D3DXVECTOR2(TLEBAT_AT_STAIR_POS_X, TLEBAT_AT_STAIR_POS_Y), pos, TLEBAT_GO_PRESET_LOCATION_SPEED);
				else if (process == TLEBAT_GO_TALLTOWER)
					pos += RadialMovement(D3DXVECTOR2(TLEBAT_AT_TALLTOWER_POS_X, TLEBAT_AT_TALLTOWER_POS_Y), pos, TLEBAT_GO_PRESET_LOCATION_SPEED);
				else if (process == TLEBAT_GO_WINDOW)
					pos += RadialMovement(D3DXVECTOR2(TLEBAT_AT_WINDOW_POS_X, TLEBAT_AT_WINDOW_POS_Y), pos, TLEBAT_GO_PRESET_LOCATION_SPEED);
				else if (process == TLEBAT_GO_SHORTTOWER)
					pos += RadialMovement(D3DXVECTOR2(TLEBAT_AT_SHORTTOWER_POS_X, TLEBAT_AT_SHORTTOWER_POS_Y), pos, TLEBAT_GO_PRESET_LOCATION_SPEED);
				posX = pos.x;
				posY = pos.y;

				//Stop moving and wait
				if ((process == TLEBAT_GO_STAIR &&
					posX == TLEBAT_AT_STAIR_POS_X &&
					posY == TLEBAT_AT_STAIR_POS_Y) ||
					(process == TLEBAT_GO_TALLTOWER &&
						posX == TLEBAT_AT_TALLTOWER_POS_X &&
						posY == TLEBAT_AT_TALLTOWER_POS_Y) ||
						(process == TLEBAT_GO_WINDOW &&
							posX == TLEBAT_AT_WINDOW_POS_X &&
							posY == TLEBAT_AT_WINDOW_POS_Y) ||
							(process == TLEBAT_GO_SHORTTOWER &&
								posX == TLEBAT_AT_SHORTTOWER_POS_X &&
								posY == TLEBAT_AT_SHORTTOWER_POS_Y))
				{
					isStartFlyCurve = false;
					isGetDistanceYTarget = false;
					waitingTrigger = false;
					waitingTimer->Reset();
					//After wait auto fly down
					directionY = 1;
				}
			}
		}
	}

	Entity::Update(dt);
	if (!flyCurveTimer->IsTimeUp())
	{
		posX += dx;
		posY += dy;
	}
	if (target->GetPosX() < posX)
		direction = -1;
	else
		direction = 1;
	if (posX > TLEBAT_MAX_POS_X) posX = TLEBAT_MAX_POS_X;
	else if (posX < TLEBAT_MIN_POS_X) posX = TLEBAT_MIN_POS_X;
	if (posY > TLEBAT_MAX_POS_Y) posY = TLEBAT_MAX_POS_Y;
	else if (posY < TLEBAT_MIN_POS_Y) posY = TLEBAT_MIN_POS_Y;
}

void TheLastEverBat::FlyStyle(float currentPosY, float extendSpeedX, float extendSpeedY)
{
	if (!isGetDistanceYTarget)
	{
		int r = rand() % (20 + 40 + 1) - 40; //random from -40 to 20 (max - min + 1) + min
		distanceYTarget = abs((TLEBAT_POS_Y_AMPLITUDE_CALC) - posY + r) / 2;
		isGetDistanceYTarget = true;
		//some unusual case
		if(process == TLEBAT_GO_STAIR && target->GetPosX() > posX)
			vX = (0.165) * direction;
		else if (process == TLEBAT_GO_WINDOW && target->GetPosX() > posX)
			vX = (0.1) * direction;
		else if (process == TLEBAT_GO_TALLTOWER && target->GetPosX() < posX)
			vX = (0.1) * direction;
		else
			vX = (TLEBAT_CURVE_FLY_SPEED_X + extendSpeedX) * direction;
	}

	//Fly curve
	if (posY - currentPosY >= distanceYTarget)
		directionY = -1;
	else if (currentPosY - posY >= distanceYTarget)
		directionY = 1;
	if (process == TLEBAT_GO_TALLTOWER && target->GetPosX() < posX)
		vY += (0.01) * directionY;
	else
		vY += (TLEBAT_CURVE_FLY_SPEED_Y + extendSpeedY) * directionY;
}

void TheLastEverBat::Render()
{
	if (isDead)
		return;

	animationSet->at(state)->Render(direction, posX, posY);

	RenderBoundingBox();
}


void TheLastEverBat::SetState(int state)
{
	Entity::SetState(state);
	switch (state)
	{
	case TLEBAT_STATE_DIE:
		vX = 0;
		vY = 0;
		health = 0;
		isDead = true;
		break;
	case TLEBAT_STATE_FLYING:
		break;
	case TLEBAT_STATE_INACTIVE:
		vX = 0;
		vY = 0;
		break;
	}
}

void TheLastEverBat::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	//not clean
	if (!isDead)
	{
		l = posX;
		t = posY;
		r = posX + TLEBAT_BBOX_WIDTH;
		b = posY + TLEBAT_BBOX_HEIGHT;
	}
}