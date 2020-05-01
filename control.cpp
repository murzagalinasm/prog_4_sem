#include "view.h"
#include "game.h"
#include "control.h"
#include <cmath>
#include <functional>
#include <algorithm>

using namespace std::placeholders;

void Human::onkey(int key)
{
	//      printf("\r  %d",key);
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
	//      auto f = std::bind(&Human::onkeypress,this,_1);
	View* v=View::get();
	v->setonkey(this);
}


int Robot::distance( Coord a, Coord b) 
{
	return (pow((a.first - b.first), 2) + pow((a.second - b.second), 2));
}





			//Robot::Robot(Game& g) : BOT(g){
			//ui::get()->ontimer(Game::TICK, std::bind(&Robot::onthink, snake));
			//}







void Robot::onthink(){
	//Ui::get()->on_timer(Game::TICK, std::bind(&Enemy::tick, this));
	//поиск кролика(ближайшего)
	
	auto rab = View::get() -> game -> rabbits;
	
	Coord low = rab.front();

	for(auto i = rab.begin(); i != rab.end(); i++) {
		if(distance(snake->body.front(), *i) < distance(snake-> body.front(), low)) {
			low = *i;
		}
	}

	int distbyx = (low.first - snake->body.front().first);
	int distbyy = (low.second - snake->body.front().second);


	if(abs(distbyx) < abs(distbyy)){
		if(distbyy < 0){
			snake->setdir(UP);
		}
		else{
			snake->setdir(DOWN);
		}
	}
	else{
		if (distbyx < 0){
			snake->setdir(LEFT);
		}
		else{
			snake->setdir(RIGHT);
		}
	}



}






