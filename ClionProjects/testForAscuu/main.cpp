#include <iostream>

using namespace std;
int stringToAscii(string input);

int main() {
    string plainText;
    cout << "Enter text to convert to ASCII: ";
    getline(cin, plainText);
    stringToAscii(plainText);
    return 0;
}

int stringToAscii(string input){
    for (int i = 0; i < input.length(); ++i) {
        char x = input.at(i);
        cout << int(x);
    }
}