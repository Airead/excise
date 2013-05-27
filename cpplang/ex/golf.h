/**
 * @file golf.h
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/21 22:00:49
 */

#ifndef _GOLF_H_
#define _GOLF_H_

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

#endif /* _GOLF_H_ */
