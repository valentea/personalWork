#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int lowEndOfRange=10;
    int highEndOfRange=100;
    bool even = false;

    cout << "Enter range of input values you want to test, separated by a comma." << endl << endl;
    cin >> lowEndOfRange >> highEndOfRange;
    int minLength = INT32_MAX;
    int maxLength = 0;
    int minInput = INT32_MAX;
    int maxInput = 0;

    for (int range = lowEndOfRange; range <= highEndOfRange; range++) {
        int numberOfLoops = 0;
        int inputNumber = range;
        while (inputNumber != 1) {
            if (inputNumber % 2 == even) {
                inputNumber = inputNumber / 2;
            }
            else {
                inputNumber = (inputNumber * 3) + 1;
            }
            numberOfLoops++;
        }

        if(numberOfLoops<minLength){
            minInput = range;
            minLength = numberOfLoops;
        }

        if(numberOfLoops>maxLength){
            maxInput = range;
            maxLength = numberOfLoops;
        }
       // cout << endl << "Input is: " << range  << " Length: " << numberOfLoops << endl;
    }
    cout  << "Shortest length is: " << minLength << endl;
    cout << "input is: " << minInput << endl;
    cout << endl << "Longest length is: " << maxLength << endl;
    cout << "input is: " << maxInput << endl;
}




