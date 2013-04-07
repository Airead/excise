#include <iostream>

using namespace std;

void Mice(void);
void How(void);

int main(int argc, char *argv[])
{
    Mice();
    Mice();
    How();
    How();

    return 0;
}

void Mice(void) {
    cout << "Three blind mice" << endl;
}

void How(void) {
    cout << "See how they run" << endl;
}
