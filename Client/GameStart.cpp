#include "GameStart.h"

GameStart::GameStart()
{
	player->OnUserUpdate();
}

void GameStart::Update(char* keys, char* preKeys)
{
	player->OnUserUpdate();
	player->Update(keys, preKeys);
}

void GameStart::Draw()
{
	if (player->IsConnected())
	{
		mapObject->DrawMap();

	}
}
