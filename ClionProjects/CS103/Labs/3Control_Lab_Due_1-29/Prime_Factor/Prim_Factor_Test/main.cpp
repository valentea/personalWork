#include <iostream>

int FindNumberOFTwoRoots(int UserInputNumber);
int FindNumberOfThreeRoots(int UserInputNumber);

using namespace std;

int main() {

    int number;
    int numberOfTwoRoots;
    int numberOfThreeRoots;
    cin >> number;

        if (number % 2 == 0 & number % 3 == 0) {
            numberOfTwoRoots = FindNumberOFTwoRoots(number);
            numberOfThreeRoots = FindNumberOfThreeRoots(number);
            cout << "numberOfTwoRoots = " << numberOfTwoRoots << endl;
            cout << "numberOfThreeRoots = " << numberOfThreeRoots << endl;
        }
        else{
            cout << "no roots applicable" << endl;
        }
    }

int FindNumberOFTwoRoots(int UserInputNumber){
    int numberOfTwoRoots=0;
    while (UserInputNumber % 2 == 0) {
        UserInputNumber = UserInputNumber / 2;
        numberOfTwoRoots++;
    }
    return numberOfTwoRoots;
}

int FindNumberOfThreeRoots(int UserInputNumber){
    int numberOfThreeRoots=0;
    while (UserInputNumber % 3 == 0) {
        UserInputNumber = UserInputNumber / 3;
        numberOfThreeRoots++;
    }
    return numberOfThreeRoots;
}