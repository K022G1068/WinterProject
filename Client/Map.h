#pragma once
#include<iostream>
#include<stdio.h>
#include"..\[Server]\Common.h"
#include"Novice.h"

#define MAP_WIDTH 50
#define MAP_HEIGHT 25

class Map
{
private:
	FILE* fp;
	errno_t err;
	std::string fname = "mapSample2.csv";
	

	Vector2 bgPos;

public:
	int Tiles[25][50];

public:
	Map();
	void InitMap();
	void DrawMap(int& blockSprite);
};

