#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>

void draw(int row, int col);
struct winsize argp;

void handler() {
	ioctl(1, TIOCGWINSZ, &argp);
	draw(argp.ws_row, argp.ws_col);
}


void draw(int row, int col) {
	printf("\e");  
      	
	//draw top hline
	for (int i = 1; i <= col; i++) {
		printf("\e[1;%d", i);
	}
	
	//draw left vline
	for (int i = 2; i <= row; i++) {
		printf("\e[%d;1", i);
	}
	
	//draw right vline
	for (int i = 2; i <= row; i++) {
		printf("\e[%d;%d", i, col);
	}
	
	//draw bottom hline
	for (int i = 1; i <= col; i++) {
		printf("\e[%d;%d", row, i);
	}
	printf("\e[1m\e[%d;%d\e[31mR\e[33mA\e[32mI\e[36mN\e[34mB\e[35mO\e[37mW\e[5m!",
			row/2+1, col/2-3);
	printf("\e[%d;%d", row, col);
	fflush(stdout);
}

void term_handler() {
	printf("\e");
	exit(0);
}

int main() {
	signal(SIGWINCH, handler);
	signal(SIGINT, term_handler);

	ioctl(0, TIOCGWINSZ, &argp);
	draw(argp.ws_row, argp.ws_col);
	//printf("\nWindow size = %d ; %d !\n", argp.ws_row, argp.ws_col);



	for (int i = 0; i < 500; i++) {
		for (int j = 0; j < 100000000; j++);
		printf("\e[%d;%d", 2 + rand() % 36, 2 + rand() % 146);
		fflush(stdout);
	}
}








