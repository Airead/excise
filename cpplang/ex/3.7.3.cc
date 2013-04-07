/**
 * @file 3.7.3.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/04 14:28:54
 */

/*
 * 编写一个程序，要求用户以度、分、秒的方式输入一个纬度，然后以度为单位
 * 显示该纬度。1度为60分，1分等于60秒，请以符号常量的方式表示这些值。对
 * 于每个输入值，应使用一个独立的变量存储它。
 *
 * Enter a latitude in degrees, minutes, and seconds:
 First, enter the degrees: 37
 Next, enter the minutes of arc: 51
 Finally, enter the seconds of arc: 19
 37 degrees, 51 minutes, 19 seconds = 37.8553 degrees
 
 */

#include <iostream>

const int SECOND = 1;
const int MINUTE = 60 * SECOND;
const int DEGREE = 60 * MINUTE;


int main(int argc, char *argv[])
{
    using namespace std;
    
    int second, minute, degree;

    cout << "Enter a latitude in degrees, mineutes, and seconds:" << endl;
    cout << "First, enter the degrees: ";
    cin >> degree;
    cout << "Next, enter the minutes of arc: ";
    cin >> minute;
    cout << "Finally, enter the seconds of arc: ";
    cin >> second;
    cout << degree << "degrees, " << minute << " minutes, " << second << " seconds = " 
         << degree + (1.0 * minute * MINUTE + second * SECOND) / DEGREE << " degrees" << endl;
    
    return 0;
}
