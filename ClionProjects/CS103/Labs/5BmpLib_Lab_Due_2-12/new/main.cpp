#include <iostream>
#include <cmath>
#include "bmplib.h"
#define M_PI 3.14159265358979323846

using namespace std;

// global variable. bad style but ok for this lab
unsigned char image[SIZE][SIZE];

// Fill in this function:
void draw_rectangle(int topRow, int leftCollum, int height, int width) {
    for (int k = leftCollum; k < leftCollum + width && k <= SIZE; ++k) { //make top and bottom line
        image [topRow][k] = 0;
        if((topRow + height) <= SIZE) {
            image[topRow + height][k] = 0;
        }
    }
    for (int i = topRow; i < topRow + height && i <= SIZE; ++i) { //make left and right line
        image [i][leftCollum] = 0;
        if((leftCollum + width) <= SIZE) {
            image[i][leftCollum + width] = 0;
        }
    }
}



// Fill in this function:
void draw_ellipse(int cy, int cx, int height, int width) {

    double rx = height / 2;
    double ry = width / 2;

    for (double theta = 0.0; theta < 2 * M_PI; theta += .01) {
        double y = rx * cos(theta);
        double x = ry * sin(theta);
        x += cx;
        y += cy;
        if(x <= SIZE && y <= SIZE && x >= 0 && y >= 0) {
            image[(int) y][(int) x] = 0;
        }
    }
}


int main() {
    // initialize the image to all white pixels
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = 255;
        }
    }
    int shape;
    int topRow;
    int leftCollum;
    int height;
    int width;
    cout << "To draw a rectangle, enter: 0 top left height width" << endl;
    cout << "To draw an ellipse, enter: 1 cy cx height width" << endl;
    cout << "To save your drawing as 'output.bmp' and quit, enter: 2" << endl;
    for (int k = 0; k < 100; ++k) {

        cin >> shape;
        if (shape == 2) {
            break;
        }
        cin >> topRow >> leftCollum >> height >> width;
        if (shape == 0) {
            draw_rectangle(topRow, leftCollum, height, width);
        }
        else if (shape == 1) {
            draw_ellipse(topRow, leftCollum, height, width);;
        }
    }
    // Write the resulting image to the .bmp file
    writeGSBMP("mainTest.bmp", image);
    return 0;
}
