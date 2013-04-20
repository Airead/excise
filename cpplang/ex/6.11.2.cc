/**
 * @file 6.11.2.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/05 15:29:53
 */

/*
  Write a program that reads up to 10 donation values into an array of double. The pro-
  gram should terminate input on non-numeric input. It should report the average of the
  numbers and also report how many numbers in the array are larger than the average.

 */

#include <iostream>

int main(int argc, char *argv[])
{
    using namespace std;
    
    const int Max = 10;
    
    int donation[Max];
    int tmp, count;
    int sum, aver, larger;
    
    cout << "Enter numbers (up to 10, and terminate by non-numeric input )" << endl;

    count = 0;
    while (count < Max && cin >> tmp) {
        donation[count] = tmp;
        count++;
    }

    sum = 0;
    for (int i = 0; i < count; i++) {
        sum += donation[i];
    }

    aver = sum / count;
    
    larger = 0;
    for (int i =0; i < count; i++) {
        if (donation[i] > aver) {
            larger++;
        }
    }

    cout << "average value is " << aver << 
        ", the number of larger is " << larger << ". " << endl;

    return 0;
}
