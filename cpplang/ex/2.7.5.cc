// get degrees Fahrenheit from degrees Celsius

#include <iostream>

int CelSius2Fahrenheit(int celsius) {
    return 1.8 * celsius + 32;
}

int main(int argc, char *argv[]) {
    using namespace std;

    int celsius, fahrenheit;

    cout << "Please enter a Celsius value: ";
    cin >> celsius;

    fahrenheit = CelSius2Fahrenheit(celsius);

    cout << celsius << " degrees Celsius is " << fahrenheit <<  " degrees Fahrenheit" << endl;

    return 0;
}
