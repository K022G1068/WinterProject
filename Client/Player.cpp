#include "Player.h"

Player::Player()
{
	ClientInterface::OnUserCreate();
	this->p_Shake.IsShaking = false;
	this->p_Shake.shakePos = { 0.0f,0.0f };
	this->p_Shake.shakeTime = maxShakeTime;

	this->p_Square = { 0 };
	this->p_SquareCells = { 0 };

	//Initialize Easing
	this->p_Easing.time = 0;
	this->p_Easing.startPos = 0;
	this->p_Easing.duration = 0.2f;
	this->p_Easing.change = 10;

	this->canDash[0] = false;
	this->canDash[1] = false;

	mapObjects[nPlayerID].p_Vel.x = 0.0f;
	mapObjects[nPlayerID].p_Vel.y = 0.0f;
	mapObjects[nPlayerID].p_OnGround = false;

	//Count elapsedTime
	m_tp1 = std::chrono::system_clock::now();
	m_tp2 = std::chrono::system_clock::now();

}

Player::~Player()
{

}

void Player::Move2(char* keys, char* preKeys, float fElapsedTime)
{
	
	mapObjects[nPlayerID].p_Vel.x = 0.0f;
	//mapObjects[nPlayerID].p_Vel.y = 0.0f;
	//Gravity
	mapObjects[nPlayerID].p_Vel.y += 400.0f * fElapsedTime;
	
	//Clamp
	if (mapObjects[nPlayerID].p_Vel.y >= 672.0f)
	{
		mapObjects[nPlayerID].p_Vel.y = 672.0f;
	}

	mapObjects[nPlayerID].p_Old_Pos.x = mapObjects[nPlayerID].p_Pos.x;
	mapObjects[nPlayerID].p_Old_Pos.y = mapObjects[nPlayerID].p_Pos.y;

	if (keys[DIK_D])
	{
		mapObjects[nPlayerID].facing = RIGHT;
		mapObjects[nPlayerID].p_Vel.x = 100.0f;
	}
	if (keys[DIK_A])
	{
		mapObjects[nPlayerID].facing = LEFT;
		mapObjects[nPlayerID].p_Vel.x = -100.0f;
	}
	if (keys[DIK_W])
	{
		mapObjects[nPlayerID].p_Vel.y = -100.0f;
	}
	if (keys[DIK_S])
	{
		mapObjects[nPlayerID].p_Vel.y = 100.0f;
	}
	if (keys[DIK_SPACE] && mapObjects[nPlayerID].canJump)
	{
		mapObjects[nPlayerID].p_OnGround = false;
		mapObjects[nPlayerID].p_Vel.y = -250.0f;
		mapObjects[nPlayerID].canJump = false;
	}
	if (mapObjects[nPlayerID].p_OnGround == 1)
	{
		mapObjects[nPlayerID].canJump = true;
	}
	if (keys[DIK_R])
	{
		mapObjects[nPlayerID].p_Pos.y = 50.0f;
		mapObjects[nPlayerID].p_Pos.x = 50.0f;
		mapObjects[nPlayerID].p_Vel.y = 0.0f;
		mapObjects[nPlayerID].p_Vel.x = 0.0f;

	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Dash
	if (p_Easing.time <= p_Easing.duration)
	{
		p_Easing.time += 0.01;
	}
	else
	{
		canDash[0] = false;
		canDash[1] = false;

	}
	if (keys[DIK_Q] && !keys[DIK_A])
	{
		canDash[0] = true;
		canDash[1] = false;
	}
	else if (keys[DIK_Q] && keys[DIK_A])
	{
		canDash[1] = true;
		canDash[0] = false;
	}
	if (canDash[0])
	{
		mapObjects[nPlayerID].p_Vel.x += EaseInOutQuad(p_Easing) * 100.0f;

	}
	else if (canDash[1])
	{
		mapObjects[nPlayerID].p_Vel.x -= EaseInOutQuad(p_Easing) * 100.0f;
	}

	else
	{
		p_Easing.time = 0;
		p_Easing.change = 10;
		p_Easing.startPos = 0;
	}
	/// <summary>
	/// /////////////////////////////////////////////////////////////////////////////////////////////
	/// </summary>
	/// <param name="keys"></param>
	/// <param name="preKeys"></param>
	/// <param name="fElapsedTime"></param>

	float p_newPosX = mapObjects[nPlayerID].p_Pos.x + mapObjects[nPlayerID].p_Vel.x * fElapsedTime;
	float p_newPosY = mapObjects[nPlayerID].p_Pos.y + mapObjects[nPlayerID].p_Vel.y * fElapsedTime;
	TilesCheck(p_newPosX, mapObjects[nPlayerID].p_Pos.y);

	if (mapObjects[nPlayerID].p_Vel.x < 0)
	{
		if (p_SquareCells.topLeft.y != p_SquareCells.bottomLeft.y)
		{
			if (map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE)][(int)(p_SquareCells.topLeft.x)] != NONE || map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y + P_BLOCK_SIZE) / BLOCK_SIZE)][(int)(p_SquareCells.bottomLeft.x)] != NONE)
			{
				mapObjects[nPlayerID].p_Vel.x = 0;
				Novice::ScreenPrintf(50, 50, "BUMPED 11");
			}
			else
			{
				mapObjects[nPlayerID].p_Pos.x = p_newPosX;
			}
		}
		else if (p_SquareCells.topLeft.y == p_SquareCells.bottomLeft.y)
		{
			if (map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE)][(int)(p_SquareCells.topLeft.x)] != NONE || map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y + P_BLOCK_SIZE) / BLOCK_SIZE) - 1][(int)(p_SquareCells.bottomLeft.x)] != NONE)
			{
				mapObjects[nPlayerID].p_Vel.x = 0;
				Novice::ScreenPrintf(50, 50, "BUMPED 12");
			}
			else
			{
				mapObjects[nPlayerID].p_Pos.x = p_newPosX;
			}
		}
	}
	else if (mapObjects[nPlayerID].p_Vel.x > 0)
	{
		if (p_SquareCells.topLeft.y != p_SquareCells.bottomLeft.y)
		{
			if (map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE)][(int)(p_SquareCells.topRight.x)] != NONE || map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y + P_BLOCK_SIZE) / BLOCK_SIZE)][(int)(p_SquareCells.bottomRight.x)] != NONE)
			{
				mapObjects[nPlayerID].p_Vel.x = 0;
				Novice::ScreenPrintf(50, 60, "BUMPED 21");
			}
			else
			{
				mapObjects[nPlayerID].p_Pos.x = p_newPosX;
			}
		}
		else if (p_SquareCells.topLeft.y == p_SquareCells.bottomLeft.y)
		{
			if (map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y) / BLOCK_SIZE)][(int)(p_SquareCells.topRight.x)] != NONE || map.Tiles[(int)((mapObjects[nPlayerID].p_Pos.y + P_BLOCK_SIZE) / BLOCK_SIZE) - 1][(int)(p_SquareCells.bottomRight.x)] != NONE)
			{
				mapObjects[nPlayerID].p_Vel.x = 0;
				Novice::ScreenPrintf(50, 60, "BUMPED 22");
			}
			else
			{
				mapObjects[nPlayerID].p_Pos.x = p_newPosX;
			}
		}
	}
	
	TilesCheck(mapObjects[nPlayerID].p_Pos.x, p_newPosY);
	if (mapObjects[nPlayerID].p_Vel.y < 0)//Moving up
	{
		if (p_SquareCells.topLeft.x != p_SquareCells.topRight.x)
		{
			if (map.Tiles[(int)(p_SquareCells.topLeft.y)][(int)((mapObjects[nPlayerID].p_Pos.x) / BLOCK_SIZE)] != NONE || map.Tiles[(int)(p_SquareCells.topRight.y)][(int)((mapObjects[nPlayerID].p_Pos.x + P_BLOCK_SIZE) / BLOCK_SIZE)] != NONE)
			{
				Novice::ScreenPrintf(50, 50, "BUMPED 3");
				mapObjects[nPlayerID].p_Vel.y = 0;
				//mapObjects[nPlayerID].p_Vel.x = 0;
			}
			else
			{
				mapObjects[nPlayerID].p_Pos.y = p_newPosY;
			}
		}
		else if (p_SquareCells.topLeft.x == p_SquareCells.topRight.x)
		{
			if (map.Tiles[(int)(p_SquareCells.topLeft.y)][(int)((mapObjects[nPlayerID].p_Pos.x) / BLOCK_SIZE)] != NONE || map.Tiles[(int)(p_SquareCells.topRight.y)][(int)((mapObjects[nPlayerID].p_Pos.x + P_BLOCK_SIZE) / BLOCK_SIZE) - 1] != NONE)
			{
				Novice::ScreenPrintf(50, 50, "BUMPED 3");
				mapObjects[nPlayerID].p_Vel.y = 0;
				//mapObjects[nPlayerID].p_Vel.x = 0;
			}
			else
			{
				mapObjects[nPlayerID].p_Pos.y = p_newPosY;
			}
		}
	}
	else if(mapObjects[nPlayerID].p_Vel.y > 0)
	{
		if (p_SquareCells.topLeft.x != p_SquareCells.topRight.x)
		{
			if (map.Tiles[(int)(p_SquareCells.bottomLeft.y)][(int)((mapObjects[nPlayerID].p_Pos.x) / BLOCK_SIZE)] != NONE || map.Tiles[(int)(p_SquareCells.bottomRight.y)][(int)((mapObjects[nPlayerID].p_Pos.x + P_BLOCK_SIZE) / BLOCK_SIZE)] != NONE)
			{
				mapObjects[nPlayerID].p_Vel.y = 0;
				//mapObjects[nPlayerID].p_Vel.x = 0;
				Novice::ScreenPrintf(50, 50, "BUMPED 4");
				mapObjects[nPlayerID].p_OnGround = true;
			}
			else
			{
				mapObjects[nPlayerID].p_Pos.y = p_newPosY;
			}
		}
		else if (p_SquareCells.topLeft.x == p_SquareCells.topRight.x)
		{
			if (map.Tiles[(int)(p_SquareCells.bottomLeft.y)][(int)((mapObjects[nPlayerID].p_Pos.x) / BLOCK_SIZE)] != NONE || map.Tiles[(int)(p_SquareCells.bottomRight.y)][(int)((mapObjects[nPlayerID].p_Pos.x + P_BLOCK_SIZE) / BLOCK_SIZE) - 1] != NONE)
			{
				mapObjects[nPlayerID].p_Vel.y = 0;
				//mapObjects[nPlayerID].p_Vel.x = 0;
				Novice::ScreenPrintf(50, 50, "BUMPED 4");
				mapObjects[nPlayerID].p_OnGround = true;
			}
			else
			{
				mapObjects[nPlayerID].p_Pos.y = p_newPosY;
			}
		}


	}

	//Dash
	if (p_Easing.time <= p_Easing.duration)
	{
		p_Easing.time += 0.01;
	}
	else
	{
		canDash[0] = false;
		canDash[1] = false;

	}
	if (keys[DIK_Q] && !keys[DIK_A])
	{
		canDash[0] = true;
		canDash[1] = false;
	}
	else if (keys[DIK_Q] && keys[DIK_A])
	{
		canDash[1] = true;
		canDash[0] = false;
	}
	if (canDash[0])
	{
		mapObjects[nPlayerID].p_Vel.x = 200.0f;

	}
	else if (canDash[1])
	{
		mapObjects[nPlayerID].p_Vel.x = -200.0f;
	}

	else
	{
		p_Easing.time = 0;
		p_Easing.change = 10;
		p_Easing.startPos = 0;
	}

}

void Player::CollisionCheck(float fElapsedTime)
{
	for (auto& object1 : mapObjects)
	{
		for (auto& object2 : mapObjects)
		{
			if (object1.first != object2.first && object1.first != 0 && object2.first != 0)
			{
				if (object2.second.p_Pos.x <= object1.second.p_Pos.x + P_BLOCK_SIZE && object2.second.p_Pos.x + P_BLOCK_SIZE >= object1.second.p_Pos.x && object2.second.p_Pos.y <= object1.second.p_Pos.y + P_BLOCK_SIZE && object2.second.p_Pos.y + P_BLOCK_SIZE >= object1.second.p_Pos.y)
				{
					object1.second.color = RED;
					object2.second.color = RED;
					
				}
				else
				{
					object1.second.color = WHITE;
					object2.second.color = WHITE;
				}
				for (int i = 0; i < 5; i++)
				{
					if (object2.second.p_Pos.x <= object1.second.bullet[i].w_Pos.x + 5 && object2.second.p_Pos.x + 5 >= object1.second.bullet[i].w_Pos.x && object2.second.p_Pos.y <= object1.second.bullet[i].w_Pos.y + 5 && object2.second.p_Pos.y + 5 >= object1.second.bullet[i].w_Pos.y)
					{
						object2.second.color = RED;
					}
					else
					{
						object1.second.color = WHITE;
						object2.second.color = WHITE;
					}
					/*float a[5], b[5], c[5];
					a[i] = object1.second.bullet[i].w_Pos.x - object2.second.p_Pos.x;
					b[i] = object1.second.bullet[i].w_Pos.y - object2.second.p_Pos.y;
					c[i] = sqrtf(pow(a[i], 2) + pow(b[i], 2));
					Novice::ScreenPrintf(10, 400, "C : %f", c[0]);
					if (c[i] < 10)
					{
						object2.second.color = RED;
					}*/


				}
			}
		}
	}

	//Bullet collision
	
	

	
	////////////////////////////////////////////////////////////
	//border
	if (mapObjects[nPlayerID].p_Pos.x >= 1230)
	{
		mapObjects[nPlayerID].p_Pos.x = 1230;
	}
	else if (mapObjects[nPlayerID].p_Pos.x <= 0)
	{
		mapObjects[nPlayerID].p_Pos.x = 0;
	}
	if (mapObjects[nPlayerID].p_Pos.y >= 720)
	{
		mapObjects[nPlayerID].p_Pos.y = 720;
	}
	else if (mapObjects[nPlayerID].p_Pos.y <= 0)
	{
		mapObjects[nPlayerID].p_Pos.y = 0;
	}
	////////////////////////////////////////////////////////////////
}

void Player::TilesCheck(float posX, float posY)
{
	//Square
	p_Square.topLeft.x = posX;
	p_Square.topLeft.y = posY;
	p_Square.bottomLeft.x = posX;
	p_Square.bottomLeft.y = posY + P_BLOCK_SIZE - 1.0f;
	p_Square.topRight.x = posX + P_BLOCK_SIZE - 1.0f;
	p_Square.topRight.y = posY;
	p_Square.bottomRight.x = posX + P_BLOCK_SIZE - 1.0f;
	p_Square.bottomRight.y = posY + P_BLOCK_SIZE - 1.0f;

	//square in cells
	p_SquareCells.topLeft.y = floor(p_Square.topLeft.y / BLOCK_SIZE);
	p_SquareCells.topLeft.x = floor(p_Square.topLeft.x / BLOCK_SIZE);
	p_SquareCells.bottomLeft.y = floor(p_Square.bottomLeft.y / BLOCK_SIZE);
	p_SquareCells.bottomLeft.x = floor(p_Square.bottomLeft.x / BLOCK_SIZE);
	p_SquareCells.topRight.y = floor(p_Square.topRight.y / BLOCK_SIZE);
	p_SquareCells.topRight.x = floor(p_Square.topRight.x / BLOCK_SIZE);
	p_SquareCells.bottomRight.y = floor(p_Square.bottomRight.y / BLOCK_SIZE);
	p_SquareCells.bottomRight.x = floor(p_Square.bottomRight.x / BLOCK_SIZE);

}

void Player::Shake(int max, int min)
{
	if (p_Shake.IsShaking == true)
	{
		p_Shake.shakeTime--;
		if (p_Shake.shakeTime >= 0)
		{
			p_Shake.shakePos.x = rand() % max - min;
			p_Shake.shakePos.y = rand() % max - min;
		}
		else
		{
			p_Shake.IsShaking = false;
		}
	}
	else
	{
		p_Shake.shakePos = { 0 };
		p_Shake.shakeTime = maxShakeTime;
	}
}

void Player::Update(char* keys, char* preKeys)
{
	//Timing
	m_tp2 = std::chrono::system_clock::now();
	std::chrono::duration<float> elapsedTime = m_tp2 - m_tp1;
	m_tp1 = m_tp2;

	//Time per frame coefficient
	fElapsedTime = elapsedTime.count();

	//Count frame
	fFrameTimer += fElapsedTime;
	nFrameCount++;
	if (fFrameTimer >= 1.0f)
	{
		nLastFPS = nFrameCount;
		nFrameCount = 0;
		fFrameTimer = 0.0f;	
	}
	ClientInterface::OnUserUpdate();
	ClientInterface::PingServer();
	Shake(10, 5);
	GetScreenPos();
	range->OnAttack(fElapsedTime, keys, preKeys, mapObjects[nPlayerID].bullet, mapObjects[nPlayerID].p_Pos);
	Skill(keys, preKeys);
	//Move(keys, preKeys, fElapsedTime);
	Move2(keys, preKeys, fElapsedTime);
	CollisionCheck(fElapsedTime);
	Draw();
	
}

Vector2 Player::GetScreenPos()
{
	mapObjects[nPlayerID].p_Vel.x += mapObjects[nPlayerID].p_Acc.x;;
	mapObjects[nPlayerID].p_Vel.y += mapObjects[nPlayerID].p_Acc.y;;

	//mapObjects[nPlayerID].p_Pos.x += mapObjects[nPlayerID].p_Vel.x * fElapsedTime;
	//mapObjects[nPlayerID].p_Pos.y += mapObjects[nPlayerID].p_Vel.y * fElapsedTime;

	mapObjects[nPlayerID].p_Pos.x = mapObjects[nPlayerID].p_Pos.x + p_Shake.shakePos.x;
	mapObjects[nPlayerID].p_Pos.y = mapObjects[nPlayerID].p_Pos.y + p_Shake.shakePos.y;
	return mapObjects[nPlayerID].p_Pos;
}

void Player::Draw()
{
	if (ClientInterface::IsConnected())
	{
		//Draw box
		Novice::DrawBox(p_SquareCells.topLeft.x * BLOCK_SIZE, p_SquareCells.topLeft.y * BLOCK_SIZE , BLOCK_SIZE, BLOCK_SIZE, 0, GREEN, kFillModeSolid);
		Novice::DrawBox(p_SquareCells.topRight.x * BLOCK_SIZE, p_SquareCells.topRight.y * BLOCK_SIZE , BLOCK_SIZE, BLOCK_SIZE, 0, GREEN, kFillModeSolid);
		Novice::DrawBox(p_SquareCells.bottomLeft.x * BLOCK_SIZE, p_SquareCells.bottomLeft.y * BLOCK_SIZE , BLOCK_SIZE, BLOCK_SIZE, 0, GREEN, kFillModeSolid);
		Novice::DrawBox(p_SquareCells.bottomRight.x * BLOCK_SIZE, p_SquareCells.bottomRight.y * BLOCK_SIZE , BLOCK_SIZE, BLOCK_SIZE, 0, GREEN, kFillModeSolid);

		//Print information
		Novice::ScreenPrintf(600, 10, "FPS: %d",nLastFPS);

		Novice::ScreenPrintf(600, 50, "Ping : %lf ms", PingCount);
		Novice::ScreenPrintf(600, 30, "fElapsedTime : %f ms", fElapsedTime);
		Novice::ScreenPrintf(600, 80, "IsGrounded : %d ", mapObjects[nPlayerID].p_OnGround);
		Novice::ScreenPrintf(600, 110, "CanJump : %d ", mapObjects[nPlayerID].canJump);

		Novice::ScreenPrintf(600, 150, "TopLeft : [%d][%d] ", int(p_SquareCells.topLeft.x), int(p_SquareCells.topLeft.y));
		Novice::ScreenPrintf(600, 180, "TopRight : [%d][%d] ", int(p_SquareCells.topRight.x), int(p_SquareCells.topRight.y));
		Novice::ScreenPrintf(600, 210, "BotLeft : [%d][%d] ", int(p_SquareCells.bottomLeft.x), int(p_SquareCells.bottomLeft.y));
		Novice::ScreenPrintf(600, 240, "BotRight : [%d][%d] ", int(p_SquareCells.bottomRight.x), int(p_SquareCells.bottomRight.y));
		for (auto& object : mapObjects)
		{
			if (object.first != 0)
			{
				Novice::DrawBox(object.second.p_Pos.x, object.second.p_Pos.y, P_BLOCK_SIZE, P_BLOCK_SIZE, 0, object.second.color, kFillModeSolid);
				Novice::ScreenPrintf(10, 10, "Vel x : %f  Vel y : %f", object.second.p_Vel.x, object.second.p_Vel.y);
				Novice::ScreenPrintf(10, 30, "Pos x : %f  Pos y : %f", object.second.p_Pos.x, object.second.p_Pos.y);
				Novice::ScreenPrintf(object.second.p_Pos.x, object.second.p_Pos.y + 70, "%s", std::to_string(object.first));
				Novice::ScreenPrintf(10, 60, "%s", std::to_string(object.second.bullet[0].w_Speed));
				//Draw bullet
				for (int i = 0; i < 5; i++)
				{
					Novice::DrawEllipse(object.second.bullet[i].w_Pos.x, object.second.bullet[i].w_Pos.y, 5, 5, 0, WHITE, kFillModeSolid);
				}
			}
			
		}

		

	}
	
}

void Player::Skill(char* keys, char* preKeys)
{
	
}
