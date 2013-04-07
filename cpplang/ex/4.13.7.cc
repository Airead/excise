/**
 * @file 4.13.7.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/04 16:52:02
 */

/*
  William Wingate runs a pizza-analysis service. For each pizza, he needs to record the fol-
  lowing information:
  • The name of the pizza company, which can consist of more than one word
  • The diameter of the pizza
  • The weight of the pizza
  Devise a structure that can hold this information and write a program that uses a struc-
  ture variable of that type. The program should ask the user to enter each of the preced-
  ing items of information, and then the program should display that information. Use cin
  (or its methods) and cout.

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

    Pizza pi;

    cout << "Enter company name: ";
    getline(cin, pi.company);
    cout << "Enter diameter of pizza: ";
    cin >> pi.diameter;
    cout << "Enter weight of pizza: ";
    cin >> pi.weight;

    cout << pi.company << ", " << pi.diameter << ", " << pi.weight << endl;
        
    return 0;
}
