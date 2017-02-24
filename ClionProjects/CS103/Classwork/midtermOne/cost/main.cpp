#include <iostream>
#include <fstream>

using namespace std;
void read(const char filename[], int* n, double numbers[], string items[]);

int main(int argc, char* argv[]) {

    double recipeAmount[100];
    string recipeItems[100];
    double storePrice[100];
    string storeItems[100];
    int numberOfObjectsRecipe = 0;
    int numberOfObjectsStore = 0;
    char* recipe = argv[1];
    char* store = argv[2];


        //argv[1] WILL ALWAYS BE THE RECIPE
    read(recipe, &numberOfObjectsRecipe, recipeAmount, recipeItems);
    read(store, &numberOfObjectsStore, storePrice, storeItems);

    double totalCost = 0;
    for (int i = 0; i < numberOfObjectsRecipe; ++i) {
        for (int j = 0; j < numberOfObjectsStore; ++j) {
            if (recipeItems[i] == storeItems[j]) {
                totalCost += storePrice[j]*recipeAmount[i];
            }
        }
    }
    cout << totalCost << endl;
}

void read(const char filename[], int* n, double numbers[], string items[]) {
    ifstream in_file;
    in_file.open(filename);
    if (!in_file.is_open()) {
        cout << "I fail" << endl;
    }
    int i = 0;;
    while (!in_file.eof()) {
        in_file >> numbers[i];
        in_file >> items[i];
        i++;
    }
    *n = i;
    in_file.close();
}