// wscramble.cpp
// Word Scramble guessing game
// Illustrates string library functions, character arrays,
//  arrays of pointers, etc.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>
#include <typeinfo>

using namespace std;

// Scramble the letters of this string randomly
void permute(char items[], int len);

// Define an array of strings (an array of char pointers, like argv)

//const char* wordBank[] = {
//        "computer", "president", "trojan", "program", "coffee",
//        "library", "football", "popcorn", "science", "engineer"};

//const int numWords = 10;

int main(int argc, char* argv[]) {
    srand(time(NULL));
    char guess[80];

    bool wordGuessed = false;
    int numTurns = 10;
    ifstream in_file;
    in_file.open(argv[1]);


    if(argc != 2){
        return 2;
    }

    if (!in_file) {
        return 3;
    }

    else {
        //int numberOfWords = 0;
        int totalNumberWords;
        in_file >> totalNumberWords;
        if(!in_file.fail){
            return 1;
        }
        char *scrambledWord[10];

        for (int i = 0; i < totalNumberWords; i++) {
            char word[80];
            in_file >> word;
            int targetLen = strlen(word);
            strcpy(scrambledWord[i], word);
        }
        in_file.close();
        // Pick a random word from the wordBank
        int target = rand() % totalNumberWords;
        int targetLength = strlen(scrambledWord[target]);

        char* word = new char[target+1];
        strcpy(word, scrambledWord[target]);
        permute(word, targetLength);

        // An individual game continues until a word
        //  is guessed correctly or 10 turns have elapsed
        while (!wordGuessed && numTurns > 0) {
            cout << "Scrambled word: " << word << endl;
            cout << "What do you guess the original word is? ";
            cin >> guess;
            wordGuessed = (strcmp(guess, scrambledWord[target]) == 0);
            numTurns--;
        }
        if (wordGuessed) {
            cout << "You win!" << endl;
        }
        else {
            cout << "Too many turns...You lose!" << endl;
        }
        delete [] word;
        for(int j=0;j<totalNumberWords;j++)
        {
            delete [] scrambledWord[j];
        }
        return 0;
    }
}

// Scramble the letters. See "Knuth shuffle" on Wikipedia.
void permute(char items[], int len) {
    for (int i = len-1; i > 0; --i) {
        int r = rand() % i;
        char temp = items[i];
        items[i] = items[r];
        items[r] = temp;
    }
}