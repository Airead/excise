/**
 * @file 5.9.9.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/04 21:13:52
 */

/*
  Write a program that matches the description of the program in Programming Exercise
  7, but use a string class object instead of an array. Include the string header file and
  use a relational operator to make the comparison test.
 */

#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    using namespace std;
    
    string word;
    
    int count;

    cout << "Enter words (to stop, type the word done):" << endl;

    cin >> word;
    count = 0;
    while (word != "done") {
        count++;
        cin >> word;
    }

    cout << "You entered a total of " << count << " words" << endl;

    return 0;
}
