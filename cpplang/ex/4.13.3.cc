/**
 * @file 4.13.3.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/04 15:50:58
 */

/*
  Write a program that asks the user to enter his or her first name and then last name, and
  that then constructs, stores, and displays a third string, consisting of the user’s last name
  followed by a comma, a space, and first name. Use **char** arrays and functions from the
  **cstring** header file. A sample run could look like this:

  Enter your first name: Flip
  Enter your last name: Fleming
  Here’s the information in a single string: Fleming, Flip
 */

#include <iostream>
#include <cstring>

int main(int argc, char *argv[])
{
    using namespace std;

    const int ArSize = 20;
    char first[ArSize], last[ArSize];
    char name[ArSize * 2 + 2];
    
    cout << "Enter your first name: ";
    cin.getline(first, ArSize);
    cout << "Enter your last name: ";
    cin.getline(last, ArSize);

    strcpy(name, first);
    strcat(name, ", ");
    strcat(name, last);

    cout << "Here's the information in a single string: " << name << endl;

    return 0;
}
