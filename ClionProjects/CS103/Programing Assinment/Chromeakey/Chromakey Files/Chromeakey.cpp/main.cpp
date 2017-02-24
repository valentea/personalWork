/*********************************************************************
 File:     chromakey.cpp

 Author:   Alex Valente

 Email address: valentea@usc.edu

 Usage: program_name in.bmp background.bmp dist_threshold out1.bmp out2.bmp

 Notes:
 This program performs the chroma key operation on an input 
 using two different methods.

 Method 1 Utilize a user-defined distance threshold from the
          chromakey value as a discriminator

 Method 2 Devise a method that to determine the chromakey mask
          that doesn't require a user-input threshold

********************************************************************/

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "bmplib.h"

using namespace std;

// Prototypes
// IMPORTANT: you must exactly use these input types, function names, and 
// return types. Otherwise the grader can't test them.
void method1(unsigned char inImage[][SIZE][RGB],
	     bool mask[][SIZE],
	     double threshold);

void method2(unsigned char inImage[][SIZE][RGB], 
	     bool mask[][SIZE]);

void replace(bool mask[][SIZE],
	     unsigned char inImage[][SIZE][RGB],
	     unsigned char bgImage[][SIZE][RGB],
	     unsigned char outImage[][SIZE][RGB]);

int main(int argc, char *argv[]) {
    // Image data array
    // Note:  DON'T use the static keyword except where we expressly say so.
    //        It puts the large array in a separate, fixed, area of memory.
    //        It is bad practice. But useful until we have dynamic allocation.
    static unsigned char inputImage[SIZE][SIZE][RGB];
    static unsigned char bgrndImage[SIZE][SIZE][RGB];
    static unsigned char outputImage[SIZE][SIZE][RGB];
    static bool chromaMask[SIZE][SIZE];

    double threshold;

    if (argc < 6) {
        cerr << "usage: program_name in.bmp background.bmp dist_threshold "
        << "out1.bmp out2.bmp" << endl;
        return 0;
    }

    if (readRGBBMP(argv[1], inputImage)) {
        cerr << "Error reading file: " << argv[1] << endl;
        return 1;
    }

    if (readRGBBMP(argv[2], bgrndImage)) {
        cout << "Error reading file: " << argv[2] << endl;
        return 1;
    }

    // Write code to convert the threshold (argv[3])
    //  from string format to a double and assign the 'threshold'
    threshold = atof(argv[3]);

    // Call Method 1 Function
    //
     method1(inputImage, chromaMask, threshold);

    // Produce the output by calling replace
    //
     replace(chromaMask, inputImage, bgrndImage, outputImage);

    // Write the output image to a file using the filename argv[4]
    if (writeRGBBMP(argv[4], outputImage)) {
        cout << "Error writing file: " << argv[4] << endl;
        exit(1);
    }

    // Call Method 2 Function
    method2(inputImage,chromaMask);

    // Produce the output by calling replace()


    // Write the output image to a file using the filename argv[5]
    if (writeRGBBMP(argv[5], outputImage)) {
        cout << "Error writing file: " << argv[5] << endl;
        exit(1);
    }

    return 0;
}



// Use user-provided threshold for chroma-key distance
// The "output" of this method is to produce a valid mask array
//  where entries in the mask array are 1 for foreground image
//  and 0 for 'background'
void method1(unsigned char inImage[][SIZE][RGB],
	     bool mask[][SIZE],
	     double threshold) {
    double lineAverageRed;
    double lineAverageGreen;
    double lineAverageBlue;
    for (int i = 0; i < 65; i++) {
        double red = 0;
        double green = 0;
        double blue = 0;
        for (int j = 0; j < SIZE; j++) {
            red += inImage[i][j][0];
            green += inImage[i][j][1];
            blue += inImage[i][j][2];
        }
        lineAverageRed += red / SIZE - 1;
        lineAverageGreen += green / SIZE - 1;
        lineAverageBlue += blue / SIZE - 1;
    }
    for (int j = 0; j < 25; j++) {
        double red = 0;
        double green = 0;
        double blue = 0;
        for (int i = 0; i < SIZE; i++) {
            red += inImage[i][j][0];
            green += inImage[i][j][1];
            blue += inImage[i][j][2];
        }
        lineAverageRed += red / SIZE - 1;
        lineAverageGreen += green / SIZE - 1;
        lineAverageBlue += blue / SIZE - 1;
    }
    double pictureAverageRed = lineAverageRed / 90;
    double pictureAverageGreen = lineAverageGreen / +90;
    double pictureAverageBlue = lineAverageBlue / 90;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            double distance = 0;
            double differenceRed = inImage[i][j][0] - pictureAverageRed;
            double differenceGreen = inImage[i][j][1] - pictureAverageGreen;
            double differenceBlue = inImage[i][j][2] - pictureAverageBlue;
            distance = sqrt(pow(differenceRed, 2) + pow(differenceGreen, 2) + pow(differenceBlue, 2));
            if (distance > threshold) {
                mask[i][j] = 1;
            }
            cout << int(mask[i][j]);
        }
        cout << endl;
    }
}

// Devise a method to automatically come up with a threshold
//  for the chroma key determination
// The "output" of this method is to produce a valid mask array
//  where entries in the mask array are 1 for foreground image
//  and 0 for 'background'
void method2(unsigned char inImage[][SIZE][RGB], 
	     bool mask[][SIZE])  
{
//    int maxNumberOfPixels = pow(SIZE,2);
//    int hexVar[maxNumberOfPixels];
//    for (int i = 0; i < SIZE; i++) {
//        for (int j = 0; j < SIZE; j++) {
//                int red = inImage[i][j][0];
//                int green = inImage[i][j][1];
//                int blue = inImage[i][j][2];
//                int totalPixelCount = (SIZE*i)+(j+1);
//                hexVar[totalPixelCount] = (red << 16)|(green << 8)|blue;
//        }
//    }
//    long averageHex = 0;
//    for (int l = 0; l < maxNumberOfPixels; ++l) {
//        averageHex = averageHex + hexVar[l];
//    }
//    averageHex = averageHex/maxNumberOfPixels;
//
//    double standDeviation = .5*maxNumberOfPixels;
//    int halfOfMaxPixels = maxNumberOfPixels/2;
//    double minHexVal = hexVar[halfOfMaxPixels]-standDeviation;
//    double maqHexVal = hexVar[halfOfMaxPixels]+standDeviation;
//    for (int k = 0; k < SIZE; ++k) {
//        for (int i = 0; i < SIZE; ++i) {
//            int red = inImage[k][i][0];
//            int green = inImage[k][i][1];
//            int blue = inImage[k][i][2];
//            int testPixel = (red << 16)|(green << 8)|blue;
//            if(testPixel>minHexVal && testPixel<minHexVal){
//                mask[k][i] = 0;
//            }
//            cout << mask[k][i];
//        }
//        cout << endl;
//    }


}

// If mask[i][j] = 1 use the input image pixel for the output image
// Else if mask[i][j] = 0 use the background image pixel
void replace(bool mask[SIZE][SIZE],
	     unsigned char inImage[SIZE][SIZE][RGB],
	     unsigned char bgImage[SIZE][SIZE][RGB],
	     unsigned char outImage[SIZE][SIZE][RGB]) {
    // Create the output image using the mask to determine
    //  whether to use the pixel from the Input or Background image
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (mask[i][j]) {
                for (int k = 0; k < 3; k++) {
                    outImage[i][j][k] = inImage[i][j][k];
                }
            }
            else {
                for (int k = 0; k < 3; k++) {
                    outImage[i][j][k] = bgImage[i][j][k];
                }
            }
        }
    }
}
