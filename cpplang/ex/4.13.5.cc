/**
 * @file 4.13.5.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/04 16:33:39
 */

/*
  The CandyBar structure contains three members. The first member holds the brand
  name of a candy bar. The second member holds the weight (which may have a fractional
  part) of the candy bar, and the third member holds the number of calories (an integer
  value) in the candy bar. Write a program that declares such a structure and creates a
  CandyBar variable called snack, initializing its members to “Mocha Munch”, 2.3, and
  350, respectively. The initialization should be part of the declaration for snack. Finally,
  the program should display the contents of the snack variable.
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
    
    CandyBar snack = {
        "Mocha Munch", 2.3, 350
    };

    cout << "snack" << endl;
    cout << "  Name: " << snack.name << endl;
    cout << "  Weight: " << snack.weight << endl;
    cout << "  Calories: " << snack.calories << endl;

    return 0;
}
