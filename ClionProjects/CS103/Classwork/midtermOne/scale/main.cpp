#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;
void read(const char filename[], int* n, double numbers[], string items[]);

int main(int argc, char* argv[]) {

    double numbers[100];
    string items[100];
    int numberOfObjects = 0;
    double scalar = atof(argv[1]);
    char* test = argv[2];


    read(test, &numberOfObjects, numbers, items);

    for (int i = 0; i < numberOfObjects; ++i) {
        numbers[i] *= scalar;
    }
    for (int i = 0; i < numberOfObjects; ++i) {
        cout << numbers[i] << " " << items[i] << endl;
    }

}

// open this file & read its contents into parallel arrays (numbers, items)
// write the number of items at the address where n points
void read(const char filename[], int* n, double numbers[], string items[]) {
    ifstream in_file;
    in_file.open(filename);

    if (!in_file.is_open()) {
        cout << "I fail" << endl;
    }

    int i = 0;
    while (!in_file.eof()) {
        in_file >> numbers[i];
        in_file >> items[i];
        i++;
    }
    *n = i;
}