/**
 * @file main.h
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/11/30 15:03:17
 */

#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*action)(void);

struct person {
    char name[1987];
    action dowhat;
};

#endif /* _MAIN_H_ */
