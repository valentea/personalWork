#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int score(int ratings[], int numberOfJudges);

int globalIndex = 0;

int main(int argc, char* argv[]) {
    char* countryScores = argv[1];

    ifstream in_file;
    in_file.open(countryScores);

    if(!in_file.is_open()){
        cout << "i suck" << endl;
    }

    int numberOfCountries = 0;
    in_file >> numberOfCountries;
    int numberOfJudges = 0;
    in_file >> numberOfJudges;

    string countries[numberOfCountries];
    int scores[numberOfJudges];
    int average[numberOfCountries];

    for (int i = 0; i < numberOfCountries; ++i) {
        in_file >> countries[i];
        for (int j = 0; j < numberOfJudges; ++j) {
            in_file >> scores[j];
        }
        average[i] = score(scores, numberOfJudges);
    }

    cout << numberOfCountries << endl;
    for (int i = 0; i < numberOfCountries; ++i) {
        cout << countries[i] << "  " << average[i] << endl;
    }

    in_file.close();

    return 1;
}



//RETURN THE ROUNDED AVERAGE SCORE
int score(int ratings[], int numberOfJudges) {
    int minNumber = ratings[0];
    int minIndex = 0;

    int maxNumber = ratings[0];
    int maxInedx = 0;

    for (int i = 1; i < numberOfJudges; ++i) {
        if (minNumber > ratings[i]) {
            minNumber = ratings[i];
            minIndex = i;
        }
    }
    for (int i = 1; i < numberOfJudges; ++i) {
        if (maxNumber < ratings[i]) {
            maxNumber = ratings[i];
            maxInedx = i;
        }
    }

    if (maxInedx == minIndex) {
        maxInedx++;
    }

    double totalAverage = 0;
    for (int i = 0; i < numberOfJudges; ++i) {
        if (maxInedx != i && minIndex != i) {
            totalAverage += ratings[i];
        }
    }
    totalAverage = totalAverage / (numberOfJudges - 2);
    totalAverage = round(totalAverage);
    return int(totalAverage);
}