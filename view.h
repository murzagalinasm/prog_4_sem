#pragma once
#include <utility>
#include <iostream>
#include <termios.h>
#include "keypress.h"
#include "game.h"

class View
{
public:
	View();
	~View();
	void draw();
	void draw_end();
	void run();
	static View* get();
	void cls();
	void setonkey(Keypressable*);
	void rabbit_painter(Coord);
	void snake_painter(Coord, Direction);
	void setgame(Game* g)
	{
		game = g;
	}

	using fn_type = std::function<void()>;
		
	void settimer(int ms, fn_type fn)
	{

		timer = std::make_pair(ms, fn);
	}

	int winx, winy;
	std::pair <int,fn_type> timer;
	Game* game;
private:
	void gotoxy(int,int);
	//void cls();
	void hline(int,int,int,char c='*');
	void vline(int,int,int,char c='*');
	void size(int);

	static View* instance;
	struct termios oldtc;
	Keypressable* keyd;
};
