/**
 * @file 5.9.3.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/04 19:52:47
 */

/*
  Write a program that asks the user to type in numbers. After each entry, the program
  should report the cumulative sum of the entries to date. The program should terminate
  when the user enters 0.
 */

#include <iostream>

int main(int argc, char *argv[])
{
    using namespace std;
    
    int num, sum;

    sum = 0;

    cin >> num;
    while (num != 0) {
        sum += num;
        cout << "sum is " << sum << endl;
        cin >> num;
    }

    return 0;
}
