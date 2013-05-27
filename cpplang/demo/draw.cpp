#include <Magick++.h>
using namespace std;
using namespace Magick;
int main(int argc,char **argv)
{
    InitializeMagick(*argv);
    Image image( "100x100", "white" );
    image.pixelColor( 49, 49, "red" );
    image.write( "red_pixel.png" );
    return 0;
}
