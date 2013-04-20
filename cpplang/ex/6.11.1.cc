/**
 * @file 6.11.1.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/05 15:06:20
 */

/*
  Write a program that reads keyboard input to the @ symbol and that echoes the input
  except for digits, converting each uppercase character to lowercase, and vice versa.
  (Don’t forget the cctype family.)

  Enter string:
  Hello My Name Is A1read Fa8. My Em1l I5 Fgh1987168@Gmail.Com
  hello my name is aread fa. my eml i fgh
 */

#include <iostream>
#include <cctype>

int main(int argc, char *argv[])
{
    using namespace std;

    char ch;

    cout << "Enter string:" << endl;

    cin.get(ch);
    while (ch != '@') {
        if (!isdigit(ch)) {
            cout << char(tolower(ch));
        }
        cin.get(ch);
    }
    cout << endl;

    return 0;
}

