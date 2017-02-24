#include <iostream>
#include <cmath>
#include "bmplib.h"

using namespace std;

// global variable. bad style but ok for this lab
unsigned char image[SIZE][SIZE];

// Fill in this function:
void draw_rectangle(int topRow, int leftCollum, int height, int width) {


//    cout << "Enter 'topRow' " << endl;
//    cin >> topRow;
//    cout << "Enter 'leftCollum' " << endl;
//    cin >> leftCollum;
//    cout << "Enter 'height' " << endl;
//    cin >> height;
//    cout << "Enter 'width' " << endl;
//    cin >> width;

    for (int k = leftCollum; k < leftCollum + width; ++k) {
        image [height][k] = 0;
    }







}

// Fill in this function:
void draw_ellipse(int cy, int cx, int height, int width) {

}


int main() {
   // initialize the image to all white pixels
   for (int i=0; i < SIZE; i++) {
      for (int j=0; j < SIZE; j++) {
         image[i][j] = 0;
      }
   }

   // Main program loop here

   // draw_rectangle(10,20,30,40);


   // Write the resulting image to the .bmp file
    writeGSBMP("output1.bmp", image);

   return 0;
}
