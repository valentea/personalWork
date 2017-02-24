/*
 *  File: election.cpp
 *  Name: Alex Valente
 *  Email: valentea@usc.edu
 *
 *  Description:
 *    Counts votes for Republic and Democratic candidates
 *    printing the total number of votes in the Dem and Rep party,
 *    the winner in each party and the percentage of
 *    votes the winner received from all those who voted in that party
 *
 */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

/* Convenience struct to group candidate info. Use if desired */
struct Candidate {
    std::string name;
    int votes;
};

/* Prototype for given printResults function         *
 *  You must use this function to print your results */
void printResults(int totalDemVotes,
                  std::string demWinnerName,
                  double demWinningPercent,
                  int totalRepVotes,
                  std::string repWinnerName,
                  double repWinningPercent);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Please provide an input file";
        return 1;
    }

    ifstream dataFile;
    dataFile.open(argv[1]);

    if (dataFile.fail()) {
        cout << "Invalid file" << endl;
        return 1;
    }

    int numberOfVotes;
    dataFile >> numberOfVotes;
    int repTotalVotes = 0;
    int demTotalVotes = 0;
    string party;
    string *partyArray = new string[numberOfVotes];
    string *candidatesArray = new string[numberOfVotes];
    string tempCan;
    int *candidateVotes = new int[numberOfVotes];
    for (int i = 0; i < numberOfVotes; i++) {
        candidateVotes[i] = 0;
    }
    for (int i = 0; i < numberOfVotes; ++i) {
        dataFile >> party;
        dataFile >> tempCan;
        partyArray[i] = party;
        for (int j = 0; j < numberOfVotes; ++j) {
            if (candidatesArray[j] == tempCan) {
                candidateVotes[i]++;
            }
        }
        candidatesArray[i] = tempCan;
        candidateVotes[i]++;
        if (party == "Rep") {
            repTotalVotes++;
        }
        else if (party == "Dem") {
            demTotalVotes++;
        }
    }

    string demWinner;
    double demWinnerVotes = 0;
    string repWinner;
    double repWinnerVotes = 0;
    double demTempMaxVotes = 0;
    double repTempMaxVotes = 0;

    for (int k = 0; k < numberOfVotes; k++) {
        if (partyArray[k] == "Rep") {
            if (candidateVotes[k] > repTempMaxVotes) {
                repTempMaxVotes = candidateVotes[k];
                repWinner = candidatesArray[k];
                repWinnerVotes = candidateVotes[k];
            }
        }
        else if (partyArray[k] == "Dem") {
            if (candidateVotes[k] > demTempMaxVotes) {
                demTempMaxVotes = candidateVotes[k];
                demWinner = candidatesArray[k];
                demWinnerVotes = candidateVotes[k];
            }
        }
    }
    double demWinningPercent = demWinnerVotes / demTotalVotes;
    double repWinningPercent = repWinnerVotes / repTotalVotes;

    printResults(demTotalVotes, demWinner, demWinningPercent, repTotalVotes, repWinner, repWinningPercent);

    delete[] partyArray;
    delete[] candidatesArray;
    delete[] candidateVotes;
    return 0;
}

void printResults(int totalDemVotes,
                  std::string demWinnerName,
                  double demWinningPercent,
                  int totalRepVotes,
                  std::string repWinnerName,
                  double repWinningPercent) {
    cout << totalDemVotes << " Dem votes, won by: " << demWinnerName << " ";
    cout << setprecision(2) << demWinningPercent << endl;
    cout << totalRepVotes << " Rep votes, won by: " << repWinnerName << " ";
    cout << setprecision(2) << repWinningPercent << endl;
}
