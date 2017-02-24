#include <iostream>
#include <cmath>
//#include <w32api/commctrl.h>
#include "bmplib.h"

using namespace std;

// global variable. bad style but ok for this lab
unsigned char image[SIZE][SIZE];

// Fill in this function:
void draw_rectangle(int topRow, int leftCollum, int height, int width) {
    cout << "Enter 'topRow' " << endl;
    cin >> topRow;
    cout << "Enter 'leftCollum' " << endl;
    cin >> leftCollum;
    cout << "Enter 'height' " << endl;
    cin >> height;
    cout << "Enter 'width' " << endl;
    cin >> width;

    for (int i=0; i < SIZE; i++) {      //Make everything white
        for (int j=0; j < SIZE; j++) {
            image[i][j] = 255;
        }
    }

    for (int i=leftCollum; i <= width; i++) {
        for (int j=0; j < SIZE; j++) {
            image[i][j] = 255;
        }
    }





}

// Fill in this function:
void draw_ellipse(int cy, int cx, int height, int width) {

}


int main() {
   // initialize the image to all white pixels
   for (int i=0; i < SIZE; i++) {
      for (int j=0; j < SIZE; j++) {
         image[i][j] = 255;
      }
   }

   // Main program loop here



   // Write the resulting image to the .bmp file
   writeGSBMP("output.bmp", image);

   return 0;
}
