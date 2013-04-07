// format hours and minutes

#include <iostream>

int main(int argc, char *argv[])
{
    using namespace std;
    
    int hours, minutes;

    cout << "Enter the number of hours: ";
    cin >> hours;

    cout << "Enter the number of minutes: ";
    cin >> minutes;

    cout << "Time: " << hours << ":" << minutes << endl;
    
    return 0;
}
