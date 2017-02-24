#include <iostream>
#include <cmath>

/* Alex Valente
 * Program: compute_sin
 * Description: Reads a number x from input, an angle in radians.
 *    Computes an approximation to sin(x) using an 8th-order Taylor series.
 */

using namespace std;

int fact(int); // declares a function the skeleton defines for you.

int main(int argc, char *argv[])
{
    // Declare any variables you need here
    double UserInputX;
    double FinalTaylorResult;

    // Prompt the user
    cout << "Enter x in radians:  ";

    // get input
    cin >> UserInputX;


    // Do some operations

        for (int i = 1; i <= 4; ++i) {
            int segment = i * 2 - 1;
            double PartOfTaylor = pow(UserInputX, segment) / fact(segment);
            if (i % 2 == 0) {
                    FinalTaylorResult -= PartOfTaylor;
            }
            else {
                FinalTaylorResult += PartOfTaylor;
            }

        }



    // Print the result to the user
    cout << "The Taylor Series result for Sin(" << UserInputX << ") is " << FinalTaylorResult << endl;


    // You're done
    return 0;
}

// here's the actual definition of fact, declared earlier.
int fact(int n)
{
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result = result * i;
    }
    return result;
}