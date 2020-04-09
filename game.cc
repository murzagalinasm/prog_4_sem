#include "game.h"
#include "view.h"

#include <cstdlib>

Game::Game()
{
	//snakes.push_back(Snake());
	rabbits.push_back(Coord(10,15));
	rabbits.push_back(Coord(15,20));
	
	View* v = View::get();
	v->View::settimer(200, std::bind(&Game::move, this));
}
void Game::add(Snake* s)
{
	snakes.push_back(s);
}
Snake::Snake()
{
	times = 0;
	body.push_back(Coord(5,5));
	body.push_back(Coord(6,5));
	d = RIGHT;
}
void Game::rabbit_visitor(RabbitPainter p)
{
	for(auto r : rabbits)
		p(r);
		
}
void Game::snake_visitor(SnakePainter p)
{
	bool head=false;
	for(auto s : snakes) {
		Direction d = s->d;
		for(auto b : s->body)
		{
				p(b,d);
				d = BODY;
		}
	}
	
}
void Game::move()
{
	View* v = View::get();

	if(rand()%30 == 1)
	{
		Coord c;
		c.first = rand()%v->winx-1;
		c.second = rand()%v->winy-1;
		rabbits.push_back(c);
		v->rabbit_painter(c);	
	}
	for(auto s : snakes)
		s->move(rabbits);
}
void Snake::move(std::list<Coord> &rabbits)
{
	Coord c = next();
	body.push_front(c);
	times++;

	
	for(auto c: body) {
		int i = 0;
		for(auto b: body) {
			if((c.first == b.first)&&(c.second == b.second))
				i++;
		}	
		if((i > 1)&&(times > 20))
			this->death();
	}


	for(auto i = rabbits.begin(); i != rabbits.end(); i++)
	{
		if(c == *i)
		{
			rabbits.erase(i);
			return;
		}
	}

	body.pop_back();
}

void Snake::death() {
	body.clear();
	
	View::get()->draw_end();
}


Coord Snake::next()
{
	Coord a = body.front();
	switch (d)
	{
		case UP:
			a.second++;
			break;
		case DOWN:
			a.second--;
			break;
		case LEFT:
			a.first--;
			break;
		case RIGHT:
			a.first++;
			break;
		default:
			break;
	}
	if((a.first == 0)||(a.second == 0)) {
		this->death();
		        View::get()->draw_end();
	}
	return a;
}
