#pragma once
#include <cstdint>
#include"Networking.h"
#include"Struct.h"
#include<math.h>
#define BLOCK_SIZE 32
#define MAXCLIENT 2

#define WIN_WIDTH  1280;
#define WIN_HEIGHT  800;


enum MapInfo
{
	NONE,
	BLOCK,
};

enum class GameMsg : uint32_t
{
	Server_GetStatus,
	Server_GetPing,

	Client_Accepted,
	Client_AssignID,
	Client_RegisterWithServer,
	Client_UnregisterWithServer,

	Lobby_MakeRoom,
	Lobby_SearchRoom,
	Lobby_JoinRoom,
	Lobby_UpdateRoom,
	Lobby_AssignRoom,
	Lobby_AddRoom,
	Lobby_DeleteRoom,

	Game_AddPlayer,
	Game_RemovePlayer,
	Game_UpdatePlayer,
};

struct PlayerInfo
{
	uint32_t nUniqueID = 0;
	uint32_t nAvatarID = 0;
	Hp p_Hp;
	Vector2 p_Pos;
	Vector2 p_Old_Pos;
	Vector2 p_Vel;
	Vector2 p_Acc;
	Vector2 p_s_Pos;
	Vector2 p_Scale;
	Bullet bullet[5];

	int facing = RIGHT;
	int color = 0xFFFFFFFF;
	bool isHitted;
	bool canHit;
	bool p_OnGround;
	bool canJump;

	
};

struct RoomInfo
{
	uint32_t nRoomID;
	uint32_t nHostID;
	uint32_t maxClient;
	uint32_t participantCount;
	uint32_t participants[MAXCLIENT];
	bool isFull;

};