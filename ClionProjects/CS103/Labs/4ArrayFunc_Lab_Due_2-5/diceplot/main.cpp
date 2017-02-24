#include <iostream>
#include <stdlib.h>

using namespace std;

int roll();
int printHistogram(int counts[]);

int main() {
    srand(time(NULL));
    int sumOfFourRolls = 0;
    int numberOfSumsArray[21];
    for (int j = 0; j < 21; ++j) {
        numberOfSumsArray[j] = 0;
    }
    long long n;
    cout << "How many rolls do you want? " << endl;
    cin >> n;

    for (int k = 0; k < n; ++k) {
        int rollValues[4];
        if(sumOfFourRolls =! 0){
            for (int i = 0; i < 4; ++i) {
                rollValues[i] = 0;
            }
        }
        for (int i = 0; i < 4; ++i) {
            rollValues[i] = roll();
            sumOfFourRolls += rollValues[i];
        }
        numberOfSumsArray[sumOfFourRolls-4] += 1;
    }
    printHistogram(numberOfSumsArray);
    cout << endl;

    return 0;
}

int roll() {
    int diceRollValue = (rand() % 6) + 1;
    return diceRollValue;
}

int printHistogram(int counts[]) {
    for (int i = 0; i < 21; ++i) {
        int numberOfTimesToPrintX = counts[i];
        if (i <= 5) {
            cout << " " << i + 4 << ": ";
        }
        else {
            cout << i + 4 << ": ";
        }
        for (int j = 0; j < numberOfTimesToPrintX; ++j) {
            cout << "x";
        }
        cout << endl;
    }
}
