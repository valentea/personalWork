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
    int x; //what the degree in radians we will be calculating is

    // Prompt the user
    cout << "Enter x in radians:  ";

    // get input


    // Do some operations


    // Print the result to the user


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
