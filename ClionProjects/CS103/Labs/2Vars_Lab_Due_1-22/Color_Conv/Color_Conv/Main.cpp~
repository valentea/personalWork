#include <iostream>
#include <algorithm>

using namespace std;

double ReadValidValueFromUser(string ColorName) {
    cout << "Enter Value for Color " << ColorName << endl;      //SHOW USER WHAT COLOR TO PUT VALUE IN
    int Color;
    cin >> Color;                                               //GET COLOR VALUE FROM USER
    if (Color > 255 | Color < 0) {                              //MAKE SURE THAT RED IS WITHIN Parameter
        do {
            cout << "Please Enter Integer For " << ColorName << " Between 0 and 255" << endl;
            cin >> Color;
        }
        while (Color > 255 | Color < 0);
    }
    return Color;                                               //RETURN VALUE OF USER INPUTTED COLOR FOR MAIN CAL
}


int main()
{
    //VARIABLES USED
    double White;
    double Cyan;
    double Magenta;
    double Yellow;
    double Black;
    //VARIABLES RECEIVED BY THE USER
    double Red;
    double Green;
    double Blue;
    //COLOR VARIABLES
    double FractionOfRed;
    double FractionOfGreen;
    double FractionOfBlue;

    //REQUEST VALUES OF VARIABLES FROM USER
    Red = ReadValidValueFromUser("Red");

    Green = ReadValidValueFromUser("Green");

    Blue = ReadValidValueFromUser("Blue");

    //PRINT INTRO TO COLOR CONVERSION FOR USER
    cout << "For the RGB Values Inputted (RED, " << Red << "; GREEN, " << Green << "; BLUE, " << Blue << ") The CMYB Values Are As Follows:" << endl;

    //GET VALUES FOR THE CMYB COLOR SCALE USING THE INPUTTED RGB VALUES
        //GETTING COLOR DIVIDED BY 255 FOR FINAL COLOR CONVERSION
        FractionOfRed = Red/255;
        FractionOfGreen = Green/255;
        FractionOfBlue = Blue/255;


        //WHITE
        White = max(FractionOfRed, max(FractionOfGreen, FractionOfBlue));
        //cout << "Value of White is " << White << endl;          //SEE VALUE OF WHITE FOR DEBUGGING

        //CYAN
        Cyan = (White-FractionOfRed)/White;
        cout << "Value Of Cyan is " << Cyan << endl;            //SEE VALUE OF CYAN

        //MAGENTA
        Magenta = (White-FractionOfGreen)/White;
        cout << "Value of Magenta is " << Magenta << endl;      //SEE VALUE OF MAGENTA

        //YELLOW
        Yellow = (White-FractionOfBlue)/White;
        cout << "Value of Yellow is " << Yellow << endl;       //SEE VALUE OF YELLOW

        //BLACK
        Black = 1-White;
        cout << "Value of Black is " << Black << endl;          //SEE VALUE OF BLACK



    return 0;
}

