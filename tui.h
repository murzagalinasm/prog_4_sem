#include <iostream>
#include "ui.h"
#include <termios.h>
#include <sys/ioctl.h>
#include <vector>
#include "game.h"
#include "control.h"

//struct winsize ws;

class Tty : public Ui{
public:
    Tty();
    ~Tty();
    
    
    int winx() const { return ws.ws_col; }
    int winy() const { return ws.ws_row; }

    void run(Game&);
    void quit();
    void draw();

    void on_key(event_fn fn);
    void on_timer(int t, timer_fn fn);
    
    //void paint(const Snake&); 
    //void paint(const xy rabbit); 
private:

public:   
    void cls();
    void putc(int x, int y, char c);
    void hline(int x, int y, int len);
    void vline(int x, int y, int len);
    void setcolor(int color);
    void gotoxy(int x, int y);
    void read_event();

    void init_tty(int echo);
    void fini_tty();
    void winch();

private:
    struct winsize ws;


};
