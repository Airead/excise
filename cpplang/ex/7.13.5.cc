/**
 * @file 7.13.5.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/20 13:50:26
 */

/*
 * Define a recursive function that takes an integer argument and
 * returns the factorial of that argument. Recall that 3 factorial,
 * written 3!, equals 3 × 2!, and so on, with 0!  defined as 1. In
 * general, if n is greater than zero, n! = n * (n – 1)!. Test your
 * function in a program that uses a loop to allow the user to enter
 * various values for which the program reports the factorial.
 */

#include <iostream>

int factorial(int n)
{
    if (n == 0 || n == 1) {
        return 1;
    }
    
    return n * factorial(n - 1);
}

int main(int argc, char *argv[])
{
    using namespace std;

    int num;
    
    cout << "Enter one num: ";
    while (cin >> num) {
        cout << num << " factorial is " << factorial(num) << endl;
        cout << "---------------------------------" << endl;
        cout << "Enter one num: ";
    }
    return 0;
}
