/**
 * @file 8.8.2.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/20 16:02:25
 */

/*
  The CandyBar structure contains three members. The first member holds the brand
  name of a candy bar. The second member holds the weight (which may have a fractional
  part) of the candy bar, and the third member holds the number of calories (an integer
  value) in the candy bar. Write a program that uses a function that takes as arguments a
  reference to CandyBar, a pointer-to-char, a double, and an int and uses the last three
  values to set the corresponding members of the structure. The last three arguments
  should have default values of “Millennium Munch,” 2.85, and 350. Also, the program
  should use a function that takes a reference to a CandyBar as an argument and displays
  the contents of the structure. Use const where appropriate.
*/

#include <iostream>

struct CandyBar {
    std::string brand;
    float weight;
    int calories;
};

void setMember(CandyBar &cb, const char *brand = "Millennium Munch", 
               float weight = 2.85, float calories = 350);
void display(const CandyBar &cb);

int main(int argc, char *argv[])
{
    CandyBar cb;

    setMember(cb);
    display(cb);
    setMember(cb, "Airead Fan");
    display(cb);

    return 0;
}

void setMember(CandyBar &cb, const char *brand, float weight, float calories)
{
    cb.brand = brand;
    cb.weight = weight;
    cb.calories = weight;
}

void display(const CandyBar &cb)
{
    std::cout << cb.brand << " " << cb.weight << " " << cb.calories << std::endl;
}
