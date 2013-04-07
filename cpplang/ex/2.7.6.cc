// get astronomical units from the number of light years

#include <iostream>

double LigthYear2AstronomicalUnit(double year) {
    return 63240 * year;
}

int main(int argc, char *argv[])
{
    using namespace std;

    double years, astr;

    cout << "Enter the number of light years: ";
    cin >> years;

    astr = LigthYear2AstronomicalUnit(years);

    cout << years << " light years = " << astr << " asronomical units" << endl;
    
    return 0;
}
