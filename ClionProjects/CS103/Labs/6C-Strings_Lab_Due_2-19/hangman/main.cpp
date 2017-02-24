// hangman.cpp
// Hangman game illustrates string library functions, 
// character arrays, arrays of pointers, etc.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

// Prototype. we'll define this below.
bool processGuess(char* word, const char* targetWord, char guessedLetterChar);

// Define an array of strings (since a string is just a char array)
//  and since string are just char *'s, we really want an array of char *'s
const char* wordBank[] = {"computer", "president", "trojan", "program",
                          "coffee", "library", "football", "popcorn",
                          "science", "engineer"};
const int numWords = 10;

int main()
{
    char* word = NULL;

    try {
        srand(time(0));
        int numLives = 10;

        // Pick a random word from the wordBank
        const char *targetWord = wordBank[rand() % numWords];

        // More initialization code as needed
        const int lengthOfTargetWord = strlen(targetWord);
        word = new char[lengthOfTargetWord + 1];
        for (int i = 0; i < lengthOfTargetWord; i++) {
            word[i] = '*';
        }
        word[lengthOfTargetWord] = NULL;

        cout << "targetWord: " << targetWord << endl;
        bool successFlag = false;
        while (0 != numLives) {
            cout << "Current word: " << word << endl;
            cout << numLives << " remain...Enter a letter to guess:" << endl;
            char guess = NULL;
            cin >> guess;
            const bool correctLetter = processGuess(word, targetWord, guess);

            if (false == correctLetter) {
                numLives--;
            }

            if (strcmp(targetWord, word) == 0) {
                cout << "The word was: " << targetWord << ". You win!" << endl;
                successFlag = true;
                break;
            }
        }
        if (successFlag == false) {
            cout << "Too many turns...You lose!" << endl;
        }
    }
    catch(exception x){
        cout << x.what() << endl;
    }
    delete[] word;
}

// Given the current version of the word, target/selected word, and
// the character that the user just guessed, change the word to 
// "turn on" any occurrences the guess character and return a count
// of how many occurrences of 'guess' were found
bool processGuess(char* word, const char* targetWord, char guessedLetterChar) {
    bool check = false;
    const int lengthOfTargetWord = strlen(targetWord);
    for (int i = 0; i < lengthOfTargetWord; i++) {
        const char* targetWordTwo = targetWord + i;
        const char correctLetterChar = *targetWordTwo;
        if(correctLetterChar == guessedLetterChar) {
            word[i] = targetWord[i];
            check = true;
        }
    }
    return check;
}