#include <stdio.h>

#include "control.h"
#include "view.h"
#include "game.h"

int main()
{
	View* v=View::get();
	Snake s;
	Human h(&s);
	Game g;

	Snake s1;
	Robot r(&s1);
		
	g.add(&s);
	g.add(&s1);
	v->setgame(&g);

	v->draw();
	v->run();



	v->cls();
	printf("BYE\n");
	delete v;
	return 0;
}
