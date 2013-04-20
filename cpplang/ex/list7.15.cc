//arrobj.cpp -- funcions with array objects (C++11)

/*
  Enter Spring expenses: 212
  Enter Summer expenses: 256
  Enter Fall expenses: 208
  Enter Winter expenses: 244

  EXPENSES
  Spring: $212
  Summer: $256
  Fall: $208
  Winter: $244
  Total Expenses: $920
 */

#include <iostream>
#include <array>
#include <string>

// constant data
const int Seasons = 4;
const std::array<std::string, Seasons> Snames = {
    {"Spring", "Summer", "Fall", "Winter"}
};

//function to modity array object
void fill(std::array<double, Seasons> *pa);
// function that uses array object without modifying it
void show(std::array<double, Seasons> da);

int main(int argc, char *argv[])
{
    std::array<double, Seasons> expenses;

    fill(&expenses);
    show(expenses);

    return 0;
}

void fill(std::array<double, Seasons> *pa)
{
    using namespace std;

    for (int i = 0; i < Seasons; i++) {
        cout << "Enter " << Snames[i] << " expenses: ";
        cin >> (*pa)[i];
    }
}

void show(std::array<double, Seasons> da)
{
    using namespace std;
    double total = 0.0;
    cout << "\nEXPENSES\n";
    for (int i = 0; i < Seasons; i++) {
        cout << Snames[i] << ": $" << da[i] << endl;
        total += da[i];
    }
    cout << "Total Expenses: $" << total << endl;
}
