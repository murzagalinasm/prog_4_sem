#include <memory>
#include <cstdio>

#include "ui.h"
#include "snake.h"
#include "control.h"



int main()
{
    std::unique_ptr<ui>  v(ui::get("tty"));
    if (!v){
        fprintf(stderr, "Cannot init UI\n");
        return 0;
    }

    Game g;
    Human h(g);
    Robot s1(g), s2(g), s3(g);

    v->run(g);

}