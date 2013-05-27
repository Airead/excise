/**
 * @file 9.6.2.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/21 22:34:08
 */

/*
  Redo Listing 9.9, replacing the character array with a string object. The program
  should no longer have to check whether the input string fits, and it can compare the
  input string to "" to check for an empty line.
 */

#include <iostream>
#include <string>

void strcount(const std::string str)
{
    using namespace std;
    static int total = 0;

    cout << "\"" << str <<"\" contains ";
    total += str.length();
    cout << str.length() << " characters\n";
    cout << total << " characters total\n";
}

int main()
{
    using namespace std;
    string input;

    cout << "Enter a line:\n";
    getline(cin, input);
    while (cin)
    {
        strcount(input);
        cout << "Enter next line (empty line to quit):\n";
        getline(cin, input);
        if (input == "") {
            break;
        }
    }
    cout << "Bye\n";
    return 0;
}
