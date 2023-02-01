#pragma once
#include"Weapon.h"
#include"Novice.h"
#include"Player.h"

class w_Melee
{
private:
	int cooldown_ = 15;
	int comboCount = 0;
	int facing = RIGHT;

public:
	w_Melee();
	~w_Melee();
	void OnAttack();

};

