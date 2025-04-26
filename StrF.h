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
        short a_num = get_num(a), b_num = get_num(b), plus_num = static_cast<short>(a_num + b_num + plus_bit);
        if (plus_num >= 10) {
            plus_num -= 10;
            bit = true;
        }
        a = put_num(plus_num);
        return bit;
    }
    void del_zero();
    static void fill_zero(StrF&, StrF&);
    std::string str1;
    std::string str2;
    bool is_min = false;

public:
    explicit StrF(const std::string &instr);
    std::string get_str() const { return str1 + "." + str2; }
    friend StrF operator+=(StrF &str1, StrF str2);
    friend StrF operator+(StrF str1, StrF str2);
    friend std::ostream &operator<<(std::ostream &os, const StrF &str) { return os << str.get_str(); }
    friend bool operator>(StrF str_a, StrF str);
    bool operator==(const StrF &str) const;
    bool operator<(const StrF &str) const;
    bool operator>=(const StrF &str) const;
    bool operator<=(const StrF &str) const;
    bool operator!=(const StrF &str) const;

    // more!
};
#endif // STR_F_H
