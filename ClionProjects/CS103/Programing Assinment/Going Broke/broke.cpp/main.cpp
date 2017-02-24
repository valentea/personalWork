#include <iostream>
#include <stdlib.h>
#include <iomanip>

using namespace std;

int flipCoin(double prob);
int whoWon(int playerCoins[]);

int main() {
//ALL NEEDED VARIABLES

//TOP PRIORITY VARIABLES
    int numberOfSimulations = 100000;
    const int numberOfPlayers = 3;
    int startingNumC = 4;
    double probOfHeads = .8;
    int numberOfTurns = 0;
    double averageNumberOfTurns = 0;
//INITIALIZE RAND SEED
    srand(time(NULL));
//POSITION OF PLAYERS COIN VALUES IN ARRAYS
    int bill = 0;
    int sarah = 1;
    int john = 2;
    bool noOneLost = true;
    int winner = noOneLost;
    int billCSide = 1;
    int sarahCSide = 1;
    int johnCSide = 1;
    int coinSideVal[numberOfPlayers] = {billCSide, sarahCSide, johnCSide};

    cout << "Enter number of coins followed by the prob of getting heads"
                    " then number of simulations." << endl; //PROMPT USER FOR INPUT
    //cin >> startingNumC >> probOfHeads >> numberOfSimulations;

    int billNumC = startingNumC;
    int sarahNumC = startingNumC;
    int johnNumC = startingNumC;

    for (int k = 0; k < numberOfSimulations; k++) { //DO THIS AS MANY TIMES AS USER WANTS

        //NUMBER OF COINS AT ANY POINT IN THE GAME
        int coinsTotal[numberOfPlayers] = {billNumC, sarahNumC, johnNumC};

        numberOfTurns = 0; //RE-INITIALIZE THE NUMBER OF TURNS EVERY GAME
        while (coinsTotal[bill] != 0 && coinsTotal[sarah] != 0 && coinsTotal[john] != 0) {
            for (int rollTurn = 0; rollTurn < numberOfPlayers; rollTurn++) {
                coinSideVal[rollTurn] = flipCoin(probOfHeads); //STORE VALS OF ROLLS IN ARRAY
            }
            winner = whoWon(coinSideVal);

            if (winner != -1) { //IF THERE IS A WINNER DO LOOP
                for (int i = 0; i < numberOfPlayers; i++) {
                    coinsTotal[i] = coinsTotal[i] - 1; //TAKE COIN FROM EVERYONE
                }
                coinsTotal[winner] = coinsTotal[winner] + numberOfPlayers; //PAY WINNER
            }
            numberOfTurns++;
        }
        averageNumberOfTurns = numberOfTurns + averageNumberOfTurns;
    }
    averageNumberOfTurns = averageNumberOfTurns/numberOfSimulations;
    cout << "Average: " << fixed << setprecision(2) << averageNumberOfTurns; //CALCULATE AVERAGE NUMBER OF TURNS AND PRINT
}

int flipCoin(double prob){
    int heads = 0;
    int coinSide = 0;
    coinSide = rand()%10; //GET NUMBER BETWEEN 0-9
    if(coinSide <= (prob*10)-1){ //MAKE PROBABILITY FACTOR OF 10 AND TEST
        heads = 1;
    }
    return heads;
}

int whoWon(int playerCoins[]){
    int bill = 0;
    int sarah = 1;
    int john = 2;
    if(playerCoins[bill] == playerCoins[sarah] && playerCoins[sarah] == playerCoins[john]){
        return -1;
    }
    for(int i = 0; i <= 1; i++){
        if(playerCoins[i] == playerCoins[i+1]){
            continue;
        }
        else if(i == 1){
            return john;
        }
        else if(i == 0 && playerCoins[i+1] == playerCoins[i+2]){
            return bill;
        }
        else if(i == 0 && playerCoins[i] == playerCoins[i+2]){
            return sarah;
        }
    }
    return 0;
}
