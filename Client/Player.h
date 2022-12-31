#pragma once
#include "ClientInterface.h"
class Player : public ClientInterface
{
public:
	Player();
	~Player();
	void Move(char* keys, char* preKeys);
	void Update(char* keys, char* preKeys);
	void Draw();


};

