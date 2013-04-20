/**
 * @file 7.13.3.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/20 11:07:39
 */

/*
 * Here is a structure declaration:
 * struct box
 * {
 *     char maker[40];
 *     float height;
 *     float width;
 *     float length;
 *     float volume;
 * };
 * a. Write a function that passes a box structure by value and that displays the value of
 * each member.
 * b. Write a function that passes the address of a box structure and that sets the volume
 * member to the product of the other three dimensions.
 * c. Write a simple program that uses these two functions.
 */

#include <iostream>

struct box
{
    char maker[40];
    float height;
    float width;
    float length;
    float volume;
};

void setVolume(box *b)
{
    b->volume = b->height * b->width * b->length;
}

void displayBox(box b)
{
    std::cout << "box's: " << std::endl;
    std::cout << "  - maker: " << b.maker << std::endl;
    std::cout << "  - height: " << b.height << std::endl;
    std::cout << "  - width: " << b.width << std::endl;
    std::cout << "  - length: " << b.length << std::endl;
    std::cout << "  - volume: " << b.volume << std::endl;
}

int main(int argc, char *argv[])
{
    box b = {
        "Airead Fan", 16.9, 3.3, 270,
    };

    setVolume(&b);
    displayBox(b);

    return 0;
}
