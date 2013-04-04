/**
 * @file 4.13.2.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/04 15:39:28
 */

// Rewrite Listing 4.4, using the C++ string class instead of char arrays.

#if 0
// listing 4.4 

//instr2.cpp -- reading more than one word with getline
#include <iostream>
int main()
{
    using namespace std;
    const int ArSize = 20;
    char name[ArSize];
    char dessert[ArSize];
    cout << “Enter your name:\n”;
    cin.getline(name, ArSize); // reads through newline
    cout << “Enter your favorite dessert:\n”;
    cin.getline(dessert, ArSize);
    cout << “I have some delicious “ << dessert;
    cout << “ for you, “ << name << “.\n”;
    return 0;
}

Enter your name:
Dirk Hammernose
Enter your favorite dessert:
Radish Torte
I have some delicious Radish Torte for you, Dirk Hammernose.

#endif

#include <iostream>

int main(int argc, char *argv[])
{
    using namespace std;

    string name, dessert;

    cout << "Enter your name:\n";
    getline(cin, name);
    cout << "Enter your favorite dessert:\n";
    getline(cin, dessert);
    cout << "I ave some delicious " << dessert;
    cout << " for you, " << name << ".\n";

    return 0;
}
