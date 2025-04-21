#include <iostream>
#include <string>
#include "StrF.h"
using namespace std;
int main() {
    std::string string1;
    std::cout << "in!:";
    std::cin >> string1;
    StrF str(string1);
    std::cout << "str1 = " << str.get_str() << endl;
    std::string string2;
    std::cout << "in!:\n";
    std::cin >> string2;
    StrF str2(string2);
    std::cout << "str2 = " << str2.get_str() << endl;
    str.plus(str2);
    std::cout << "plus str1=" << str.get_str() << endl;
    return 0;
    // 还可以更多！
}
