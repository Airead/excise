/**
 * @file 8.8.1.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/20 15:41:29
 */

/*
  Write a function that normally takes one argument, the address of a string, and prints
  that string once. However, if a second, type int, argument is provided and is nonzero,
  the function should print the string a number of times equal to the number of times that
  function has been called at that point. (Note that the number of times the string is
  printed is not equal to the value of the second argument; it is equal to the number of
  times the function has been called.) Yes, this is a silly function, but it makes you use
  some of the techniques discussed in this chapter. Use the function in a simple program
  that demonstrates how the function works.
 */

#include <iostream>

void silly_print(const char *str, int flag = 0)
{
    using namespace std;
    static int call_times = 0;

    call_times++;

    cout << "---------------------------------\n";
    cout << "silly_print(\"" << str << "\", " << flag << ")" << endl;
    if (flag > 0) {
        for (int i = 0; i < call_times; i++) {
            cout << "[" << i + 1 << "] " << str << endl;
        }
    } else {
        cout << "[1] " <<  str << endl;
    }
}

int main(int argc, char *argv[])
{
    silly_print("1");
    silly_print("2");
    silly_print("3", 10);
    silly_print("4");
    silly_print("5", 1);
    return 0;
}
