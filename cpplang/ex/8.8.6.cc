/**
 * @file 8.8.6.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/20 19:26:42
 */

/*
  Write a template function maxn() that takes as its arguments an array of items of type T
  and an integer representing the number of elements in the array and that returns the
  largest item in the array. Test it in a program that uses the function template with an
  array of six int value and an array of four double values. The program should also
  include a specialization that takes an array of pointers-to-char as an argument and the
  number of pointers as a second argument and that returns the address of the longest
  string. If multiple strings are tied for having the longest length, the function should
  return the address of the first one tied for longest. Test the specialization with an array of
  five string pointers.
 */

#include <iostream>
#include <cstring>

using namespace std;

template <class T>
T maxn(T *a, int n);

template <> const char *maxn<const char*>(const char **strarr, int n)
{
    const char *pmax;

    cout << "specialization: " << endl;
    pmax = strarr[0];
    for (int i = 1; i < n; i++) {
        if (strlen(pmax) < strlen(strarr[i])) {
            pmax = strarr[i];
        }
    }

    return pmax;
}

void show(int *intarr, int n)
{
    cout << "int array: ";
    for (int i = 0; i < n; i++) {
        cout << intarr[i] << ", ";
    }
    cout << "largest is " << maxn(intarr, n) << endl;
}

void show(double *douarr, int n)
{
    cout << "double array: ";
    for (int i = 0; i < n; i++) {
        cout << douarr[i] << ", ";
    }
    cout << "largest is " << maxn(douarr, n) << endl;
}

void show(const char **strarr, int n)
{
    cout << "string array: ";
    for (int i = 0; i < n; i++) {
        cout << strarr[i] << ", ";
    }
    cout << "largest is " << maxn(strarr, n) << endl;
}


int main(int argc, char *argv[])
{
    int intarr[6] = {1, 6, 2, 5, 3, 4};
    double douarr[4] = {1.1, 5.5, 2.2, 3.3};
    const char *strarr[] = {
        "Airead",
        "Fan",
        "template example",
        "TEMPLATE EXAMPLE",
        "and other",
    };

    show(intarr, 6);
    show(douarr, 4);
    show(strarr, 5);

    return 0;
}

template <class T>
T maxn(T *a, int n)
{
    T max;

    max = a[0];
    for (int i = 1; i < n; i++) {
        if (max < a[i]) {
            max = a[i];
        }
    }

    return max;
}
