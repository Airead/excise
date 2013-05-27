#include <Magick++.h>
#include <iostream>
using namespace std;
using namespace Magick;
int main(int argc,char **argv)
{
    InitializeMagick(*argv);
    Image master("girl.gif");
    Image second = master;
    second.zoom("640x120");
    Image third = master;
    third.zoom("8000x4000");
    second.write("horse640x480.jpg");
    third.write("horse800x6000.jpg");
    return 0;
}
