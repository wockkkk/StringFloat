//
// Created by Administrator on 2025/4/21.
//

#ifndef STR_F_H
#define STR_F_H
#include <iostream>
#include <string>
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
    explicit StrF(const std::string& instr) {
        unsigned long long point = instr.find('.');
        str1 = instr.substr(0, point);
        str2 = instr.substr(point + 1, instr.length() - point - 1);
        del_zero();
    }
    std::string get_str() const {
        return str1 + "." + str2;
    }
    friend void operator+=(StrF str1 , StrF str2);
    friend StrF operator+(StrF str1 , StrF str2);
    friend std::ostream& operator<<(std::ostream& os, const StrF& str) {
        return os << str.get_str();
    }
    void del_zero();
    // 还可以更多！
};
inline void operator+=(StrF str1 , StrF str2){
    if (str1.str1.length() > str2.str1.length()) {
        for (; 0 != (str1.str1.length() - str2.str1.length()); str2.str1 = "0" + str2.str1) {
        }
    } else if (str1.str1.length() < str2.str1.length()) {
        for (; 0 != (str2.str1.length() -str1.str1.length());str1.str1 = "0" +str1.str1) {
        }
    }
    if (str1.str2.length() > str2.str2.length()) {
        for (; 0 != (str1.str2.length() - str2.str2.length()); str2.str2 += "0") {
        }
    } else if (str1.str2.length() < str2.str2.length()) {
        for (; 0 != (str2.str2.length() -str1.str2.length());str1.str2 += "0") {
        }
    }
    bool add = false;
    for (unsigned long long i =str1.str2.length(); i > 0; i--) {
        add = StrF::add(str1.str2[i - 1], str2.str2[i - 1], add);
    }
    for (unsigned long long i =str1.str1.length(); i > 0; i--) {
        add = StrF::add(str1.str1[i - 1], str2.str1[i - 1], add);
    }
    if (add) {
       str1.str1 = "1" +str1.str1;
    }
    str1.del_zero();
}
inline StrF operator+(const StrF &str1 , const StrF &str2){
    StrF temp = str1;
    temp += str2;
    return temp;
}
inline void StrF::del_zero() {
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
#endif // STR_F_H
