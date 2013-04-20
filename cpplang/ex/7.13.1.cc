/**
 * @file 7.13.1.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/20 10:20:28
 */

/*
 * Write a program that repeatedly asks the user to enter pairs of
 * numbers until at least one of the pair is 0. For each pair, the
 * program should use a function to calculate the harmonic mean of
 * the numbers. The function should return the answer to main(), which
 * should report the result. The harmonic mean of the numbers is the
 * inverse of the average of the inverses and can be calculated as
 * follows:
 * 
 * harmonic mean = 2.0 × x × y / (x + y)
 */

#include <iostream>

float harmonicMean(float x, float y)
{
    float mean;

    mean = 2.0 * x * y / (x + y);

    return mean;
}

int main(int argc, char *argv[])
{
    using namespace std;
    
    float x, y;
    
    cout << "Enter two num: ";
    cin >> x >> y;
    while (!cin.fail() && x != 0 && y != 0) {
        float harmean;

        harmean = harmonicMean(x, y);
        cout << "the harmonic mean of " << x << " and " << y
             << " is " << harmean << endl;
        cout << "Enter two num: ";
        cin >> x >> y;
    }
    
    cout << "Over" << endl;

    return 0;
}
