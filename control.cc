#include "game.h"
#include "control.h"
#include "view.h"
#include <functional>
#include <algorithm>

using namespace std::placeholders;

void Human::onkey(int key)
{
	//	printf("\r  %d",key);
	switch (key)
	{
		case 'A':
			snake->setdir(UP);
			break;
		case 'B':
			snake->setdir(DOWN);
			break;
		case 'C':
			snake->setdir(RIGHT);
			break;
		case 'D':
			snake->setdir(LEFT);
			break;
		default:
			break;
	}

}
Human::Human(Snake* s) : snake(s)
{
	//snake =s;
	//	auto f = std::bind(&Human::onkeypress,this,_1);
	View* v=View::get();
	v->setonkey(this);
}


Coord Robot::distance(Coord rab)
{
	return Coord(rab.first - snake -> body.front().first, rab.second - snake -> body.front().second);
}


void Robot::onthink()
{
	auto rab = View::get() -> game -> rabbits;
	Coord low = rab.front();
	for(auto i:rab)
	{
		if((distance(low).first*distance(low).first + distance(low).second*distance(low).second)
				> (distance(i).first*distance(i).first + distance(i).second * distance(i).second))
		{
			low = i;
		}
	}
	if(distance(low).first*distance(low).first > distance(low).second*distance(low).second)
	{
		if(distance(low).first > 0)
			snake -> setdir(RIGHT);
		else
			snake -> setdir(LEFT);
	}
	else
	{
		if(distance(low).second > 0)
			snake -> setdir(UP);// zopa
		else
			snake -> setdir(DOWN);
	}

	Coord head = snake -> body.front();
	switch(snake -> d)
	{
		case(RIGHT): head.first++; break;
		case(LEFT): head.first--; break;
		case(DOWN): head.second++; break;
		case(UP): head.second--; break;
	}

	std::list<Snake*> sn = View::get() -> game -> snakes;
	for(auto i : sn)
		if(find(i -> body.begin(), i -> body.end(), head) != i -> body.end() && this -> snake != i)
		{
			if(snake -> d == LEFT || snake -> d == RIGHT)
			{
				snake -> setdir((rand() % 2 == 0)?UP:DOWN);
				Coord head = snake -> body.front();
				switch(snake -> d)
				{
					case(RIGHT): head.first++; break;
					case(LEFT): head.first--; break;
					case(DOWN): head.second++; break;
					case(UP): head.second--; break;
				}

				std::list<Snake*> sn = View::get() -> game -> snakes;
				for(auto i : sn)
					if(find(i -> body.begin(), i -> body.end(), head) != i -> body.end() && this -> snake != i)
					{
						if(snake -> d == UP)
						{
							snake -> setdir(DOWN);
						}
						else
						{
							snake -> setdir(UP); 
						}
					}

				if(find(++(snake -> body.begin()), snake -> body.end(), head) != snake -> body.end() || head.first == 0 ||
						head.first == View::get() -> winx || head.second == View::get() -> winy || head.second == 0)
				{

					if(snake -> d == UP)
					{
						snake -> setdir(DOWN);
					}
					else
					{
						snake -> setdir(UP); 
					}
				}
			}
			else
			{
				snake -> setdir((rand() % 2 == 0)?LEFT:RIGHT); 
				Coord head = snake -> body.front();
				switch(snake -> d)
				{
					case(RIGHT): head.first++; break;
					case(LEFT): head.first--; break;
					case(DOWN): head.second++; break;
					case(UP): head.second--; break;
				}

				std::list<Snake*> sn = View::get() -> game -> snakes;
				for(auto i : sn)
					if(find(i -> body.begin(), i -> body.end(), head) != i -> body.end() && this -> snake != i)
					{
						if(snake -> d == LEFT)
						{
							snake -> setdir(RIGHT);
						}
						else
						{
							snake -> setdir(LEFT); 
						}
					}

				if(find(++(snake -> body.begin()), snake -> body.end(), head) != snake -> body.end() || head.first == 0 ||
						head.first == View::get() -> winx || head.second == View::get() -> winy || head.second == 0)
				{

					if(snake -> d == LEFT)
					{
						snake -> setdir(RIGHT);
					}
					else
					{
						snake -> setdir(LEFT); 
					}
				}
			}
		}

	if(find(++(snake -> body.begin()), snake -> body.end(), head) != snake -> body.end() || head.first == 0 ||
			head.first == View::get() -> winx || head.second == View::get() -> winy || head.second == 0)
	{
		if(snake -> d == LEFT || snake -> d == RIGHT)
		{
			snake -> setdir((rand() % 2 == 0)?UP:DOWN);
			Coord head = snake -> body.front();
			switch(snake -> d)
			{
				case(RIGHT): head.first++; break;
				case(LEFT): head.first--; break;
				case(DOWN): head.second++; break;
				case(UP): head.second--; break;
			}

			std::list<Snake*> sn = View::get() -> game -> snakes;
			for(auto i : sn)
				if(find(i -> body.begin(), i -> body.end(), head) != i -> body.end() && this -> snake != i)
				{
					if(snake -> d == UP)
					{
						snake -> setdir(DOWN);
					}
					else
					{
						snake -> setdir(UP); 
					}
				}

			if(find(++(snake -> body.begin()), snake -> body.end(), head) != snake -> body.end() || head.first == 0 ||
					head.first == View::get() -> winx || head.second == View::get() -> winy || head.second == 0)
			{

				if(snake -> d == UP)
				{
					snake -> setdir(DOWN);
				}
				else
				{
					snake -> setdir(UP); 
				}
			}
		}
		else
		{
			snake -> setdir((rand() % 2 == 0)?LEFT:RIGHT); 
			Coord head = snake -> body.front();
			switch(snake -> d)
			{
				case(RIGHT): head.first++; break;
				case(LEFT): head.first--; break;
				case(DOWN): head.second++; break;
				case(UP): head.second--; break;
			}

			std::list<Snake*> sn = View::get() -> game -> snakes;
			for(auto i : sn)
				if(find(i -> body.begin(), i -> body.end(), head) != i -> body.end() && this -> snake != i)
				{
					if(snake -> d == LEFT)
					{
						snake -> setdir(RIGHT);
					}
					else
					{
						snake -> setdir(LEFT); 
					}
				}

			if(find(++(snake -> body.begin()), snake -> body.end(), head) != snake -> body.end() || head.first == 0 ||
					head.first == View::get() -> winx || head.second == View::get() -> winy || head.second == 0)
			{

				if(snake -> d == LEFT)
				{
					snake -> setdir(RIGHT);
				}
				else
				{
					snake -> setdir(LEFT); 
				}
			}
		}
	}


}
Robot::Robot(Snake* s) : snake(s)
{
}
