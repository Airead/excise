/**
 * @file 4.13.1.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/04 15:14:46
 */

/*
  Write a C++ program that requests and displays information as shown in the following
  example of output:

  What is your first name? Betty Sue
  What is your last name? Yew
  What letter grade do you deserve? B
  What is your age? 22
  Name: Yew, Betty Sue
  Grade: C
  Age: 22
*/

#include <iostream>
#include <cstring>

int main(int argc, char *argv[])
{
    using namespace std;

    const int ArSize = 20;
    char name_first[ArSize], name_last[ArSize];
    char grade;
    int age;

    cout << "What is your first name? ";
    cin.getline(name_first, 20);
    cout << "What is your last name? ";
    cin.getline(name_last, 20);
    cout << "What letter grade do you deserve? ";
    cin >> grade;
    cout << "What is your age? ";
    cin >> age;

    cout << "Name: " << name_last << ", " << name_first << endl;
    cout << "Grade: " << char(grade + 1) << endl;
    cout << "Age: " << age << endl;

    return 0;
}
