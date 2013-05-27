/**
 * @file 9.6.1.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/21 21:50:20
 */

/*
  1. Here is a header file:

  Note that setgolf() is overloaded. Using the first version of setgolf() would look like
  this:

  golf ann;
  setgolf(ann, “Ann Birdfree”, 24);

  The function call provides the information that’s stored in the ann structure. Using the
  second version of setgolf() would look like this:

  golf andy;
  setgolf(andy);

  The function would prompt the user to enter the name and handicap and store them in
  the andy structure. This function could (but doesn’t need to) use the first version inter-
  nally.
  Put together a multifile program based on this header. One file, named golf.cpp, should
  provide suitable function definitions to match the prototypes in the header file. A second
  file should contain main() and demonstrate all the features of the prototyped functions.
  For example, a loop should solicit input for an array of golf structures and terminate
  when the array is full or the user enters an empty string for the golfer’s name. The
  main() function should use only the prototyped functions to access the golf structures.
*/

#if 0
// golf.h -- for pe9-1.cpp
const int Len = 40;
struct golf
{
    char fullname[Len];
    int handicap;
};
// non-interactive version:
// function sets golf structure to provided name, handicap
// using values passed as arguments to the function
void setgolf(golf & g, const char * name, int hc);
// interactive version:
// function solicits name and handicap from user
// and sets the members of g to the values entered
// returns 1 if name is entered, 0 if name is empty string
int setgolf(golf & g);
// function resets handicap to new value
void handicap(golf & g, int hc);
// function displays contents of golf structure
void showgolf(const golf & g);

#endif

#include <iostream>

#include "golf.h"

int main(int argc, char *argv[])
{
    const int Size = 3;
    golf golfs[Size];
    int num = 0;

    setgolf(golfs[0], "Ann Birdfree", 24);
    num++;

    for (int i = 1; i < Size; i++) {
        /* int ret;
         * ret = setgolf(golfs[i]);
         * if (ret == 0) { */
        if (setgolf(golfs[i]) == 0) {
            break;
        }
        num++;
    }

    std::cout << "\n=================================\n";
    for (int i = 0; i < num; i++) {
        showgolf(golfs[i]);
        std::cout << std::endl;
    }
    std::cout << "\n=================================\n";

    handicap(golfs[0], 48);

    for (int i = 0; i < num; i++) {
        showgolf(golfs[i]);
        std::cout << std::endl;
    }
    std::cout << std::endl;

    return 0;
}

