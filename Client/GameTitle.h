#pragma once
#include"Player.h"
#include"Novice.h"

class GameTitle : public ClientInterface
{
protected:
	std::shared_ptr<Player> player;
private:
	int graph;
public:
	
	GameTitle();
	void Init();
	void Draw();
};

