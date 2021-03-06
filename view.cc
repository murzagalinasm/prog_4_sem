#include <sys/time.h>
#include <utility>
#include <iostream>
#include <poll.h>
#include <termios.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <functional>

using namespace std::placeholders;
#include "view.h"

View* View::instance;
View* View::get()
{
	if (instance == 0)
		instance = new View;
	return instance;
}
void onwinch(int sig)
{
	View::get()->draw();
}
void bye (int go)
{
	printf("\nBye!\n");
	View* v = View::get();
	delete v;
	exit(0);
}

View::View()
{
	struct termios a;
	tcgetattr(0,&a);
	oldtc = a;
	cfmakeraw(&a);
	tcsetattr(0,TCSAFLUSH,&a);

	setbuf(stdout, NULL);
	signal(SIGWINCH, onwinch);
	instance = this;

	signal(SIGTERM, bye);
	signal(SIGINT,bye);
	signal(SIGSEGV,bye);

}
void View::gotoxy(int x, int y)
{
	printf("\e[%d;%dH",winy-y,x+1);
}
void View::cls()
{
	printf("\e[H\e[J");
}
View::~View()
{
	//cls();
	//printf("BYE\n");
	signal(SIGWINCH, SIG_DFL);
	instance = NULL;

	tcsetattr(0,TCSAFLUSH,&oldtc);
}
void View::hline(int x,int y,int len,char c)
{
	gotoxy(x,y);
	for (int i=0;i<len;i++)
		printf("%c",c);

}
void View::vline(int x,int y,int len,char c)
{
	for (int i=y;i<len;i++)
	{
		gotoxy(x,i);
		printf("%c",c);
	}
}

void View::draw_end() {
	int i,j;
	struct winsize p;
	ioctl(0,TIOCGWINSZ, &p);
	winy=p.ws_row;
	winx=p.ws_col;

	cls();

	hline(0,0,winx,'*');
	vline(0,0,winy,'*');
	vline(winx-1,0,winy,'*');
	hline(0,winy-1,winx,'*');

	hline(1,1,winx - 1,'*');
	vline(1,1,winy - 1,'*');
	vline(winx-2,1,winy - 1,'*');
	hline(1,winy-2,winx - 1,'*');

	gotoxy(winx/2,winy/2);
	printf(" -GAMEOVER- ");

	fflush(stdout);
}

void View::draw()
{
	int i,j;
	struct winsize p;
	ioctl(0,TIOCGWINSZ, &p);
	winy=p.ws_row;
	winx=p.ws_col;

	cls();

	hline(0,0,winx,'*');
	vline(0,0,winy,'*');
	vline(winx-1,0,winy,'*');
	hline(0,winy-1,winx,'*');

	gotoxy(winx/2,winy/2);
	printf(" -SNAKE- ");

	game->rabbit_visitor(std::bind(&View::rabbit_painter, this, _1));
	game->snake_visitor(std::bind(&View::snake_painter, this, _1, _2));

	fflush(stdout);
}
void View::setonkey(Keypressable* x)
{
	keyd=x;
}
void View::run()
{
	int timeout = timer.first;
	while(1)
	{
		struct pollfd arr[1];
		arr[0].fd = 0;
		arr[0].events = POLLIN;

		struct timeval t1;
		gettimeofday(&t1, NULL);

		int n = poll(arr, 1, timeout);
		if (n>0)
		{
			char c;
			read(0, &c, 1);
			if (c =='q')
				break;
			keyd->onkey(c);

		}

		struct timeval t2;
		gettimeofday(&t2, NULL);

		//обрабатываем timeout
		int delta = (t2.tv_sec-t1.tv_sec)*1000+(t2.tv_usec-t1.tv_usec)/1000;
		timeout-=delta;
		if (timeout <=0)
		{
			timer.second();
			timeout = timer.first;
		}
		draw();
	}
}
void View::rabbit_painter(Coord c) //const Coord& c
{
	gotoxy(c.first,c.second);
	//setcolor(0);
	putchar('@');
}
void View::snake_painter(Coord c, Direction d)
{
	gotoxy(c.first,c.second);
	const char* s="^v<>#";
	putchar(s[d]);

}



