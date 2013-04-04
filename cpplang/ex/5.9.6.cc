/**
 * @file 5.9.6.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/04 20:36:42
 */

/*
  Do Programming Exercise 4, but use a two-dimensional array to store input for 3 years
  of monthly sales. Report the total sales for each individual year and for the combined
  years.
 */

#include <iostream>
#include <string>
#include <array>

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
    int sales[3][4];
    int yearSum, totalSum;

    totalSum = 0;
    for (int year = 2001; year <= 2003; year++) {
        yearSum = 0;
        cout << year << " data: " << endl;
        for (int month = 0; month < 4; month++) {
            cout << "    sales of " << months[month] << ": ";
            cin >> sales[year - 2001][month];
            yearSum += sales[year - 2001][month];
        }
        cout << year << " total sale " << yearSum << " books" << endl << endl;;
        totalSum += yearSum;
    }
    
    cout << "=================================" << endl;
    cout << "3 years total sale " << totalSum << " books" << endl;

    return 0;
}
