#include <memory>
#include <cstdio>

#include "ui.h"
#include "game.h"
#include "control.h"



int main()
{
    std::unique_ptr<Ui>  v(Ui::get("tty"));
    if (!v){
        fprintf(stderr, "Cannot init UI\n");
        return 0;
    }

    Game g;
    Snake* s;
    Human h(s);
    //Human h(g);
    Robot s1(s), s2(s), s3(s);
   // Robot s1(g), s2(g), s3(g);

    v->run(g);

}
