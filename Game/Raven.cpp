#include "Raven.h"

Raven::Raven(float posX, float posY, int directionX, int firstDirY, LPGAMEENTITY target)
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(ANIMATION_SET_RAVEN));
	tag = EntityType::RAVEN;

	this->posX = posX;
	this->posY = posY;
	destinationPosXPhase1 = posX + RAVEN_DIST_TO_DEST_POSX_PHASE1;
	destinationPosYPhase1 = posY + RAVEN_DIST_TO_DEST_POSY_PHASE1 * firstDirY;
	this->direction = directionX;

	this->SetState(RAVEN_STATE_INACTIVE);

	health = 1;
	isDead = false;
	this->target = target;
	activated = false;
	isDonePhase1 = false;
	isDonePhase2 = false;
	triggerReady = false;
	sidePhase2 = 1;
	countChangeSide = 0;
	isRavenTired = false;
}

Raven::~Raven() {}

void Raven::Update(DWORD dt, vector<LPGAMEENTITY> *coObjects)
{
	if (health <= 0 || posX < 5 || posX > SCREEN_WIDTH * 2.85f)
	{
		SetState(RAVEN_STATE_DIE);
		return;
	}

	if (target != NULL)
	{
		if (GetDistance(D3DXVECTOR2(this->posX, this->posY), D3DXVECTOR2(target->GetPosX(), target->GetPosY())) <= 250 && target->GetState() != 0 && !target->IsUnsighted())
		{
			SetState(RAVEN_STATE_FLYING);
			activated = true;
		}
	}
	D3DXVECTOR2 pos = D3DXVECTOR2(posX, posY);

	if (!isDonePhase1 && activated)	//Phase 1 : Fly toward the destination's defined when init
	{
		pos += RadialMovement(D3DXVECTOR2(destinationPosXPhase1, destinationPosYPhase1), pos, RAVEN_FLYING_SPEED_PHASE1);
			
		if (posX == destinationPosXPhase1 && 
			posY == destinationPosYPhase1)
		{
			isDonePhase1 = true;
			waitingTimer->Start();
		}
	}
	if (isDonePhase1 && waitingTimer->IsTimeUp() && !isDonePhase2)	//Phase 2 : Fly around player
	{
		if (countChangeSide >= 5)
		{
			isDonePhase2 = true;
			readyTimer->Reset();

			isRavenTired = true;
			int random = rand() % 1;
			if (random == 1)
				destinationPosXRavenTired = SCREEN_WIDTH * 4;
			else
				destinationPosXRavenTired = -10;
			destinationPosYRavenTired = destinationPosYPhase2;
			return;
		}
		int random = rand() % 10000;
		if (random <= 50)	//0.5% chance xay ra dao chieu tiep can cua Raven
		{
			sidePhase2 *= -1;
			countChangeSide++;
			if (triggerReady)	//Neu da~ kich hoat readyTimer roi thi reset dem' lai
			{
				readyTimer->Reset();
				triggerReady = false;
			}
		}
		destinationPosXPhase2 = target->GetPosX() + RAVEN_DIST_TO_DEST_POSX_PHASE2 * sidePhase2;
		destinationPosYPhase2 = target->GetPosY() + RAVEN_DIST_TO_DEST_POSY_PHASE2;
		pos += RadialMovement(D3DXVECTOR2(destinationPosXPhase2, destinationPosYPhase2), pos, RAVEN_FLYING_SPEED_PHASE2);

		if (!triggerReady)
		{
			readyTimer->Start();
			triggerReady = true;
		}
		if (readyTimer->IsTimeUp())
			isDonePhase2 = true;
	}
	if (isDonePhase1 && isDonePhase2 && !isRavenTired)	//Phase 3 : Fly toward player with highspeed
	{
		pos += RadialMovement(D3DXVECTOR2(target->GetPosX(), target->GetPosY()), pos, RAVEN_FLYING_SPEED_PHASE3);
		
	}
	if (isRavenTired)	//Sub Phase: Change side too much so 'fvck this sh1t im out'
	{
		pos += RadialMovement(D3DXVECTOR2(destinationPosXRavenTired, destinationPosYRavenTired), pos, RAVEN_FLYING_SPEED_PHASE2);
	}

	posX = pos.x;
	posY = pos.y;
	Entity::Update(dt);
	if (target->GetPosX() < posX)
		direction = -1;
	else
		direction = 1;
}

void Raven::Render()
{
	if (isDead)
		return;

	animationSet->at(state)->Render(direction, posX, posY);

	RenderBoundingBox();
}


void Raven::SetState(int state)
{
	Entity::SetState(state);
	switch (state)
	{
	case RAVEN_STATE_DIE:
		vX = 0;
		vY = 0;
		isDead = true;
		break;
	case RAVEN_STATE_FLYING:
		break;
	case RAVEN_STATE_INACTIVE:
		vX = 0;
		vY = 0;
		break;
	}
}

void Raven::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	//not clean
	if (!isDead)
	{
		l = posX;
		t = posY;
		r = posX + RAVEN_BBOX_WIDTH;
		b = posY + RAVEN_BBOX_HEIGHT;
	}
}