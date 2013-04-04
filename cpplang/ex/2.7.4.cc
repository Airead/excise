// show how many months in one's age

#include <iostream>

int MonthsInYears(int years) {
    return years * 12;
}

int main(int argc, char *argv[]) {
    using namespace std;

    int years;

    cout << "Enter your age: ";
    cin >> years;
    cout << "months: " << MonthsInYears(years) << endl;
    
    return 0;
}
