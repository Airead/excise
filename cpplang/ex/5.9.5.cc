/**
 * @file 5.9.5.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/04 20:15:46
 */

/*
  You sell the book C++ for Fools. Write a program that has you enter a year’s worth of
  monthly sales (in terms of number of books, not of money). The program should use a
  loop to prompt you by month, using an array of char * (or an array of string objects, if
  you prefer) initialized to the month strings and storing the input data in an array of int.
  Then, the program should find the sum of the array contents and report the total sales
  for the year.
 */

#include <iostream>
#include <string>
#include <array>

#if 0
一月：January 二月：February 
三月：March 四月：April 
五月：May 六月：June 
七月：July 八月：August 
九月：September 十月：October 
十一月：November 十二月：December 
#endif
int main(int argc, char *argv[])
{
    using namespace std;

    array<string, 12> months = {
        {
            "January", "February", "March", "April",
            "May", "June", "July", "August",
            "September", "October", "November", "December",
        }
    };
    array<int, 12> sales;
    int sum = 0;

    for (int i = 0; i < 12; i++) {
        cout << "Enter sales number of " << months[i] << ": ";
        cin >> sales[i];
    }

    for (int i = 0; i < 12; i++) {
        sum += sales[i];
    }

    cout << "total sales " << sum << " books" << endl;
    
    return 0;
}
