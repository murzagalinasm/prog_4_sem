#pragma once
#include <utility>
#include <list>
#include <functional>

enum Direction{UP, DOWN, LEFT,	RIGHT, BODY};

using Coord = std::pair<int,int>;
using RabbitPainter = std::function<void(Coord)>;
using SnakePainter = std::function<void(Coord, Direction)>;



class Snake
{
public:
	std::list<Coord> body;
	Snake();
	void move(std::list<Coord> &rabbits);
	Coord next();
	void setdir(Direction a)
	{
		d = a;
	}

	Direction d;
private:
	void death();
	int times;
};

class Game
{
public:
	std::list<Coord> rabbits;
	std::list<Snake*> snakes;
	Game();
	void Gameover();
	void rabbit_visitor(RabbitPainter);
	void snake_visitor(SnakePainter);
	void move();
	void add(Snake*);	
};




