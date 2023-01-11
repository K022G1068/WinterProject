#pragma once
#include"Weapon.h"
#include"Novice.h"

class w_Ranged
{
private:
	int cooldown_ = 30;
	int bulletCount_ = 0;
	static const int maxBullet_ = 5;
	Vector2 playerPos_;
	int facing;

public:
	w_Ranged(int damage, int speed, Bullet* bullet, Vector2& base_pos);
	~w_Ranged();
	void OnAttack(float& fElapsedTime, char* keys, char* preKeys, Bullet* bullet, Vector2& base_pos);
	//void Draw(Bullet bullet[]);
};

