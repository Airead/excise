#include <iostream>

int L2Yard(int l);

int main(int argc, char *argv[]) {
    using namespace std;

    int l;

    cin >> l;
    cout << L2Yard(l) << endl;
    
    return 0;
}

int L2Yard(int l) {
    return l * 220;
}
