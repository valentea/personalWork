#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <boost/multiprecision/cpp_int.hpp>


using namespace std;

int gcdExtended(int a, int b, int *x, int *y); //Using Extended Eulers method to find GCD
int modInverse(int *e, int tn); //Solves Modular Multiplicatine Inverse equations
bool isPrime(int input); //Checks input for prime properties
void stringToAscii(string input, int* messageArray); //Takes string and using references inputs Ascii letter by
int numberOfPrimeFactors(int n); //UNUSED CURRENTLY.......                                      letter to an array.
void primeFactorArray(int n, int *test); //UNUSED CURRENTLY
static char ReadAllBytes(const char  filename, int* read); //Changes String to a bitStream
void encryptMsg(int n, int e, int* messageArray); //Takes public key and using references changes Ascii array

int main() {

    beginning: //When done with any step 'goto' here to continue program
    int menu;
    cout << "Welcome to my first 'END to END Two Key' encryption algorithm." << endl;
    cout << "Please choose what you would like to do" << endl;
    cout << "1. Create New public and private keys manually." << endl;
    cout << "2. Encode message using Public key by typing message in." << endl;
    cout << "3. Decode message using Private key." << endl;
    cout << "4. Exit program." << endl;
    cout << "5. test" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "Enter number of your choice." << endl;
    cin >> menu; //Enter number to jump to choice on menu


    if (1 == menu) {
        int p, q;
        Error1: //If one or two numbers are not prime go back and re-enter numbers
        cout << "Enter two prime numbers as your foundation to the encryption. The larger the prime number the more "
                "secure the encryption will be." << endl;
        cin >> p >> q;
        if (!isPrime(p)) { //Check if input is prime
            cout << "The value '" << p << "' is not prime." << endl;
            cout << "Please try again." << endl;
            goto Error1;  //If not try again
        }
        if (!isPrime(q)) {//Check if input is prime
            cout << "The value '" << q << "' is not prime." << endl;
            cout << "Please try again." << endl << endl;
            goto Error1; //If not prime try again
        }
        int n;
        n = p * q;
        int tn;
        tn = (p - 1) * (q - 1);
        cout << endl << "Enter a number that is in between 1 and " << tn << ". This number must "
                "be CO-PRIME with " << tn << endl;
        cout << "ONCE AGAIN THIS NUMBER MUST BE CO-PRIME AND THERE IN NO INPUT CHECK." << endl;
        cout << "For a more secure encryption pick a number that has a large binary bit-length "
                "and a large binary hammer weight" << endl;
        cout << "If you do not know what a Co-Prime number is, or you are too lazy to find one for " << tn <<
        " then enter any prime number that is less than " << tn << "." << endl;
        int d;
        int *e;
        d = modInverse(e, tn); //Solve Modular Multiplicative Inverse
        cout << "The Public key has two parts. You must use them IN THIS ORDER." << endl;
        cout << "The public key is (" << n << ", " << *e << ")" << endl;
        cout << "The private key is (" << d << ")" << endl;
        cout << "The private key is meant for your eyes only. Keep it PRIVATE!" << endl;
        cout << endl << endl;
        goto beginning; //Go back to main menu because this section of code is done.
    }

    else if(2 == menu){
        cout << "Enter the message that you would like to encrypt." << endl;
        string message; //The actual character array that you would like to encrypt.
        cin.ignore(); //This is needed because the std::getline function while using
                      //'cin' will read the '\n' at the end of the last 'cout' and cant
                      //take the message. This ignores the new line so we can input a message.
        getline(cin, message);
        int messageArray[500]; //NEEDS TO BE WORKED ON!!! It should be dynamically allocated memory because
        //message length may change. This is the actual array that will hold the
        //ascii message and the post encrypted message. Also data type is 'long long'
        //to accommodate for large numbers in encryption.
        stringToAscii(message, messageArray);
        int index = 0;
        while(messageArray[index] != '\0'){ //Goes letter by letter and prints ascii message to console. Ends when
            //'null' character is found. AKA when the string array is done, even
            //tho we allocate too much memory. Needs to be fixed like above.
            cout << messageArray[index] << " ";
            index++;  //Increases index of messageArray;
        }
        cout << endl << "Enter the values for two values for your private key. They must be in the order "
                "they are given to you." << endl;
        int n, e;
        cin >> n >> e; //Take private key from user to encrypt message
        encryptMsg(n, e, messageArray);
        goto beginning;
    }


//    else if(5 == menu){
//        int number;
//        int total =numberOfPrimeFactors(number);
//        cout << "enter numbre" << endl;
//        cin >> number;
//
//        int *poop;
//        poop = new int[total];
//        primeFactorArray(number, poop);
//        for (int i = 0; i < total; ++i) {
//                cout << poop[i] << " ";
//        }
//    }

    else if(4 == menu) {
        return 0; //Ends the program.
    }
}

int modInverse(int *e, int tn) {
    int x, y;
    test:
        cin >> *e;
        int g = gcdExtended(*e, tn, &x, &y);
        if (g != 1) {
            cout << "The number you entered was not Co-Prime with " << tn << endl;
            cout << "Try again." << endl;
            goto test;
        }
        else {
            int res = (x % tn + tn) % tn;
            return res;
        }
}

int gcdExtended(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0, *y = 1;
        return b;
    }

    int x1, y1;
    int gcd = gcdExtended(b % a, a, &x1, &y1);


    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

bool isPrime(int input){
    bool prime = true;
    for (int i = 2; i < input/2; ++i) {
        if(input%i == 0){
            prime = false;
        }
    }
    if(!prime){
        return prime;
    }
    else{
        return prime;
    }
}

void stringToAscii(string input, int* messageArray){
    for (int i = 0; i < input.length(); ++i) {
        char x = input.at(i);
        messageArray[i] = int(x);
    }
}

int numberOfPrimeFactors(int n) {
    int total = 0;
    while (n % 2 == 0) {
        n = n / 2;
        total++;
    }
    for (int i = 3; i <= sqrt(n); i = i + 2) {
        while (n % i == 0) {

            n = n / i;
            total++;
        }
    }
    if(n > 2){
        total++;
    }
    return total;
}

void primeFactorArray(int n, int* test) {
    int x = 0;
    while (n % 2 == 0) {
        cout << "2" << endl;
        test[x] = 2;
        x++;
        n = n / 2;
    }
    for (int i = 3; i <= sqrt(n); i = i + 2) {
        while (n % i == 0) {
            cout << i << endl;
            test[x] = i;
            x++;
            n = n / i;
        }
    }
    if(n > 2){
        cout << n << endl;
        test[x] = n;
        x++;
    }
}
//static char ReadAllBytes(const char  filename, int* read) {
//    ifstream ifs(filename, ios::binary | ios::ate);
//    ifstream::pos_type pos = ifs.tellg();
//
//    int length = pos;
//
//    char *pChars = new char[length];
//    ifs.seekg(0, ios::beg);
//    ifs.read(pChars, length);
//
//    ifs.close();
//    *read = length;
//    return pChars;
//}

void encryptMsg(int n, int e, int* messageArray) {
    int i = 0;
    while (messageArray[i] != '\0') {
        unsigned long long int powerOfN = 0;
        powerOfN = pow(messageArray[i], e);
        int encrpytNumber = powerOfN % n;
        messageArray[i] = encrpytNumber;
        i++;
    }
    cout << endl;
    i = 0;
    while (messageArray[i] != '\0') {
        char encryptLetter = messageArray[i] + 1;
        cout << encryptLetter;
        i++;
    }
    cout << endl;
}