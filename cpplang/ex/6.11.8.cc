/**
 * @file 6.11.8.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/05 16:10:46
 */

/*
  Write a program that opens a text file, reads it character-by-character to the end of the
  file, and reports the number of characters in the file.
 */

#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
    using namespace std;

    ifstream inFile;
    string fname;
    char ch;
    int count;

    cout << "Enter file name: ";
    cin >> fname;

    inFile.open(fname);
    if (!inFile.is_open()) {
        cout << "Open file " << fname << " failed" << endl;
        exit(1);
    }

    count = 0;
    while (inFile.get(ch)) {
        count++;
    }

    cout << fname << " contains " << count << " chars." << endl;

    return 0;
}
