/**
 * @file 4.13.4.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/04 16:12:29
 */

/*
  Write a program that asks the user to enter his or her first name and then last name, and
  that then constructs, stores, and displays a third string consisting of the user’s last name
  followed by a comma, a space, and first name. Use **string** objects and methods from the
  **string** header file. A sample run could look like this:
  
  Enter your first name: Flip
  Enter your last name: Fleming
  Here’s the information in a single string: Fleming, Flip
*/

#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    using namespace std;

    string first, last, name;

    cout << "Enter your first name: ";
    getline(cin, first);
    cout << "Enter your last name: ";
    getline(cin, last);

    name = first + ", " +last;
    
    cout << "Here's the information in a single string: " << name << endl;

    return 0;
}
