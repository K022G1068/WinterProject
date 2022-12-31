#include "Player.h"

Player::Player()
{
	ClientInterface::OnUserCreate();
}

Player::~Player()
{

}

void Player::Move(char* keys, char* preKeys)
{
	if (keys[DIK_D])
	{
		mapObjects[nPlayerID].p_Pos.x += 2;
	}
	if (keys[DIK_A])
	{
		mapObjects[nPlayerID].p_Pos.x -= 2;
	}
	else if (keys[DIK_W])
	{
		mapObjects[nPlayerID].p_Pos.y -= 2;
	}
	if (keys[DIK_S])
	{
		mapObjects[nPlayerID].p_Pos.y += 2;
	}
}

void Player::Update(char* keys, char* preKeys)
{
	ClientInterface::OnUserUpdate();
	ClientInterface::PingServer();
	Move(keys, preKeys);
	Draw();
}

void Player::Draw()
{
	if (ClientInterface::IsConnected())
	{
		Novice::ScreenPrintf(600, 10, "Ping : %s ms", std::to_string(ClientInterface::PingCount));
		for (auto& object : mapObjects)
		{
			if (object.first != 0)
			{
				Novice::DrawBox(object.second.p_Pos.x, object.second.p_Pos.y, 50, 50, 0, WHITE, kFillModeSolid);
				Novice::ScreenPrintf(object.second.p_Pos.x, object.second.p_Pos.y + 70, "%s", std::to_string(object.first));
			}
			
		}

	}
	
}
