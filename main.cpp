#include <iostream>
#include <string>
#include "StrF.h"
using namespace std;
int main() {
    string string1;
    cout << "in!:";
    cin >> string1;
    StrF str(string1);
    cout << "str1 = " << str << endl;
    string string2;
    cout << "in!:\n";
    cin >> string2;
    StrF str2(string2);
    cout << "str2 = " << str2 << endl;
    str += str2;
    cout << "plus str1=" << str << endl;
    if (str >str2){cout << ">:" << "ture";}
    else {cout << ">:" << "false";}

    return 0;
    // 还可以更多！
}
