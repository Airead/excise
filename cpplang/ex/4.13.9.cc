/**
 * @file 4.13.9.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/04 17:04:04
 */

/*
  Do Programming Exercise 6, but, instead of declaring an array of
  three CandyBar structures, use new to allocate the array
  dynamically.
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
    CandyBar *snack = new CandyBar[3];

    /* {"Mocha Munch", 2.3, 350},
     * {"Dove", 5.5, 430},
     * {"Henri Nestlé", 3.8, 380}, */

    snack[0].name = "Mocha Munch";
    snack[0].weight = 2.3;
    snack[0].calories = 350;

    snack[1].name = "Dove";
    snack[1].weight = 5.5;
    snack[1].calories = 430;
    
    snack[2].name = "Henri Nestlé";
    snack[2].weight = 3.8;
    snack[2].calories = 380;

    for (i = 0; i < 3; i++) {
        cout << "snack[" << i << "]:" << endl;
        cout << "  Name: " << snack[i].name << endl;
        cout << "  Weight: " << snack[i].weight << endl;
        cout << "  Calories: " << snack[i].calories << endl;
    }

    return 0;
}
