#include <iostream>

#include "ui.h"
#include "tui.h"

Tty::Tty(){
    Tty::init_tty(__k8__); 
}

void Tty::cls(){
    printf("\e[H\e[J\e[m");
} 

void Tty::gotoxy(int x, int y){
    printf("\e[%d;%d H", x, y);  //Но тут проблема
}

void Tty::draw(){
    Tty::hline(1, 1, Tty::winx());
    Tty::vline(1, 1, Tty::winy());
}

void Tty::putc(int x, int y, char c){
    Tty::gotoxy(x, y);
    printf("%c", c);
}

void Tty::winch(){

}
