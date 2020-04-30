#pragma once
#include "game.h"
#include "control.h"
class Ui
{

private:

    static Ui*instance;
public:
    
    using event_fn = std::function<void(int)>;
    using timer_fn = std::function<void(void)>;

    enum Keys {
	    KEY_UP = 100,
	    KEY_DOWN,
	    KEY_LEFT,
	    KEY_RIGHT,
    };
    
    static Ui * get(const char *what = NULL);

    virtual int winx() = 0;
    virtual int winy() = 0;

    virtual void run(Game&) = 0;
    virtual void draw() = 0;
    virtual void quite() = 0;

    virtual void on_key(event_fn) = 0;
    virtual void on_timer(int time, timer_fn) = 0;
    //virtual void paint(const Snake&) = 0;


    virtual ~Ui() = 0;

protected:
    Ui() = default;
};







