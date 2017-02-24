#include <iostream>

using namespace std;

int main() {
    //VARIABLES USED IN THIS PROGRAM
    int UserInputNumber;
    int HundredsPlaceHolder;
    int TensPlaceHolder;
    int OnesPlaceHolder;

    //REQUEST USER FOR NUMBER BETWEEN 0 AND 999
    cout << "Please Enter An Integer Between 0 And 999" << endl;
    cin >> UserInputNumber;

    if(UserInputNumber<0 | UserInputNumber > 999){
        do{
            cout << "Please Enter A Number Less Than 1000 and Bigger Than 0" << endl;
            cin >> UserInputNumber;
        }
        while(UserInputNumber<0 | UserInputNumber >999);
    }
    
    HundredsPlaceHolder = UserInputNumber/100;
    TensPlaceHolder = (UserInputNumber - (HundredsPlaceHolder*100))/10;
    OnesPlaceHolder = UserInputNumber - (HundredsPlaceHolder * 100) - TensPlaceHolder * 10;

    cout << "OnesPlaceHolder is " << OnesPlaceHolder << endl;
    
    cout << "TensPlaceHolder is " << TensPlaceHolder << endl;
    
    cout << "HundredsPlaceHolder is " << HundredsPlaceHolder << endl;





    return 0;
}
