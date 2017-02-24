#include "turtle.h"
#include "draw.h"
#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
//   if (argc != 2) {
//      cerr << "Usage: shape N\nwhere N is an integer >= 3" << endl;
//      std::exit(1);
//   }
//   int N = atoi(argv[1]);
//
   draw::setrange(-100, 100);
//
//   Turtle t(-25, -50, 0);
//   for (int i=0; i<N; i++) {
//      t.move(300.0/N); // draw a shape with perimeter 300 steps
//      t.turn(360.0/N); // do a full turn in N parts
//   }
//
//   if (N<0) { // easter egg
//      for (int i=0; i<4; i++) {
//         t.move(50); t.turn(-45); t.move(50); t.turn(135);
//      }
//   }
    srand(time(NULL));




    draw::show(1000);

    int oneX = 100;
   for (int i = 0; i < 20; ++i) {
      Turtle one(-100, oneX, 0);
      one.setColor(draw::RED);
      one.move(200);
       int step = rand()%10;
      oneX -= step;
       one.turn(rand());
   }
    int twoX = -100;
   for (int i = 0; i < 20; ++i) {
      Turtle two(twoX, 100, 270);
      two.setColor(draw::GREEN);
      two.move(200);
       int step = rand()%10;
       twoX += step;
       two.turn(-rand());
   }
    int threeX = 95;
   for (int i = 0; i < 20; ++i) {
       Turtle three(-100, threeX, 315);
      three.setColor(draw::BLACK);
      three.move(200);
      threeX -= 10;
   }
    int fourX = -95;
   for (int i = 0; i < 20; ++i) {
       Turtle four(fourX ,-100, 45);
      four.setColor(draw::BLUE);
      four.move(200);
      fourX += 10;
   }
    draw::show(1000);

   return 0;
}
