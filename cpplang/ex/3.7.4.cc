/**
 * @file 3.7.4.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/04 14:53:30
 */

/*
  Write a program that asks the user to enter the number of seconds
  as an integer value (use type long) and that then displays the
  equivalent time in days, hours, minutes, and seconds. Use symbolic
  constants to represent the number of hours in the day, the number of
  minutes in an hour, and the number of seconds in a minute. The output
  should
  
  look like this:
  Enter the number of seconds: 31600000
  31600000 seconds = 365 days, 46 minutes, 40 seconds
 */

#include <iostream>

const int MINUTE = 60;
const int HOUR = 60 * MINUTE;
const int DAY = 24 * HOUR;

int main(int argc, char *argv[])
{
    using namespace std;

    long num;
    int day, hour, minute, second;

    cout << "Enter the number of seconds: ";
    cin >> num;

    day = num / DAY;
    num %= DAY;

    hour = num / HOUR;
    num %= HOUR;

    minute = num / MINUTE;
    num %= MINUTE;

    second = num;

    cout << second << " seconds = " << day << " days, " << hour << " hour, "
         << minute << " minutes, " << second << " seconds" << endl;

    return 0;
}
