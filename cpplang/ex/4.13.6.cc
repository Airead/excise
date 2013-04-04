/**
 * @file 4.13.6.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/04 16:39:02
 */

/*
  The CandyBar structure contains three members, as described in
  Programming Exercise 5. Write a program that creates an array of
  three CandyBar structures, initializes them to values of your
  choice, and then displays the contents of each structure.
 */

#include <iostream>

struct CandyBar {
    std::string name;
    float weight;
    int calories;
};

int main(int argc, char *argv[])
{
    using namespace std;

    int i;
    CandyBar snack[3] = {
        {"Mocha Munch", 2.3, 350},
        {"Dove", 5.5, 430},
        {"Henri Nestlé", 3.8, 380},
    };

    for (i = 0; i < 3; i++) {
        cout << "snack[" << i << "]:" << endl;
        cout << "  Name: " << snack[i].name << endl;
        cout << "  Weight: " << snack[i].weight << endl;
        cout << "  Calories: " << snack[i].calories << endl;
    }

    return 0;
}
