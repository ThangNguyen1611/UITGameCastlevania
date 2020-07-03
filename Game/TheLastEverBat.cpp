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
	/*if (rand() % 100 <= 50)
		isPhaseWaitAtWindow = false;
	else*/
		isPhaseWaitAtWindow = true;
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

	if (waitingTrigger && waitingTimer->IsTimeUp())
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
			if(isPhaseWaitAtWindow)
				pos += RadialMovement(D3DXVECTOR2(TLEBAT_AT_WINDOW_POS_X, TLEBAT_AT_WINDOW_POS_Y), pos, TLEBAT_GO_WINDOW_SPEED);
			else
				pos += RadialMovement(D3DXVECTOR2(TLEBAT_NOTAT_WINDOW_POS_X, TLEBAT_NOTAT_WINDOW_POS_Y), pos, TLEBAT_GO_WINDOW_SPEED);

			posX = pos.x;
			posY = pos.y;

			//Stop moving and wait
			if ((posX == TLEBAT_AT_WINDOW_POS_X &&
				posY == TLEBAT_AT_WINDOW_POS_Y) ||
				(posX == TLEBAT_NOTAT_WINDOW_POS_X &&
				posY == TLEBAT_NOTAT_WINDOW_POS_Y))
			{
				isDonePhaseWait = true;
				waitingTimer->Start();
			}
		}
		if (isDonePhaseWait && waitingTimer->IsTimeUp())
		{
			waitingTimer->Reset();
			if (!isStartFlyCurve)
			{
				flyCurveTimer->Start();
				isStartFlyCurve = true;
			}
			if (isStartFlyCurve && !flyCurveTimer->IsTimeUp())
			{
				//Calculate to set Simon is top of parabol
				if (!isGetDistanceYTarget)
				{
					int r = rand() % (20 + 20 + 1) - 20; //random from -20 to 20 (max - min + 1) + min
					distanceXTarget = abs((target->GetPosY()) - posY) / 2;
					isGetDistanceYTarget = true;
					vX = TLEBAT_CURVE_FLY_SPEED_X * direction;
				}

				//Fly curve
				if (posY - TLEBAT_AT_WINDOW_POS_Y >= distanceXTarget)
					directionY = -1;
				else if (TLEBAT_AT_WINDOW_POS_Y - posY >= distanceXTarget)
					directionY = 1;

				vY += TLEBAT_CURVE_FLY_SPEED_Y * directionY;

				//Stop fly curve
				if (posX == TLEBAT_MIN_POS_X)
				{
					direction *= -1;
					vX *= -1;
					vY = -0.02;
				}
			}
			else
			{
				flyCurveTimer->Reset();
				vX = 0;
				vY = 0;
				//Di ve ben phai tren simon va lap lai curve
			}
			/*else
			{
				pos += RadialMovement(D3DXVECTOR2(target->GetPosX(), target->GetPosY()), pos, 1.25f);
				posX = pos.x;
				posY = pos.y;
			}*/
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