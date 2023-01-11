#include "w_Ranged.h"

w_Ranged::w_Ranged(int damage, int speed, Bullet* bullet, Vector2& base_pos)
{
	for (int i = 0; i < maxBullet_; i++)
	{
		bullet[i].w_Damage= damage;
		bullet[i].w_Speed = speed;
		bullet[i].w_Base_Pos = base_pos;
		bullet[i].w_Pos = base_pos;
		this->playerPos_ = base_pos;
	}
}

w_Ranged::~w_Ranged()
{

}


void w_Ranged::OnAttack(float& fElapsedTime, char* keys, char* preKeys, Bullet* bullet, Vector2& base_pos)
{
	cooldown_--;
	for (int i = bulletCount_; i < maxBullet_; i++)
	{
		if (Novice::IsPressMouse(0))
		{
				if (cooldown_ <= 30)
				{
					if (keys[DIK_A])
					{
						bullet[i].isShooting[face::LEFT] = 1;
					}
					else
					{
						bullet[i].isShooting[face::RIGHT] = 1;
					}
					bulletCount_++;
					cooldown_ = 60;
				}
				break;
			}
	}
	for (int i = 0; i < maxBullet_; i++)
	{
		bullet[i].w_Base_Pos = base_pos;
	}
	for (int i = 0; i < 5; i++)
	{
		if (bullet[i].isShooting[face::RIGHT])
		{
			bullet[i].w_Pos.x += 400.0f * fElapsedTime;
		}
		else if (bullet[i].isShooting[face::LEFT])
		{
			bullet[i].w_Pos.x -= 400.0f * fElapsedTime;
		}
		else
		{
			bullet[i].w_Pos.x = bullet[i].w_Base_Pos.x + 16;
			bullet[i].w_Pos.y = bullet[i].w_Base_Pos.y + 16;
		}


		if (bullet[i].w_Pos.x >= 1200 )
		{
			bullet[i].isShooting[face::RIGHT] = 0;
		}
		else if(bullet[i].w_Pos.x <= 0)
		{
			bullet[i].isShooting[face::LEFT] = 0;
		}

		bullet[i].bulletRange = bullet[i].w_Pos.x - bullet[i].w_Base_Pos.x;
		if (abs(bullet[i].bulletRange) >= 300.0f)
		{
			bullet[i].isShooting[face::RIGHT] = false;
		}
		else if (abs(bullet[i].bulletRange) <= -300.0f)
		{
			bullet[i].isShooting[face::LEFT] = false;
		}
	}
	if (bulletCount_ >= maxBullet_)
	{
		bulletCount_ = 0;
	}
}


//void w_Ranged::Draw(Bullet bullet[])
//{
//	for (int i = 0; i < maxBullet_; i++)
//	{
//		Novice::DrawEllipse(bullet[i].w_Pos.x, bullet[i].w_Pos.y, 5, 5, 0, WHITE, kFillModeSolid);
//	}
//}


