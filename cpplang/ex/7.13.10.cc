/**
 * @file 7.13.10.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/20 15:15:21
 */

/*
  Design a function calculate() that takes two type double values and a pointer to a
  function that takes two double arguments and returns a double. The calculate() func-
  tion should also be type double, and it should return the value that the pointed-to func-
  tion calculates, using the double arguments to calculate(). For example, suppose you
  have this definition for the add() function:
  double add(double x, double y)
  {
  return x + y;
  }
  Then, the function call in
  double q = calculate(2.5, 10.4, add);
  would cause calculate() to pass the values 2.5 and 10.4 to the add() function and
  then return the add() return value (12.9).
  Use these functions and at least one additional function in the add() mold in a program.
  The program should use a loop that allows the user to enter pairs of numbers. For each
  pair, use calculate() to invoke add() and at least one other function. If you are feeling
  adventurous, try creating an array of pointers to add()-style functions and use a loop to
  successively apply calculate() to a series of functions by using these pointers. Hint:
  Here’s how to declare such an array of three pointers:
  double (*pf[3])(double, double);
  You can initialize such an array by using the usual array initialization syntax and func-
  tion names as addresses.
 */

#include <iostream>

typedef double (*action)(double, double);

double add(double x, double y)
{
    return x + y;
}

double sub(double x, double y)
{
    return x - y;
}

double muli(double x, double y)
{
    return x * y;
}

double div(double x, double y)
{
    return x / y;
}

double calculate(double x, double y, action act)
{
    return act(x, y);
}

int main(int argc, char *argv[])
{
    using namespace std;
    action acts[] = {
        add, sub, muli, div
    };
    const char *names[] = {
        "add", "sub", "muli", "div"
    };
    int i = 0;
    int total = sizeof(acts) / sizeof(acts[1]);

    while (1) {
        double x, y;
        cout << names[i] << " two numbers: ";
        cin >> x >> y;
        if (cin.fail()) {
            break;
        }
        cout << names[i] << " " << x << ", " << y << " is "
             << calculate(x, y, acts[i]) << endl;
        i = (i + 1) % total;
    }

    return 0;
}
