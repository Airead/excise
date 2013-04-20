/**
 * @file 6.11.3.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/05 15:44:38
 */

/*
  Write a precursor to a menu-driven program. The program should display a menu offer-
  ing four choices, each labeled with a letter. If the user responds with a letter other than
  one of the four valid choices, the program should prompt the user to enter a valid
  response until the user complies. Then the program should use a switch to select a sim-
  ple action based on the user’s selection. A program run could look something like this:

  Please enter one of the following choices:
  c) carnivore           p) pianist
  t) tree                g) game
  f
  Please enter a c, p, t, or g: q
  Please enter a c, p, t, or g: t
  A maple is a tree;
 */

#include <iostream>

int main(int argc, char *argv[])
{
    using namespace std;
    
    char choice;
    const char *ret;

    cout << "Please enter one of the following choices: " << endl;
    cout << "c) carnivore           p) pianist" << endl;
    cout << "t) tree                g) game" << endl;

    while (cin >> choice) {
        if (choice == 'c' || choice == 'p' || choice == 't' || choice == 'g') {
            break;
        }
        cout << "Please enter a c, p, t, or g: ";
    }

    switch (choice) {
    case 'c':
        ret = "carnivore";
        break;
    case 'p':
        ret  = "pianist";
        break;
    case 't':
        ret = "tree";
        break;
    case 'g':
        ret = "game";
    }

    cout << "A maple is a " << ret << endl;

    return 0;
}
