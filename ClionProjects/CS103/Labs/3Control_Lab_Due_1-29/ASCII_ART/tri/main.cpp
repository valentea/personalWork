#define M_PI 3.14159265358979323846

#include <iostream>
#include <cmath>

using namespace std;

double GetRadiansFromDegrees(double UserInput);

int main() {
    double  UserInputThetaInDegrees = 0;
    cout << "Please Enter A value for Theta between 15 and 75" << endl;
    cin >> UserInputThetaInDegrees;

    double UserInputThetaInRadians = 0;
    double MaxNumberInCollum = 0;

    UserInputThetaInRadians = GetRadiansFromDegrees(UserInputThetaInDegrees);


    for (int i = 1; i < 31; i++) {
        MaxNumberInCollum = tan(UserInputThetaInRadians)*i;
        MaxNumberInCollum = floor(MaxNumberInCollum);
        if(MaxNumberInCollum >= 20 && MaxNumberInCollum <= 30){
            for (int k = 0; k < 20; ++k) {
                cout << "*";
            }
        }else{
            for (int j = 1; j <= MaxNumberInCollum; j++) {
                cout << "*";
            }

        }
        //cout << "   LINE: " << i << "||||| Max: " << MaxNumberInCollum << endl;
        cout << endl;
    }
    return 0;
}

double GetRadiansFromDegrees(double UserInput){
    double Radians;
    Radians = (UserInput * M_PI) / 180;
    return Radians;
}
