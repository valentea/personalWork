#include <iostream>


using namespace std;

int main() {
    int OriginalNumber = 0;
    int TotalNubmerOfThrees = 0;
    int TotalNumberOfTwos = 0;

    cin >> OriginalNumber;
    if (OriginalNumber % 2 == 0 || OriginalNumber % 3 == 0) {

        while (OriginalNumber != 1) {

            if (OriginalNumber % 2 == 0) {
                OriginalNumber = OriginalNumber / 2;
                TotalNumberOfTwos++;
            }
            else if (OriginalNumber % 3 == 0) {
                OriginalNumber = OriginalNumber / 3;
                TotalNubmerOfThrees++;
            }
            else{
                cout << "No" << endl;
                return 0;
            }
        }
        cout << "Yes" << endl;
        cout << "Twos=" << TotalNumberOfTwos;
        cout << " Threes=" << TotalNubmerOfThrees << endl;
        return 0;
    }
    else{
        cout << "No" << endl;
        return 0;
    }

}
