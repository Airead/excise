/**
 * @file 7.13.6.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/20 14:03:25
 */

/*
  Write a program that uses the following functions:

  Fill_array() takes as arguments the name of an array of double values and an array
  size. It prompts the user to enter double values to be entered in the array. It ceases tak-
  ing input when the array is full or when the user enters non-numeric input, and it
  returns the actual number of entries.

  Show_array() takes as arguments the name of an array of double values and an array
  size and displays the contents of the array.

  Reverse_array() takes as arguments the name of an array of double values and an
  array size and reverses the order of the values stored in the array.
  
  The program should use these functions to fill an array, show the array, reverse the array,
  show the array
 */

#include <iostream>

int fillArray(double *arr, int n)
{
    int i;
    
    for (i = 0; i < n; i++) {
        std::cout << "[" << i + 1 << "] input num: ";
        if ((std::cin >> arr[i]).fail()) {
            break;
        }
    }

    return i;
}

void showArray(double *arr, int n)
{
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void ReverseArray(double *arr, int n)
{
    for (int i = 0; i < n / 2; ++i) {
        int t;
        t = arr[i];
        arr[i] = arr[n - i - 1];
        arr[n - i - 1] = t;
    }
}

int main(int argc, char *argv[])
{
    const int Size = 10;
    double arr[Size];
    int n;

    n = fillArray(arr, Size);
    showArray(arr, n);
    ReverseArray(arr, n);
    showArray(arr, n);
    
    return 0;
}
