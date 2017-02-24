#include <iostream>
#include <climits>

using namespace std;

int main() {
    //DEFINE ALL NEEDED VARIABLES
    int lowEndOfRange=10;
    int highEndOfRange=100;
    bool even = false;
    int minLength = INT_MAX;
    int maxLength = 0;
    int minInput = INT_MAX;
    int maxInput = 0;

    //PROMPT AND RECEIVE USER MIN/MAX RANGE
    cout << "Enter range of input values you want to test,";
    cout << " separated by a space." << endl << endl;
    cin >> lowEndOfRange >> highEndOfRange;

    //Check user input for min<max
    if(highEndOfRange < lowEndOfRange) {
        cout << "First put input low end range, then max end of range" << endl;
        return 1;
    }

    //LOOP EVERY NUMBER IN GIVEN RANGE TO FIND NUBMER OF LOOPS NEED
    for (int range = lowEndOfRange; range <= highEndOfRange; range++) {
        int numberOfLoops = 0;   //MAKE numberOfLoops 0 AT BEGINNING OF 
        int inputNumber = range;    //EVERY NEW LOOP
        while (inputNumber != 1) { //KEEP DOING THIS L00P UNTIL THE NUMBER GETS TO 1 (END OF HAILSTONE LOOP)
            if (inputNumber % 2 == even) {        //IF EVEN; DIVIDE BY TWO
                inputNumber = inputNumber / 2;
            }
            else {                  //IF ODD; MULTIPLY BY THREE AND ADD ONE
                inputNumber = (inputNumber * 3) + 1;
            }
            numberOfLoops++;
        }

        if(numberOfLoops<minLength){  //CHECK IF THE NUMBER OF LOOPS IS 
            minInput = range;             //THE SMALLEST THUS FAR
            minLength = numberOfLoops;
        }

        if(numberOfLoops>maxLength){    //CHECK IF THE NUMBER OF LOOPS IS 
            maxInput = range;              //THE BIGEST THUS FAR
            maxLength = numberOfLoops;
        }
    }

    //OUTPUT THE WANTED INFORMATION
    cout  << "Shortest length is: " << minLength << endl;
    cout << "input is: " << minInput << endl;
    cout << endl << "Longest length is: " << maxLength << endl;
    cout << "input is: " << maxInput << endl;

    return 0;
}
