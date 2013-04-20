/**
 * @file 7.13.7.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/20 14:25:35
 */

/*
  Redo exercise 7.13.6, modifying the three array-handling functions
  to each use two pointer parameters to represent a range. The
  fill_array() function, instead of returning the actual number of
  items read, should return a pointer to the location after the last
  location filled; the other functions can use this pointer as the
  second argument to identify the end of the data.
 */

#include <iostream>

double *fillArray(double *start, double *end)
{
    double *p;
    
    for (p = start; p <= end; p++) {
        std::cout << "[" << (p - start) + 1 << "] input num: ";
        if ((std::cin >> *p).fail()) {
            break;
        }
    }

    return p - 1;
}

void showArray(double *start, double *end)
{
    double *p;
    
    for (p = start; p <= end; p++) {
        std::cout << *p << " ";
    }
    std::cout << std::endl;
}

void ReverseArray(double *start, double *end)
{
    double *p, *q;
    
    p = start;
    q = end;
    while (p < q) {
        int t;
        t = *p;
        *p = *q;
        *q = t;
        p++;
        q--;
    }
}

int main(int argc, char *argv[])
{
    const int Size = 10;
    double arr[Size];
    double *end;


    end = fillArray(arr, arr + Size - 1);
    showArray(arr, end);
    ReverseArray(arr, end);
    showArray(arr, end);
    
    return 0;
}
