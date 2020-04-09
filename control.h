#pragma once
#include "game.h"
#include "keypress.h"
class Control
{
public:
};
class Human:public Control, Keypressable
{
public:
	Snake* snake;
	void onkey(int key);
	Human(Snake*);
};
class Robot:public Control
{
public:
	Snake* snake;
	void onthink();
	void distance(int,int,int,int);
	Robot(Snake*);
};
