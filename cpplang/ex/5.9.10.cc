/**
 * @file 5.9.10.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/04 21:16:40
 */

/*
  Write a program using nested loops that asks the user to enter a value for the number of
  rows to display. It should then display that many rows of asterisks, with one asterisk in
  the first row, two in the second row, and so on. For each row, the asterisks are preceded
  by the number of periods needed to make all the rows display a total number of charac-
  ters equal to the number of rows. A sample run would look like this:

  Enter number of rows: 5
  ....*
  ...**
  ..***
  .****
  *****

 */

#include <iostream>

int main(int argc, char *argv[])
{
    using namespace std;

    int row;

    cout << "Enter number of rows: ";
    cin >> row;

    for (int i = 0; i < row; i++) {
        int j;
        for (j = 0; j < row - i - 1; j++) {
            cout << ".";
        }
        for (; j < row; j++) {
            cout << "*";
        }
        cout << endl;
    }

    return 0;
}
