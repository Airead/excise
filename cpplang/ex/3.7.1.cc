// 根据脚长（毫米）计算出欧码。该程序用下划线字符来指示输入位置。使用一个 const 符号常量来表示转换因子。
// 法码 = (脚长 / 10) * 2 - 10

#include <iostream>

const int diff = 10;

int main(int argc, char *argv[])
{
    using namespace std;

    int length, eur;

    cout << "Input the length of your foot:_____\b\b\b\b";
    cin >> length;

    eur = length / 10 * 2 - diff;

    cout << "the eur of your foot is " << eur << endl;

    return 0;
}
