/**
 * @file 8.8.4.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/20 17:09:04
 */

/*
  Complete this skeleton by providing the described functions and prototypes. Note that
  there should be two show() functions, each using default arguments. Use const argu-
  ments when appropriate. Note that set() should use new to allocate sufficient space to
  hold the designated string. The techniques used here are similar to those used in design-
  ing and implementing classes. (You might have to alter the header filenames and delete
  the using directive, depending on your compiler.)
*/

#if 0
The following is a program skeleton:

#include <iostream>
using namespace std;
#include <cstring>
struct stringy {
    char * str;
    int ct;
};
// for strlen(), strcpy()
// points to a string
// length of string (not counting ‘\0’)
// prototypes for set(), show(), and show() go here
int main()
{
    stringy beany;
    char testing[] = “Reality isn’t what it used to be.”;
    set(beany, testing);
// first argument is a reference,
// allocates space to hold copy of testing,
// sets str member of beany to point to the
// new block, copies testing to new block,
// and sets ct member of beany
    show(beany);
// prints member string once
    show(beany, 2);
// prints member string twice
    testing[0] = ‘D’;
    testing[1] = ‘u’;
    show(testing);
// prints testing string once
    show(testing, 3); // prints testing string thrice
    show(“Done!”);
    return 0;
}
#endif 

#include <iostream>
using namespace std;
#include <cstring> // for strlen(), strcpy()

struct stringy {
    char *str; // points to a string
    int ct; // length of string (not counting ‘\0’)
};
// prototypes for set(), show(), and show() go here
void set(stringy &s, const char *str)
{
    int len;
    char *tmp;

    len = strlen(str);
    tmp = new char[len + 1];
    strncpy(tmp, str, len);

    s.str = tmp;
    s.ct = len;
}

void show(const stringy &s, int n = 1)
{
    for (int i = 0; i < n; i++) {
        cout << s.str << endl;
    }
}

void show(const char *str, int n = 1)
{
    for (int i = 0; i < n; i++) {
        cout << str << endl;
    }
}

int main()
{
    stringy beany;
    char testing[] = "Reality isn’t what it used to be.";
    set(beany, testing);        /* first argument is a reference,
                                   allocates space to hold copy of testing,
                                   sets str member of beany to point to the
                                   new block, copies testing to new block,
                                   and sets ct member of beany
                                */
    show(beany);
    // prints member string once
    show("---------------------------------");
    show(beany, 2);
    // prints member string twice
    testing[0] = 'D';
    testing[1] = 'u';
    show("---------------------------------");
    show(testing);
    // prints testing string once
    show("---------------------------------");
    show(testing, 3); // prints testing string thrice
    show("---------------------------------");
    show("Done!");
    return 0;
}
