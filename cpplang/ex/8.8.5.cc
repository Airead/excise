/**
 * @file 8.8.5.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/20 19:12:46
 */

/*
  Write a template function max5() that takes as its argument an array of five items of type
  T and returns the largest item in the array. (Because the size is fixed, it can be hard-coded
  into the loop instead of being passed as an argument.) Test it in a program that uses the
  function with an array of five int value and an array of five double values.
 */

#include <iostream>

using namespace std;

template <class T>
T max5(T *a);

void show(int *intarr)
{
    cout << "int array: ";
    for (int i = 0; i < 5; i++) {
        cout << intarr[i] << ", ";
    }
    cout << "largest is " << max5(intarr) << endl;
}


void show(double *douarr)
{
    cout << "double array: ";
    for (int i = 0; i < 5; i++) {
        cout << douarr[i] << ", ";
    }
    cout << "largest is " << max5(douarr) << endl;
}


int main(int argc, char *argv[])
{
    int intarr[5] = {1, 2, 5, 3, 4};
    double douarr[5] = {1.1, 5.5, 2.2, 3.3, 4.4};

    show(intarr);
    show(douarr);

    return 0;
}

template <class T>
T max5(T *a)
{
    T max;

    max = a[0];
    for (int i = 1; i < 5; i++) {
        if (max < a[i]) {
            max = a[i];
        }
    }

    return max;
}
