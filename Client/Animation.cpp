#include "Animation.h"

Animation::Animation(int maxFrame, int currentFrame, int resetFrame, int timeCount, int frameTime, int graph, bool repeat)
{
	this->maxFrame_ = maxFrame;
	this->currentFrame_ = currentFrame;
	this->timeCount_ = timeCount;
	this->graph_ = graph;
	this->repeat_ = repeat;
	this->frameTime_ = frameTime;
	this->resetFrame_ = resetFrame;
}

void Animation::RunAnimation(Vector2 pos, int size)
{
	timeCount_++;
	if (timeCount_ >= frameTime_)
	{
		currentFrame_++;
		timeCount_ = 0;
	}

	if (repeat_)
	{
		if (currentFrame_ >= maxFrame_)
		{
			currentFrame_ = resetFrame_;
		}
	}
}


