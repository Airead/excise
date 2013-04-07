/**
 * @file 4.13.8.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/04 16:59:23
 */

/*
  Do Programming Exercise 7, but use **new** to allocate a structure instead of declaring a
  structure variable. Also, have the program request the pizza diameter before it requests
  the pizza company name.
 */

#include <iostream>
#include <string>

struct Pizza {
    std::string company;
    float diameter;
    float weight;
};

int main(int argc, char *argv[])
{
    using namespace std;

    Pizza *pi = new Pizza;

    cout << "Enter company name: ";
    getline(cin, pi->company);
    cout << "Enter diameter of pizza: ";
    cin >> pi->diameter;
    cout << "Enter weight of pizza: ";
    cin >> pi->weight;

    cout << pi->company << ", " << pi->diameter << ", " << pi->weight << endl;

    return 0;
}
