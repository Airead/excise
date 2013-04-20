/**
 * @file 8.8.7.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/20 19:53:45
 */

/*
  Modify Listing 8.14 so that the template functions return the sum of the array contents
  instead of displaying the contents. The program now should report the total number of
  things and the sum of all the debts.
 */

#include <iostream>

template <typename T>
void SuArray(T arr[], int n); // template A

template <typename T> // template B
void SuArray(T * arr[], int n);

struct debts
{
    char name[50];
    double amount;
};

int main(void)
{
    using namespace std;
    int things[6] = {13, 31, 103, 301, 310, 130};
    struct debts mr_E[3] = {
            {"Ima Wolfe", 2400.0},
            {"Ura Foxe ", 1300.0},
            {"Iby Stout", 1800.0}
    };
    double * pd[3];

    // set pointers to the amount members of the structures in the arr mr_E
    for (int i = 0; i < 3; i++)
        pd[i] = &mr_E[i].amount;

    cout << "Listing Mr. E's counts of things:\n";
    // things is an array of int
    SuArray(things, 6); // uses template A
    cout << "Listing Mr. E's debts:\n";
    // pd is an array of pointers to double
    SuArray(pd, 3);     // uses template B (more specialized)
    return 0;
}

template <typename T>
void SuArray(T arr[], int n)
{
    using namespace std;
    T sum = 0;

    cout << "template A\n";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << ' ';
        sum += arr[i];
    }
    cout << ", sum: " << sum << endl;
}

template <typename T>
void SuArray(T * arr[], int n)
{
    using namespace std;
    T sum = 0;

    cout << "template B\n";
    for (int i = 0; i < n; i++) {
        cout << *arr[i] << ' ';
        sum += *arr[i];
    }
    cout << ", sum: " << sum << endl;
}
