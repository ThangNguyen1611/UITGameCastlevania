#include "PlayScene.h"

PlayScene::PlayScene() : Scene()
{
	keyHandler = new PlayScenceKeyHandler(this);
	LoadBaseObjects();
	ChooseMap(STAGE_1);
}

void PlayScene::LoadBaseObjects()
{
	texturesFilePath = ToLPCWSTR("Resources/Scene/textures_playscene.txt");
	LoadBaseTextures();
	if (player == NULL)
	{
		player = new Player(100, 280);
		//listObjects.push_back(player);
		DebugOut(L"[INFO] Simon CREATED! \n");
	}
	gameUI = new UI(player->GetHealth(), 16);
	gameTime = GameTime::GetInstance();		//That ra khong can 2 buoc nay vi ca 2 deu thiet ke Singleton
	gameCamera = Camera::GetInstance();
	gameMap = new Map();
	triggerResetGame = false;
	triggerCrossTimer = false;
}

void PlayScene::ChooseMap(int whatMap)	
{
	idStage = whatMap;
	Game::GetInstance()->SetKeyHandler(this->GetKeyEventHandler());
	player->ReceiveCurrentStage(idStage);
	player->StopInvisible();
	gameTime->ResetGameTime();
	triggerCrossTimer = false;
	crossTimer->Reset();

	switch (idStage)
	{
	case STAGE_2_1:
		easterEgg_Stage2_1 = 0;
		break;
	case STAGE_2_2:
		easterEgg_Stage2_2 = 0;
		break;
	case STAGE_3_1:
		triggerSpawnGhost = true;
		break;
	case STAGE_3_2:
		easterEgg_Stage3_2 = 1;
		triggerSpawnGhost = true;
		break;
	case STAGE_4:
		//Zombie Logic
		zombieCounter = 0;
		isTimeToSpawnZombie = true;		//vua vao spawn luon
		triggerSpawnZombie = false;
		//Bat Logic
		isTimeToSpawnBat = true;
		triggerSpawnBat = true;
	default:
		break;
	}

	int convertSimple = idStage / STAGE_1;
	sceneFilePath = listSceneFilePath[convertSimple - 1];
	LoadSceneObjects();
	gameGrid = new Grid(mapWidth, mapHeight);
	gameGrid->PushObjectIntoGrid(listObjectsToGrid);
}

void PlayScene::GetObjectFromGrid()
{
	listObjects.clear();
	listObjectsFromGrid.clear();
	gameGrid->GetObjectFromGrid(listObjectsFromGrid);
	for (UINT i = 0; i < listObjectsFromGrid.size(); i++)
	{
		LPGAMEENTITY obj = listObjectsFromGrid[i];
		listObjects.push_back(obj);
	}
}

Effect* PlayScene::CreateEffect(EntityType createrType, EntityType effectType, float posX, float posY, int typeBrickExplode)
{
	if (effectType == EntityType::HITEFFECT)
		return new Hit(posX - HIT_EFFECT_CUSTOMIZED_POS, posY - HIT_EFFECT_CUSTOMIZED_POS);
	else if (effectType == EntityType::FIREEFFECT)
		return new Fire(posX, posY);
	else if (effectType == EntityType::ADDSCOREEFFECT)
		return new Score(posX, posY, createrType);
	else if (effectType == EntityType::BRICKEXPLODEEFFECT)
		return new BrickExplode(posX, posY, typeBrickExplode);
	else
		return new Hit(posX - HIT_EFFECT_CUSTOMIZED_POS, posY - HIT_EFFECT_CUSTOMIZED_POS);
}

Item* PlayScene::RandomItem(float posX, float posY)
{
	int bagrandom = rand() % 100; 
	int random = rand() % 1350;
	if (random <= 100)
		return new SmallHeart(posX, posY);
	else if (100 < random && random <= 200)
		return new BigHeart(posX, posY);
	else if (200 < random && random <= 300)
		return new YummiChickenLeg(posX, posY);
	else if (300 < random && random <= 400)
		return new UpgradeMorningStar(posX, posY);
	else if (400 < random && random <= 500)
		return new ItemDagger(posX, posY);
	else if (500 < random && random <= 600)
		return new ItemAxe(posX, posY);
	else if (600 < random && random <= 700)
		return new ItemBoomerang(posX, posY);
	else if (700 < random && random <= 800)
		return new ItemWaterPotion(posX, posY);
	else if (800 < random && random <= 900)
		return new ItemStopWatch(posX, posY);
	else if (900 < random && random <= 1000)
		return new Cross(posX, posY);
	else if (1000 < random && random <= 1100)
		return new Drug(posX, posY);
	else if (1100 < random && random <= 1200)
	{
		if (rand() % 100 <= 50)
			return new ExtraShot(posX, posY, EXTRASHOT_LEVEL2);
		else
			return new ExtraShot(posX, posY, EXTRASHOT_LEVEL3);
	}
	else if (1200 < random && random <= 1250)
		return new ItemPokeball(posX, posY);
	else
	{
		if (bagrandom <= 33)
			return new MoneyBags(posX, posY, EntityType::MONEYBAGRED);
		else if (33 < bagrandom && bagrandom <= 66)
			return new MoneyBags(posX, posY, EntityType::MONEYBAGWHITE);
		else
			return new MoneyBags(posX, posY, EntityType::MONEYBAGBLUE);
	}
}

Item* PlayScene::DropItem(EntityType createrType, float posX, float posY, int idCreater)
{
	if (createrType == EntityType::NONE)		//special case
	{
		if (idStage == STAGE_2_1 || idStage == STAGE_3_2)
			return new Crown(posX, posY);
		else
			if (idStage == STAGE_2_2)
				return new ExtraShot(posX, posY, EXTRASHOT_LEVEL2);
	}

	if (createrType == EntityType::TORCH)
	{
		if (idCreater == 1)
		{
			return new BigHeart(posX, posY);
		}
		else
			if (idCreater == 2)
			{
				return new UpgradeMorningStar(posX, posY);
			}
			else
				if (idCreater == 3)
				{
					return new ItemDagger(posX, posY);
				}
				else
				{
					RandomItem(posX, posY);
				}
	}
	else
		if (createrType == EntityType::CANDLE)
		{
			if (idCreater == 1)
			{
				return new SmallHeart(posX, posY);
			}
			else
			{
				RandomItem(posX, posY);
			}
		}
		else
			if (createrType == EntityType::BREAKABLEBRICK)
			{
				return new YummiChickenLeg(posX, posY);
			}
			else
				if (createrType == EntityType::KNIGHT ||
					createrType == EntityType::DARKENBAT ||
					createrType == EntityType::GHOST ||
					createrType == EntityType::HUNCHMAN ||
					createrType == EntityType::RAVEN ||
					createrType == EntityType::SKELETON ||
					createrType == EntityType::BAT ||
					createrType == EntityType::ZOMBIE)
				{
					RandomItem(posX, posY);
				}
				else
					return new BigHeart(posX, posY);
}

void PlayScene::SlayEnemies(UINT i, Weapon* weapon, int scoreGive)
{
	if (weapon->GetType() == EntityType::BOOMERANG)
	{
		Boomerang* bmr = dynamic_cast<Boomerang*>(weapon);
		if (!bmr->GetIsDidDamageTurn1() && bmr->GetOwnerDirection() == bmr->GetDirection())
		{
			listObjects[i]->AddHealth(-weapon->GetDamage());
			bmr->SetIsDidDamageTurn1(true);
			listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::HITEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
			if (listObjects[i]->GetHealth() <= 0)
			{
				player->AddScore(scoreGive);
				listItems.push_back(DropItem(listObjects[i]->GetType(), listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
				listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::FIREEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
			}
		}
		if (!bmr->GetIsDidDamageTurn2() && bmr->GetOwnerDirection() != bmr->GetDirection())
		{
			listObjects[i]->AddHealth(-weapon->GetDamage());
			bmr->SetIsDidDamageTurn2(true);
			listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::HITEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
			if (listObjects[i]->GetHealth() <= 0)
			{
				player->AddScore(scoreGive);
				listItems.push_back(DropItem(listObjects[i]->GetType(), listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
				listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::FIREEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
			}
		}
	}
	else
		if (weapon->GetType() == EntityType::MORNINGSTAR)
		{
			MorningStar* ms = dynamic_cast<MorningStar*>(weapon);
			if (!ms->GetDidDamage())
			{
				listObjects[i]->AddHealth(-weapon->GetDamage());
				ms->SetDidDamage(true);
				listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::HITEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
				if (listObjects[i]->GetHealth() <= 0)
				{
					player->AddScore(scoreGive);
					listItems.push_back(DropItem(listObjects[i]->GetType(), listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
					listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::FIREEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
				}
			}
		}
		else
			if (weapon->GetType() == EntityType::AXE)
			{
				Axe* axe = dynamic_cast<Axe*>(weapon);
				if (!axe->GetDidDamage())
				{
					listObjects[i]->AddHealth(-weapon->GetDamage());
					axe->SetDidDamage(true);
					listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::HITEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
					if (listObjects[i]->GetHealth() <= 0)
					{
						player->AddScore(scoreGive);
						listItems.push_back(DropItem(listObjects[i]->GetType(), listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
						listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::FIREEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
					}
				}
			}
	else
	{
		if (listObjects[i]->GetHealth() == 1)	//Hit nay se chet 
		{
			player->AddScore(scoreGive);
			listItems.push_back(DropItem(listObjects[i]->GetType(), listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
			listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::FIREEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
		}
		listObjects[i]->AddHealth(-weapon->GetDamage());
		listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::HITEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
	}
}

void PlayScene::WeaponInteractObj(UINT i, Weapon* weapon)
{
	//Co 1 phuong an de delay DropItem la trigger Start timer o day, o update thi lien tuc check timer de push
	//Van de la timer co hoat dong dung khong khi giet nhieu target 1 luc ?	//Phuong an la dat timer trong class cua item
	switch (listObjects[i]->GetType())
	{
	case EntityType::BAT:
		SlayEnemies(i, weapon, BAT_SCORE_GIVEN);
		break;
	case EntityType::DARKENBAT:
		SlayEnemies(i, weapon, DARKBAT_SCORE_GIVEN);
		break;
	case EntityType::GHOST:
	{
		SlayEnemies(i, weapon, GHOST_SCORE_GIVEN);
		Ghost* ghost = dynamic_cast<Ghost*>(listObjects[i]);
		ghost->TriggerHurt(true);
		break; 
	}
	case EntityType::ZOMBIE:
		SlayEnemies(i, weapon, ZOMBIE_SCORE_GIVEN);
		zombieCounter--;
		if (zombieCounter == 0)
		{
			spawningZombieTimer->Start();
			triggerSpawnZombie = true;
			isTimeToSpawnZombie = false;
		}
		break;
	case EntityType::KNIGHT:
	{
		SlayEnemies(i, weapon, KNIGHT_SCORE_GIVEN);
		Knight* k9 = dynamic_cast<Knight*>(listObjects[i]);
		k9->TriggerHurt(true);
		break; 
	}
	case EntityType::HUNCHMAN:
		SlayEnemies(i, weapon, HUNCHMAN_SCORE_GIVEN);
		break;
	case EntityType::SKELETON:
		SlayEnemies(i, weapon, SKELETON_SCORE_GIVEN);
		break;
	case EntityType::RAVEN:
		SlayEnemies(i, weapon, RAVEN_SCORE_GIVEN);
		break;
	case EntityType::TORCH:
	{
		Torch* torch = dynamic_cast<Torch*>(listObjects[i]);	//Extension cua DropItem
		listObjects[i]->AddHealth(-weapon->GetDamage());
		listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::HITEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
		listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::FIREEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
		listItems.push_back(DropItem(listObjects[i]->GetType(), listObjects[i]->GetPosX(), listObjects[i]->GetPosY(), torch->GetIdTorch()));
		break;
	}
	case EntityType::CANDLE:
	{
		if (weapon->GetType() == EntityType::POKEBALL) return;
		Candle* candle = dynamic_cast<Candle*>(listObjects[i]);	//Extension cua DropItem
		listObjects[i]->AddHealth(-weapon->GetDamage());
		listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::HITEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
		listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::FIREEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
		listItems.push_back(DropItem(listObjects[i]->GetType(), listObjects[i]->GetPosX(), listObjects[i]->GetPosY(), candle->GetIdCandle()));
		break;
	}
	case EntityType::BREAKABLEBRICK:
	{
		if (weapon->GetType() == EntityType::MORNINGSTAR)
		{
			if (idStage == STAGE_2_1)
			{
				easterEgg_Stage2_1++;
			}
			else 
				if (idStage == STAGE_2_2)
				{
					easterEgg_Stage2_2++;
				}
				else
				{
					listItems.push_back(DropItem(listObjects[i]->GetType(), listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
				}
			listObjects[i]->AddHealth(-1);
			listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::HITEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
			listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::BRICKEXPLODEEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY(), EXPLODE_TYPE1));
			listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::BRICKEXPLODEEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY(), EXPLODE_TYPE2));
			listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::BRICKEXPLODEEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY(), EXPLODE_TYPE3));
			listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::BRICKEXPLODEEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY(), EXPLODE_TYPE4));
		}
		break;
	}
	default:
		break;
	}
}

void PlayScene::SetSubWeaponDone(UINT i, Weapon* weapon)
{
	if (listObjects[i]->GetType() == EntityType::BAT ||
		listObjects[i]->GetType() == EntityType::ZOMBIE ||
		listObjects[i]->GetType() == EntityType::TORCH ||
		listObjects[i]->GetType() == EntityType::DARKENBAT ||
		listObjects[i]->GetType() == EntityType::KNIGHT ||
		listObjects[i]->GetType() == EntityType::BREAKABLEBRICK ||
		listObjects[i]->GetType() == EntityType::HUNCHMAN ||
		listObjects[i]->GetType() == EntityType::GHOST ||
		listObjects[i]->GetType() == EntityType::SKELETON ||
		listObjects[i]->GetType() == EntityType::RAVEN)
	{
		if (player->GetPlayerSupWeaponType() == EntityType::DAGGER)
			weapon->SetIsDone(true);
	}
}

void PlayScene::WeaponCollision()
{
	if (!player->GetPlayerMainWeapon()->GetIsDone() || player->GetPlayerSupWeapon() != NULL)	//Hoac dang dung vu khi chinh, hoac dang co vu khi phu
	{
		for (UINT i = 0; i < listObjects.size(); i++)
		{
			if (player->GetPlayerMainWeapon()->IsCollidingObject(listObjects[i]))	//Main weapon va cham voi obj
			{
				WeaponInteractObj(i, player->GetPlayerMainWeapon());
			}
			else
				if (player->GetPlayerSupWeapon() != NULL //Dong nay de dam bao dong ben duoi khong bi break
					&& player->GetPlayerSupWeapon()->IsCollidingObject(listObjects[i]))
				{
					WeaponInteractObj(i, player->GetPlayerSupWeapon());
					SetSubWeaponDone(i, player->GetPlayerSupWeapon());
				}
				else 
					if (player->IsGettingDouble() && player->GetPlayerSupWeaponAtDouble() != NULL
						&& player->GetPlayerSupWeaponAtDouble()->IsCollidingObject(listObjects[i]))
					{
						WeaponInteractObj(i, player->GetPlayerSupWeaponAtDouble());	
						SetSubWeaponDone(i, player->GetPlayerSupWeaponAtDouble());
					}
					else
						if (player->IsGettingTriple() && player->GetPlayerSupWeaponAtTriple() != NULL
							&& player->GetPlayerSupWeaponAtTriple()->IsCollidingObject(listObjects[i]))
						{
							WeaponInteractObj(i, player->GetPlayerSupWeaponAtTriple());	
							SetSubWeaponDone(i, player->GetPlayerSupWeaponAtTriple());
						}
		}
	}
}

void PlayScene::PlayerCollideBone()
{
	for (UINT i = 0; i < listObjects.size(); i++)
	{
		if (listObjects[i]->GetType() == EntityType::SKELETON)
		{
			Skeleton* skeleton = dynamic_cast<Skeleton*>(listObjects[i]);
			if (skeleton->GetBone()->IsCollidingObject(player))
			{
				if (!player->IsImmortaling())
				{
					player->AddHealth(-skeleton->GetBone()->GetDamage());
					player->StartHurtingTimer();
					player->StartImmortalingTimer();
					player->SetImmortal(true);
					player->SetState(PLAYER_STATE_HURTING);
				}
			}
		}
	}
}

void PlayScene::PlayerCollideItem()
{
	for (UINT i = 0; i < listItems.size(); i++)
	{
		if (!listItems[i]->GetIsDone())
		{
			if (player->IsCollidingObject(listItems[i]))
			{
				switch (listItems[i]->GetType())
				{
				case EntityType::MONEYBAGRED:
					player->AddScore(BAGS_RED_SCORE_GIVEN);
					listItems[i]->SetIsDone(true);
					listEffects.push_back(CreateEffect(EntityType::MONEYBAGRED, EntityType::ADDSCOREEFFECT, listItems[i]->GetPosX(), listItems[i]->GetPosY() - PLAYER_BBOX_HEIGHT));
					break;
				case EntityType::MONEYBAGWHITE:
					player->AddScore(BAGS_WHITE_SCORE_GIVEN);
					listItems[i]->SetIsDone(true);
					listEffects.push_back(CreateEffect(EntityType::MONEYBAGWHITE, EntityType::ADDSCOREEFFECT, listItems[i]->GetPosX(), listItems[i]->GetPosY() - PLAYER_BBOX_HEIGHT));
					break;
				case EntityType::MONEYBAGBLUE:
					player->AddScore(BAGS_BLUE_SCORE_GIVEN);
					listItems[i]->SetIsDone(true);
					listEffects.push_back(CreateEffect(EntityType::MONEYBAGBLUE, EntityType::ADDSCOREEFFECT, listItems[i]->GetPosX(), listItems[i]->GetPosY() - PLAYER_BBOX_HEIGHT));
					break;
				case EntityType::SMALLHEART:
					player->AddMana(SMALLHEART_MANA_GIVEN);
					listItems[i]->SetIsDone(true);
					break;
				case EntityType::BIGHEART:
					player->AddMana(BIGHEART_MANA_GIVEN);
					listItems[i]->SetIsDone(true);
					break;
				case EntityType::YUMMICHICKENLEG:
					if (player->GetHealth() <= PLAYER_MAXHEALTH - CHICKEN_HP_RESTORE)
						player->AddHealth(CHICKEN_HP_RESTORE);
					else
						player->SetHealth(PLAYER_MAXHEALTH);
					listItems[i]->SetIsDone(true);
					break;
				case EntityType::CROWN:
					player->AddScore(CROWN_SCORE_GIVEN);
					listItems[i]->SetIsDone(true);
					listEffects.push_back(CreateEffect(EntityType::CROWN, EntityType::ADDSCOREEFFECT, listItems[i]->GetPosX(), listItems[i]->GetPosY() - PLAYER_BBOX_HEIGHT));
					break;
				case EntityType::ITEMEXTRASHOT:
				{
					ExtraShot* exs = dynamic_cast<ExtraShot*>(listItems[i]);
					if (exs->GetTypeExtra() == EXTRASHOT_LEVEL2)
						player->SetGettingDouble(true);
					else
						if (exs->GetTypeExtra() == EXTRASHOT_LEVEL3)
						{
							player->SetGettingDouble(true);
							player->SetGettingTriple(true);
						}
					listItems[i]->SetIsDone(true);
					break; 
				}
				case EntityType::UPGRADEMORNINGSTAR:
				{
					MorningStar* morningStarWeapon = dynamic_cast<MorningStar*>(player->GetPlayerMainWeapon());
					player->UpgradingMorningStar();
					morningStarWeapon->UpLevel();
					listItems[i]->SetIsDone(true);
					break;
				}
				case EntityType::ITEMDAGGER:
				{
					player->SetPlayerSupWeaponType(EntityType::DAGGER);
					listItems[i]->SetIsDone(true);
					break;
				}
				case EntityType::ITEMBOOMERANG:
				{
					player->SetPlayerSupWeaponType(EntityType::BOOMERANG);
					listItems[i]->SetIsDone(true);
					break;
				}
				case EntityType::ITEMAXE:
				{
					player->SetPlayerSupWeaponType(EntityType::AXE);
					listItems[i]->SetIsDone(true);
					break;
				}
				case EntityType::ITEMWATERPOTION:
				{
					player->SetPlayerSupWeaponType(EntityType::WATERPOTION);
					listItems[i]->SetIsDone(true);
					break;
				}
				case EntityType::ITEMSTOPWATCH:
				{
					player->SetPlayerSupWeaponType(EntityType::STOPWATCH);
					listItems[i]->SetIsDone(true);
					break;
				}
				case EntityType::CROSS:
				{
					if (!triggerCrossTimer)
					{
						crossTimer->Start();
						triggerCrossTimer = true;
						for (UINT i = 0; i < listObjects.size(); i++)
						{
							//Them if xet trong tam` camera 
							//Thuc ra da~ duoc xet tren Grid nhung tam` Grid xa hon camera
							if (listObjects[i]->GetType() == EntityType::BAT ||
								listObjects[i]->GetType() == EntityType::DARKENBAT ||
								listObjects[i]->GetType() == EntityType::ZOMBIE ||
								listObjects[i]->GetType() == EntityType::KNIGHT ||
								listObjects[i]->GetType() == EntityType::HUNCHMAN ||
								listObjects[i]->GetType() == EntityType::GHOST ||
								listObjects[i]->GetType() == EntityType::RAVEN ||
								listObjects[i]->GetType() == EntityType::SKELETON)
							{
								listObjects[i]->AddHealth(-listObjects[i]->GetHealth());
								if (listObjects[i]->GetType() == EntityType::ZOMBIE)
								{
									zombieCounter--;
									if (zombieCounter == 0)
									{
										spawningZombieTimer->Start();
										triggerSpawnZombie = true;
										isTimeToSpawnZombie = false;
									}
								}
								listItems.push_back(DropItem(listObjects[i]->GetType(), listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
								listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::HITEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
								listEffects.push_back(CreateEffect(listObjects[i]->GetType(), EntityType::FIREEFFECT, listObjects[i]->GetPosX(), listObjects[i]->GetPosY()));
							}
						}
					}
					listItems[i]->SetIsDone(true);
					break;
				}
				case EntityType::INVIPOTION:
				{
					player->StartInvisible();
					listItems[i]->SetIsDone(true);
					break;
				}
				case EntityType::ITEMPOKEBALL:
				{
					player->SetPlayerSupWeaponType(EntityType::POKEBALL);
					listItems[i]->SetIsDone(true);
					break;
				}
				default:
					break;
				}
			}
		}
	}
}

bool PlayScene::PlayerPassingStage(float DistanceXWant, int directionGo)
{
	if (directionGo == 1)	//cua o ben phai
	{
		if (player->GetPosX() < DistanceXWant)
		{
			player->SetDirection(directionGo);
			player->SetState(PLAYER_STATE_PASSING_STAGE);
			return false;
		}
	}
	else
		if (directionGo == -1)	//cua o ben trai
		{
			if (player->GetPosX() > DistanceXWant)
			{
				player->SetDirection(directionGo);
				player->SetState(PLAYER_STATE_PASSING_STAGE);
				return false;
			}
		}
	return true;
}

void PlayScene::PlayerGotGate()
{
	for (UINT i = 0; i < listObjects.size(); i++)
	{
		if (listObjects[i]->GetType() == EntityType::GATE)
		{
			if (player->IsCollidingObject(listObjects[i]))
			{
				Gate* gate = dynamic_cast<Gate*>(listObjects[i]);
				int tempMap = gate->GetIdScene() * STAGE_1;
				float tempPosX = gate->newSimonPosX;
				float tempPosY = gate->newSimonPosY;
				int tempState = gate->newSimonState;
				bool tempNeed = gate->isNeedResetCam;
				if (idStage == STAGE_1)
				{
					if (!PlayerPassingStage(listObjects[i]->GetPosX() + 20.0f, 1))
						return;
				}
				else if (idStage == STAGE_2_2 && tempMap == STAGE_3_1)
				{
					if (!PlayerPassingStage(listObjects[i]->GetPosX(), -1))
						return;
				}
				else if (idStage == STAGE_3_2 && tempMap == STAGE_4)
				{
					if (!PlayerPassingStage(listObjects[i]->GetPosX() + 10.0f, 1))
						return;
				}
				Unload();
				if(tempNeed)
					gameCamera->SetCamPos(0, 0);
				ChooseMap(tempMap);
				player->SetPosition(tempPosX, tempPosY);
				player->SetVx(0);
				player->SetVy(0);
				player->SetState(tempState);
			}
		}
	}
}

void PlayScene::EasterEggEvent()
{
	if (idStage == STAGE_2_1)
	{
		if (easterEgg_Stage2_1 == 2)
		{
			listItems.push_back(DropItem(EntityType::NONE, HIDDEN_CROWN_POS_X_STAGE_2_1, HIDDEN_CROWN_POS_Y_STAGE_2_1));
			easterEgg_Stage2_1 = 0;
		}
	}
	else
		if (idStage == STAGE_2_2)
		{
			if (easterEgg_Stage2_2 == 1)
			{
				listItems.push_back(DropItem(EntityType::NONE, HIDDEN_EXTRASHOT_POS_X_STAGE_2_2, HIDDEN_EXTRASHOT_POS_Y_STAGE_2_2));
				easterEgg_Stage2_2 = 0;
			}
		}
		else
			if (idStage == STAGE_3_2)
			{
				if (player->GetPosX() > EASTER_EGG_ACTIVATE_AREA_X_STAGE_3_2 && 
					player->GetPosX() < EASTER_EGG_ACTIVATE_AREA_X_STAGE_3_2 + 20 && 
					player->IsSitting() && 
					easterEgg_Stage3_2 == 1)
				{
					listItems.push_back(DropItem(EntityType::NONE, HIDDEN_CROWN_POS_X_STAGE_3_2, HIDDEN_CROWN_POS_Y_STAGE_3_2));
					easterEgg_Stage3_2 = 0;
				}
			}
}

void PlayScene::PlayerInSightGhost()
{
	if (idStage == STAGE_3_1)
	{
		if (player->GetPosX() > GHOST_ACTIVATE_AREA_X_STAGE_3_1 && player->GetPosX() < GHOST_ACTIVATE_AREA_X_STAGE_3_1 + 10)
		{
			if (triggerSpawnGhost)
			{
				listObjectsToGrid.push_back(new Ghost(1350, 345, player));
				triggerSpawnGhost = false;
			}
		}
	}
	else
		if (idStage == STAGE_3_2)
		{
			if (player->GetPosX() > GHOST_ACTIVATE_AREA_X_STAGE_3_2 && player->GetPosX() < GHOST_ACTIVATE_AREA_X_STAGE_3_2 + 10)
			{
				if (triggerSpawnGhost)
				{
					listObjectsToGrid.push_back(new Ghost(200, 200, player));
					triggerSpawnGhost = false;
				}
			}
		}
}

void PlayScene::CountingZombie()
{
	for (UINT i = 0; i < listObjects.size(); i++)
	{
		if (listObjects[i]->GetPosX() < SCREEN_WIDTH * 1.9f && listObjects[i]->GetPosX() > 1)
		{
			if (listObjects[i]->GetType() == EntityType::ZOMBIE && (listObjects[i]->GetPosX() < 10 || listObjects[i]->GetPosX() > SCREEN_WIDTH * 1.85f))
			{
				if(zombieCounter > 0)	//
					zombieCounter--;
				if (zombieCounter == 0)
				{
					spawningZombieTimer->Start();
					triggerSpawnZombie = true;
					isTimeToSpawnZombie = false;
				}
			}
		}
	}
}

void PlayScene::SpawnZombie()
{
	if (isTimeToSpawnZombie)
	{
		if (delaySpawningZombieTimer->IsTimeUp())
		{
			if (zombieCounter < 3)
			{
				int randomAbove = rand() % 100;
				if (randomAbove <= 50)
					listObjectsToGrid.push_back(new Zombie(SCREEN_WIDTH, SCREEN_HEIGHT - 290, -1));	//spawn o bac tren
				else
				{
					int randomRight = rand() % 100;
					if (randomRight <= 50)
						listObjectsToGrid.push_back(new Zombie(SCREEN_WIDTH, SCREEN_HEIGHT - 120, -1));	//spawn ben phai
					else
						listObjectsToGrid.push_back(new Zombie(20, SCREEN_HEIGHT - 120, 1));	//spawn ben trai
				}
				zombieCounter++;
				if (zombieCounter >= 3)
				{
					isTimeToSpawnZombie = false;	
					triggerSpawnZombie = false;		
				}
				delaySpawningZombieTimer->Start();
			}
			else
				zombieCounter--;
		}
	}
	else
	{
		if (triggerSpawnZombie)
		{
			if (spawningZombieTimer->IsTimeUp())
			{
				isTimeToSpawnZombie = true;
			}
		}
	}
}

void PlayScene::SpawnBat()
{
	if (isTimeToSpawnBat) {
		if (spawningBatTimer->IsTimeUp())
		{
			int randomY = rand() % 290 + 90;
			int randomX = rand() % 100;
			if (randomX <= 50)
				listObjectsToGrid.push_back(new Bat(SCREEN_WIDTH * 1.25f, SCREEN_HEIGHT - randomY, -1));
			else
				listObjectsToGrid.push_back(new Bat(1, SCREEN_HEIGHT - randomY, 1));

			spawningBatTimer->Reset(SPAWNING_BAT_DELAY + (rand() % 3000));
			triggerSpawnBat = true;	//Dung 1 cho thi se spawn bat mai mai, cho den khi di den khu vuc ma trigger o do = false
		}
		if (triggerSpawnBat)
		{
			spawningBatTimer->Start();
			triggerSpawnBat = false;
		}
	}
}

void PlayScene::Update(DWORD dt)
{
	GetObjectFromGrid();
#pragma region Camera
	float cx = player->GetPosX();
	
	if (player->GetPosX() >= camMaxWidth)
	{
		cx -= SCREEN_WIDTH / 2 - (camMaxWidth - player->GetPosX());
	}
	else
	{
		if (player->GetPosX() < SCREEN_WIDTH / 2)
			cx = 0;
		else
			cx -= SCREEN_WIDTH / 2;
	}
	gameCamera->SetCamPos(cx, 0.0f);//cy khi muon camera move theo y player //castlevania chua can
#pragma endregion

	if(!player->GetPlayerMainWeapon()->GetIsDone() ||
		(player->GetPlayerSupWeapon() != NULL && !player->GetPlayerSupWeapon()->GetIsDone()) ||
		(player->GetPlayerSupWeaponAtDouble() != NULL && !player->GetPlayerSupWeaponAtDouble()->GetIsDone()) ||
		(player->GetPlayerSupWeaponAtTriple() != NULL && !player->GetPlayerSupWeaponAtTriple()->GetIsDone()))
		WeaponCollision();
	if(listItems.size() > 0)
		PlayerCollideItem();
	PlayerGotGate(); 
	EasterEggEvent();
	if (idStage == STAGE_3_1 || idStage == STAGE_3_2)
	{
		PlayerInSightGhost();
		PlayerCollideBone();
	}
	if (idStage == STAGE_4 && player->GetPosX() < 800)
	{
		SpawnBat();
		CountingZombie();
		SpawnZombie();
	}

	if (!player->IsTimeStop())
		gameTime->Update(dt);
	if (gameTime->GetTime() >= SCENEGAME_GAMETIMEMAX)
		player->AddHealth(-player->GetHealth());

	gameUI->Update(cx + BLACKBOARD_DISTANCE_FROM_CAM_X, BLACKBOARD_POS_Y, player->GetHealth(), 16);	//move posX follow camera

	gameGrid->ResetGrid(listObjectsToGrid);

	if (player->IsRespawning() && !triggerResetGame)
		ResetGame();
	else if (!player->IsRespawning()) 
		triggerResetGame = false;

	if (triggerCrossTimer && crossTimer->IsTimeUp())
	{
		triggerCrossTimer = false;
		crossTimer->Reset();
	}

#pragma region Objects Updates
	vector<LPGAMEENTITY> coObjects;
	for (int i = 0; i < listObjects.size(); i++)
		coObjects.push_back(listObjects[i]);
	player->Update(dt, &coObjects);
	for (int i = 0; i < listObjects.size(); i++)
		if(!listObjects[i]->isStaticObj)	//Ignore Static Obstacle
			if (!player->IsUpgrading() && !player->IsTimeStop())
				listObjects[i]->Update(dt, &coObjects);
	for (int i = 0; i < listEffects.size(); i++)
		listEffects[i]->Update(dt);
	for (int i = 0; i < listItems.size(); i++)
		listItems[i]->Update(dt, &listObjects);
#pragma endregion
}

void PlayScene::Render()
{
	gameMap->Draw();
	for (int i = 0; i < listObjects.size(); i++)
		listObjects[i]->Render();
	for (int i = 0; i < listEffects.size(); i++)
		listEffects[i]->Render();
	for (int i = 0; i < listItems.size(); i++)
		listItems[i]->Render();
	player->Render();

	int realIdStage = idStage / STAGE_1;
	gameUI->Render(realIdStage, SCENEGAME_GAMETIMEMAX - gameTime->GetTime(), player);
	
}


bool PlayScene::PlayerCollideStairs()
{
	player->SetCannotMoveDown(false);
	return player->SimonCollideWithStair(&listStairs);
}

bool PlayScene::PlayerCollideStairsEx()
{
	return player->SimonCollideWithStair(&listStairsEx);
}

void PlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	Player* simon = ((PlayScene*)scence)->player;
	PlayScene* playScene = dynamic_cast<PlayScene*>(scence);
	vector<LPGAMEENTITY> listObj = ((PlayScene*)scence)->listObjects;

	switch (KeyCode)
	{
	case DIK_ESCAPE:
		DestroyWindow(Game::GetInstance()->GetWindowHandle());
	case DIK_1:	//test auto
		break;
	case DIK_2:	//test jump stage
		playScene->Unload();
		playScene->ChooseMap(playScene->idStage + STAGE_1);
		if (playScene->idStage == STAGE_2_1)
		{
			simon->SetPosition(400, 150);
		}
		else
			if (playScene->idStage == STAGE_2_2)
			{
				simon->SetPosition(800, 150);
			}
			else 
				if (playScene->idStage == STAGE_3_1)
				{
					simon->SetPosition(1440, 350);
				}
				else 
					if (playScene->idStage == STAGE_3_2)
					{
						simon->SetPosition(304, 200);
					}
					else
					{
						simon->SetPosition(304, 200);
					}

		simon->SetVx(0);
		simon->SetVy(0);
		simon->SetState(PLAYER_STATE_IDLE);
		break;
	case DIK_3:
		if (simon->GetPlayerSupWeaponType() == EntityType::NONE || simon->GetPlayerSupWeaponType() == EntityType::STOPWATCH)
			simon->SetPlayerSupWeaponType(EntityType::DAGGER);
		else if (simon->GetPlayerSupWeaponType() == EntityType::DAGGER)
			simon->SetPlayerSupWeaponType(EntityType::AXE);
		else if (simon->GetPlayerSupWeaponType() == EntityType::AXE)
			simon->SetPlayerSupWeaponType(EntityType::BOOMERANG);
		else if (simon->GetPlayerSupWeaponType() == EntityType::BOOMERANG)
			simon->SetPlayerSupWeaponType(EntityType::WATERPOTION);
		else if (simon->GetPlayerSupWeaponType() == EntityType::WATERPOTION)
			simon->SetPlayerSupWeaponType(EntityType::STOPWATCH);
		break;
	case DIK_4:
		simon->AddHealth(-4);
		break;
	case DIK_5:
		simon->SetHealth(16);
		break;
	case DIK_6:
		simon->StartInvisible();
		break;
	case DIK_R:
		for (int i = 0; i < listObj.size(); i++)
		{
			if (listObj[i]->GetBBARGB() == 0)
				listObj[i]->SetBBARGB(200);
			else
				listObj[i]->SetBBARGB(0);
		}

		if (simon->GetBBARGB() == 0)
			simon->SetBBARGB(200);
		else
			simon->SetBBARGB(0);

		if (simon->GetPlayerMainWeapon()->GetBBARGB() == 0)
			simon->GetPlayerMainWeapon()->SetBBARGB(200);
		else
			simon->GetPlayerMainWeapon()->SetBBARGB(0);
		break;
	case DIK_C:
		if (simon->IsDeadYet() || simon->IsRespawning() || simon->IsAttacking() || simon->IsSitting() || simon->IsHurting() || simon->IsUpgrading() || simon->IsPassingStage() || simon->IsOnStairs())
			return;
		simon->SetState(PLAYER_STATE_JUMPING);
		break;
	case DIK_X:
		if (simon->IsDeadYet() || simon->IsRespawning() || simon->IsAttacking() || simon->IsHurting() || simon->IsUpgrading() || Game::GetInstance()->IsKeyDown(DIK_UP) || simon->IsPassingStage())	//Up + X khong Whip duoc nua
			return;
		if (simon->GetState() == PLAYER_STATE_GOING_UP_STAIRS)
			simon->SetState(PLAYER_STATE_UPSTARIS_ATTACK);
		else if (simon->GetState() == PLAYER_STATE_GOING_DOWN_STAIRS)
			simon->SetState(PLAYER_STATE_DOWNSTAIRS_ATTACK);
		else if(!simon->IsSitting() && !simon->IsOnStairs())
			simon->SetState(PLAYER_STATE_ATTACKING);
		else if(simon->IsSitting() && !simon->IsOnStairs())
			simon->SetState(PLAYER_STATE_SITTING_ATTACK);
		break;
	}
}

void PlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void PlayScenceKeyHandler::KeyState(BYTE *states)
{
	Player* simon = ((PlayScene*)scence)->player;
	PlayScene* playScene = dynamic_cast<PlayScene*>(scence);
	vector<LPGAMEENTITY> listObjects = ((PlayScene*)scence)->listObjects;

	if ((simon->GetState() == PLAYER_STATE_GOING_UP_STAIRS || 
		simon->GetState() == PLAYER_STATE_GOING_DOWN_STAIRS ||
		simon->GetState() == PLAYER_STATE_UPSTARIS_ATTACK ||
		simon->GetState() == PLAYER_STATE_DOWNSTAIRS_ATTACK)
		&& !simon->GetAnimationSet()->at(simon->GetState())->IsRenderOver())
		return;

	if (simon->GetIsWalkingOnStairs() || simon->IsDeadYet() || simon->IsRespawning() ||  simon->IsHurting() || simon->IsUpgrading() || simon->IsPassingStage())
	{
		return;
	}

	if (Game::GetInstance()->IsKeyDown(DIK_UP) && Game::GetInstance()->IsKeyDown(DIK_X) && !simon->IsAttacking() && !simon->IsOnStairs())
	{
		if (simon->GetPlayerSupWeaponType() != EntityType::NONE)	//Neu chua nhat duoc vu khi phu thi khong attack
		{
			if (!simon->IsSitting())
				simon->SetState(PLAYER_STATE_SUPWEAPON_ATTACK);
			else
				simon->SetState(PLAYER_STATE_SUPWEAPON_SIT_ATTACK);
		}
	}

	if (simon->IsAttacking() || simon->IsJumping())
		return;

	if (Game::GetInstance()->IsKeyDown(DIK_DOWN))
	{
		if ((playScene->PlayerCollideStairsEx() && simon->GetCannotMoveDown()) || playScene->PlayerCollideStairs())
		{
			simon->PlayerDownStairs();
			return;
		}
		simon->SetState(PLAYER_STATE_SITTING);
		if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
			simon->SetDirection(1);
		else if (Game::GetInstance()->IsKeyDown(DIK_LEFT))
			simon->SetDirection(-1);
		return;				//Important return //Dont change state while sitting
	}
	else if (Game::GetInstance()->IsKeyDown(DIK_UP))
	{
		if (playScene->PlayerCollideStairs() || playScene->PlayerCollideStairsEx())
		{
			simon->SetCannotMoveDown(false);
			simon->PlayerUpStairs();
			return;
		}
		simon->SetState(PLAYER_STATE_IDLE);
		return;				//Important return //Dont change state while sitting
	}
	else if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
	{
		if ((playScene->PlayerCollideStairsEx() || playScene->PlayerCollideStairs()) && simon->IsOnStairs())
		{
			if (simon->GetStairsDirectionPlayerColliding() == 1)
				simon->PlayerUpStairs();
			else
				simon->PlayerDownStairs();

			return;
		}
		simon->SetDirection(1);
		simon->SetState(PLAYER_STATE_WALKING);
	}
	else if (Game::GetInstance()->IsKeyDown(DIK_LEFT))
	{
		if ((playScene->PlayerCollideStairsEx() || playScene->PlayerCollideStairs()) && simon->IsOnStairs())
		{
			if (simon->GetStairsDirectionPlayerColliding() == 1)
				simon->PlayerDownStairs();
			else
				simon->PlayerUpStairs();

			return;
		}
		simon->SetDirection(-1);
		simon->SetState(PLAYER_STATE_WALKING);
	}
	else
	{
		if (playScene->PlayerCollideStairsEx() || playScene->PlayerCollideStairs())
		{
			if (simon->PlayerStandOnStairs())
				return;
		}
		simon->SetState(PLAYER_STATE_IDLE);
	}

}

void PlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void PlayScene::_ParseSection_CLEARTEXTURES(string line)
{
	vector<string> tokens = split(line);
	int idClear = atoi(tokens[0].c_str());
	CTextures::GetInstance()->ClearAt(idClear);
	DebugOut(L"[INFO] Cleared Texture %d!\n", idClear);
}

void PlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void PlayScene::_ParseSection_CLEARSPRITES(string line)
{
	vector<string> tokens = split(line);
	int idClear = atoi(tokens[0].c_str());
	CSprites::GetInstance()->ClearAt(idClear);
	DebugOut(L"[INFO] Cleared Sprite %d!\n", idClear);
}

void PlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void PlayScene::_ParseSection_CLEARANIMATIONS(string line)
{
	vector<string> tokens = split(line);
	int idClear = atoi(tokens[0].c_str());
	CAnimations::GetInstance()->ClearAt(idClear);
	DebugOut(L"[INFO] Cleared Animation %d!\n", idClear);
}

void PlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations *animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

void PlayScene::_ParseSection_CLEARANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);
	int idClear = atoi(tokens[0].c_str());
	CAnimationSets::GetInstance()->ClearAt(idClear);
	DebugOut(L"[INFO] Cleared Animation Set %d!\n", idClear);
}

void PlayScene::_ParseSection_SCENEFILEPATH(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return;

	listSceneFilePath.push_back(ToLPCWSTR(tokens[0]));
	mapWidth = atoi(tokens[1].c_str());
	mapHeight = atoi(tokens[2].c_str());
	//Hien tai chi lay mapWidth/Height cua list cuoi cung` :P co the dem vo tung file scene rieng de phan biet (hoac khong can, camera co chay toi duoc dau)
}

void PlayScene::_ParseSection_TILEMAP(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 7) return;

	//idStage
	//mapFilePath
	//Row of Map
	//Column of Map
	//tilesetFilePath
	//Row of Tileset
	//Column of Tileset

	gameMap->LoadMap(atoi(tokens[0].c_str()), 
		ToLPCWSTR(tokens[1]), atoi(tokens[2].c_str()), atoi(tokens[3].c_str()),
		ToLPCWSTR(tokens[4]), atoi(tokens[5].c_str()), atoi(tokens[6].c_str()));

	camMaxWidth = atoi(tokens[7].c_str());
}

/*
	Parse a line in section [OBJECTS]
*/
void PlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	switch (object_type)
	{
	case OBJECT_TYPE_CANDLE:
	{
		int extras = atoi(tokens[3].c_str());
		listObjectsToGrid.push_back(new Candle(x, y, extras));
		break;
	}
	case OBJECT_TYPE_BRICK:
	{
		int extras = atoi(tokens[3].c_str());
		listObjectsToGrid.push_back(new Brick(x, y, extras));
		break;
	}
	case OBJECT_TYPE_TORCH:
	{
		int extras = atoi(tokens[3].c_str());
		listObjectsToGrid.push_back(new Torch(x, y, extras));
		break; 
	}
	case OBJECT_TYPE_GATE:
	{
		int extras1 = atoi(tokens[3].c_str());
		float extras2 = atoi(tokens[4].c_str());
		float extras3 = atoi(tokens[5].c_str());
		int extras4 = atoi(tokens[6].c_str());
		int extras5 = atoi(tokens[7].c_str());
		listObjectsToGrid.push_back(new Gate(x, y, extras1, extras2, extras3, extras4, extras5));
		break;
	}
	case OBJECT_TYPE_STAIRS:
	{
		int extras1 = atoi(tokens[3].c_str());
		int isEx = atoi(tokens[4].c_str());
		if(isEx == 0)
			listStairs.push_back(new Stairs(x, y, extras1));
		else
			listStairsEx.push_back(new Stairs(x, y, extras1));
		break;
	}
	case OBJECT_TYPE_DARKENBAT:
	{
		//player tao truoc nen kh sao
		int extras1 = atoi(tokens[3].c_str());
		listObjectsToGrid.push_back(new DarkenBat(x, y, extras1, player));
		break;
	}
	case OBJECT_TYPE_KNIGHT:
	{
		int extras1 = atoi(tokens[3].c_str());
		int extras2 = atoi(tokens[4].c_str());
		listObjectsToGrid.push_back(new Knight(x, y, extras1, extras2));
		break;
	}
	case OBJECT_TYPE_BREAKABLEBRICK:
	{
		int extras1 = atoi(tokens[3].c_str());
		listObjectsToGrid.push_back(new BreakableBrick(x, y, extras1));
		break;
	}
	case OBJECT_TYPE_MOVING_PLATFORM:
	{
		listObjectsToGrid.push_back(new MovingPlatform(x, y));
		break;
	}
	case OBJECT_TYPE_HUNCHMAN:
	{
		//player tao truoc nen kh sao
		listObjectsToGrid.push_back(new Hunchman(x, y, player));
		break;
	}
	case OBJECT_TYPE_RAVEN:
	{
		//player tao truoc nen kh sao
		int extras1 = atoi(tokens[3].c_str());
		int extras2 = atoi(tokens[4].c_str());
		listObjectsToGrid.push_back(new Raven(x, y, extras1, extras2, player));
		break;
	}
	case OBJECT_TYPE_SKELETON:
	{
		//player tao truoc nen kh sao
		listObjectsToGrid.push_back(new Skeleton(x, y, player));
		break;
	}
	case OBJECT_TYPE_BUSH:
	{
		//player tao truoc nen kh sao
		listObjectsToGrid.push_back(new Bush(x, y, player));
		break;
	}
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}
}

void PlayScene::LoadBaseTextures()
{
	DebugOut(L"[INFO] Start loading TEXTURES resources from : %s \n", texturesFilePath);

	ifstream f;
	f.open(texturesFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { 
			section = SCENE_SECTION_TEXTURES; continue; 
		}
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[SCENE]") {
			section = SCENE_SECTION_SCENEFILEPATH; continue;
		}
		
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_SCENEFILEPATH: _ParseSection_SCENEFILEPATH(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading TEXTURES resources %s\n", texturesFilePath);
}

void PlayScene::LoadSceneObjects()
{
	DebugOut(L"[INFO] Start loading scene111 resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[CLEARTEXTURES]") {
			section = SCENE_SECTION_CLEARTEXTURES; continue;
		}
		if (line == "[CLEARSPRITES]") {
			section = SCENE_SECTION_CLEARSPRITES; continue;
		}
		if (line == "[CLEARANIMATIONS]") {
			section = SCENE_SECTION_CLEARANIMATIONS; continue;
		}
		if (line == "[CLEARANIMATIONSETS]") {
			section = SCENE_SECTION_CLEARANIMATION_SETS; continue;
		}
		if (line == "[TEXTURES]") {
			section = SCENE_SECTION_TEXTURES; continue;
		}
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line == "[TILEMAP]") {
			section = SCENE_SECTION_TILEMAP; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_CLEARTEXTURES: _ParseSection_CLEARTEXTURES(line); break;
		case SCENE_SECTION_CLEARSPRITES: _ParseSection_CLEARSPRITES(line); break;
		case SCENE_SECTION_CLEARANIMATIONS: _ParseSection_CLEARANIMATIONS(line); break;
		case SCENE_SECTION_CLEARANIMATION_SETS: _ParseSection_CLEARANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_TILEMAP:	_ParseSection_TILEMAP(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void PlayScene::Unload()
{
	for (int i = 0; i < listObjects.size(); i++)
		delete listObjects[i];
	for (int i = 0; i < listEffects.size(); i++)
		delete listEffects[i];
	for (int i = 0; i < listItems.size(); i++)
		delete listItems[i];
	for (int i = 0; i < listStairs.size(); i++)
		delete listStairs[i];
	for (int i = 0; i < listStairsEx.size(); i++)
		delete listStairsEx[i];
	listObjectsToGrid.clear();
	listObjectsFromGrid.clear();
	listObjects.clear();
	listEffects.clear();
	listItems.clear();
	listStairs.clear();
	listStairsEx.clear();
}

void PlayScene::ResetGame()
{
	listObjectsToGrid.clear();
	listObjectsFromGrid.clear();
	listObjects.clear();

	ChooseMap(idStage);

	gameTime->ResetGameTime();

	player->SetPlayerSupWeaponType(EntityType::NONE);
	player->SetMana(55);
	player->AddScore(-player->GetScore());

	triggerResetGame = true;
}
