/**
 * @file 8.8.3.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/20 16:13:38
 */

/*
  Write a function that takes a reference to a string object as its parameter and that con-
  verts the contents of the string to uppercase. Use the toupper() function described in
  Table 6.4. Write a program that uses a loop which allows you to test the function with
  different input. A sample run might look like this:

  Enter a string (q to quit): go away
  GO AWAY
  Next string (q to quit): good grief!
  GOOD GRIEF!
  Next string (q to quit): q
  Bye.
 */

#include <iostream>
#include <string>
#include <cctype>

void string2Upper(std::string &str)
{
    for (unsigned int i = 0; i < str.length(); i++) {
        str[i] = std::toupper(str[i]);
    }
}

int main(int argc, char *argv[])
{
    using namespace std;
    string str;

    cout << "Enter a string (q to quit): ";
    getline(cin, str);
    while (str != "q") {
        string2Upper(str);
        cout << str << endl;
        cout << "Next string (q to quit): ";
        getline(cin, str);
    }
    cout << "Bye" << endl;

    return 0;
}
