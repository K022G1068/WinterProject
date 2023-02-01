#pragma once
#include"..\[Server]\Common.h"
#include"Novice.h"

class Animation
{
public:
	int maxFrame_;
	int resetFrame_;
	int currentFrame_;
	int timeCount_;
	int frameTime_;
	int graph_;
	bool repeat_;

public:
	Animation(int maxFrame, int currentFrame, int resetFrame, int timeCount, int frameTime, int graph, bool repeat);
	~Animation();
	void RunAnimation(Vector2 pos, int size);
	void Draw();
};

