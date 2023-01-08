#pragma once
#include"..\[Server]\Common.h"
#include"Novice.h"
class Weapon
{
protected:
	int w_Damage;
	int w_Speed;
	Vector2 w_Pos;

public:
	virtual void OnAttack();
	virtual void ChargeAttack();
};

