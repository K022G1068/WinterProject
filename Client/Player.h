#pragma once
#include "ClientInterface.h"
#include "Map.h"
#include "Easing.h"
#include "w_Ranged.h"

#define P_BLOCK_SIZE 32
#define maxShakeTime 60

class Player : public ClientInterface
{
private:
	
	bool canDash[2]; //0 right 1 left
	ShakeElement p_Shake;
	Square p_Square;
	Square p_SquareCells;
	Easing p_Easing;
	Vector2 w_Pos;

	
	float fElapsedTime = 0.0f;
	float fFrameTimer =0;
	int nFrameCount =0;
	int nLastFPS = 0;
	std::chrono::time_point<std::chrono::system_clock> m_tp1, m_tp2;
public:
	w_Ranged* range = new w_Ranged(1.0f, 150.0f, mapObjects[nPlayerID].bullet, mapObjects[nPlayerID].p_Pos);

	Map map;
	Player();
	~Player();
	void Move2(char* keys, char* preKeys, float fElapsedTime);
	void CollisionCheck(float fElapsedTime);
	void TilesCheck(float posX, float posY);
	void Shake(int max, int min);
	void Update(char* keys, char* preKeys);
	Vector2 GetScreenPos();
	void Draw();

	//Skill
	void Skill(char* keys, char* preKeys);

	
};


