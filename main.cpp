#include <iostream>
#include <string>
using namespace std;
static constexpr char NUM_LIST[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
class StrF {
    static short get_num(char a) {
        char num_char = NUM_LIST[0];
        for (short i = 0; i < 10; i++) {
            if (num_char == a) {
                return i;
            }
            num_char = NUM_LIST[i + 1];
        }
        return -1;
    }
    static char put_num(short a) { return NUM_LIST[a]; }
    static bool add(char &a, char b, bool plus_bit) {
        bool bit = false;
        short a_num = get_num(a), b_num = get_num(b), plus_num = short(a_num + b_num + plus_bit);
        if (plus_num >= 10) {
            plus_num -= 10;
            bit = true;
        }
        a = put_num(plus_num);
        return bit;
    }


public:
    std::string str1;
    std::string str2;
    explicit StrF(const string &instr) {
        unsigned long long point = instr.find('.');
        str1 = instr.substr(0, point);
        str2 = instr.substr(point + 1, instr.length() - point - 1);
    }

    std::string get_str() const { return str1 + "." + str2; }

    void plus(StrF str) {
        if (str1.length() > str.str1.length()) {
            for (; 0 != (str1.length() - str.str1.length()); str.str1 = "0" + str1) {
            }
        } else if (str1.length() < str.str1.length()) {
            for (; 0 != (str.str1.length() - str1.length()); str1 = "0" + str.str1) {
            }
        }
        if (str2.length() > str.str2.length()) {
            for (; 0 != (str2.length() - str.str2.length()); str.str2 += "0") {
            }
        } else if (str2.length() < str.str2.length()) {
            for (; 0 != (str.str2.length() - str2.length()); str2 += "0") {
            }
        }
        bool add = false;
        for (unsigned long long i = str2.length(); i > 0; i--) {
            add = StrF::add(str2[i - 1], str.str2[i - 1], add);
        }
        for (unsigned long long i = str1.length(); i > 0; i--) {
            add = StrF::add(str1[i - 1], str.str1[i - 1], add);
        }
        if (add) {
            str1 = "1" + str1;
        }
        unsigned long long temp = str1.length();
        for (int i = 0; i < temp; ++i) {
            if (str1[i] == '0') {
                str1.erase(i, 1);
            } else {
                break;
            }
        }
        for (unsigned long long i = str2.length(); i != 0; --i) {
            if (str2[i - 1] == '0') {
                str2.erase(i - 1, 1);
            } else {
                break;
            }
        }
    }
    // 还可以更多！
};

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
