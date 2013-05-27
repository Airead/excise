/**
 * @file golf.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/21 22:02:54
 */

#include <iostream>
#include <cstring>
#include "golf.h"

// non-interactive version:
// function sets golf structure to provided name, handicap
// using values passed as arguments to the function
void setgolf(golf &g, const char * name, int hc)
{
    std::strncpy(g.fullname, name, Len);
    g.handicap = hc;
}

// interactive version:
// function solicits name and handicap from user
// and sets the members of g to the values entered
// returns 1 if name is entered, 0 if name is empty string
int setgolf(golf &g)
{
    using namespace std;

    cout << "golf name: ";
    cin.getline(g.fullname, Len);
    if (strlen(g.fullname) == 0) {
        return 0;
    }
    cout << " handicap: ";
    cin >> g.handicap;
    cin.get();

    return 1;
}

// function resets handicap to new value
void handicap(golf & g, int hc)
{
    g.handicap = hc;
}

// function displays contents of golf structure
void showgolf(const golf &g)
{
    std::cout << g.fullname << " " << g.handicap;
}
