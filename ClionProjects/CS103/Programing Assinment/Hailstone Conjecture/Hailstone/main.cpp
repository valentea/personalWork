#include <iostream>
#include <cmath>
using namespace std;

int main() {
    //DECLARE VARIABLES
    long InputNubmer = 0;
    long NumberOfLoops = 0;
    bool EvenOrOdd = false;

    //PROMPT USER FOR INPUT OF ORIGINAL NUMBER
    cout << "Please input original number to run the HailStone Computation on." << endl;
    cin >> InputNubmer;

    while (InputNubmer != 1) {                //RUN THIS LOOP UNTIL OUTPUT HAS REACHED ZERO AND ENDED THE LOOP
        if (InputNubmer % 2 == EvenOrOdd) {   //IF EVEN; DIVIDE BY TWO
            InputNubmer = InputNubmer / 2;
            cout << InputNubmer << " ";
        }
        else {                                //IF ODD; MULTIPLY BY THREE AND ADD ONE
            InputNubmer = (InputNubmer * 3) + 1;
            cout << InputNubmer << " ";
        }
        NumberOfLoops++;                      //ADD TOO TOTAL NUMBER OF LOOPS
    }

    cout << endl << "Length: " << NumberOfLoops << endl;
}