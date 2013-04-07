/**
 * @file 5.9.1.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/04 19:45:53
 */

/*
  Write a program that requests the user to enter two integers. The program should then
  calculate and report the sum of all the integers between and including the two integers.
  At this point, assume that the smaller integer is entered first. For example, if the user
  enters 2 and 9, the program should report that the sum of all the integers from 2 through
  9 is 44.
 */

#include <iostream>

int main(int argc, char *argv[])
{
    using namespace std;

    int start, end, sum;

    cout << "Enter start number: ";
    cin >> start;
    cout << "Enter end number: ";
    cin >> end;

    sum = 0;
    for (int i = start; i <= end; i++) {
        sum += i;
    }

    cout << "the sum from " << start << " to " << end 
         << " is " << sum << "." << endl;

    return 0;
}
