#pragma once
#include"GameTitle.h"
#include"Map.h"

class GameStart:public GameTitle
{
private:
	
	Map* mapObject = new Map();
public:

	GameStart();
	void Update(char* keys, char* preKeys);
	void Draw();
};

