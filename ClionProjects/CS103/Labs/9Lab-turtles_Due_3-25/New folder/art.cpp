#include "turtle.h"
#include "draw.h"
#include <cstdlib>
#include <iostream>
using namespace std;

int main() {
    draw::setrange(-100, 100);



    Turtle three(-100, 100, 315);
    Turtle four(-100 ,-100, 45);

    for (int i = 0; i < 10; ++i) {
        int x = 100;
        Turtle one(-100, x, 0);
        one.setColor(draw::RED);
        one.move(200);
        x -= 10;
    }
    for (int i = 0; i < 10; ++i) {
        int x = -100;
        Turtle one(x, 100, 270);
        one.setColor(draw::GREEN);
        one.move(200);
        x += 10;
    }


    return 0;
}
