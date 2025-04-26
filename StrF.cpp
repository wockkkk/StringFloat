#include "StrF.h"
void StrF::fill_zero(StrF &str1,StrF &str2) {
    if (str1.str1.length() > str2.str1.length()) {
        for (; 0 != (str1.str1.length() - str2.str1.length()); str2.str1 = "0" + str2.str1) {
        }
    } else if (str1.str1.length() < str2.str1.length()) {
        for (; 0 != (str2.str1.length() - str1.str1.length()); str1.str1 = "0" + str1.str1) {
        }
    }
    if (str1.str2.length() > str2.str2.length()) {
        for (; 0 != (str1.str2.length() - str2.str2.length()); str2.str2 += "0") {
        }
    } else if (str1.str2.length() < str2.str2.length()) {
        for (; 0 != (str2.str2.length() - str1.str2.length()); str1.str2 += "0") {
        }
    }
}
StrF operator+=(StrF &str1, StrF str2) {
    StrF::fill_zero(str1, str2);
    bool add = false;
    for (unsigned long long i = str1.str2.length(); i > 0; i--) {
        add = StrF::add(str1.str2[i - 1], str2.str2[i - 1], add);
    }
    for (unsigned long long i = str1.str1.length(); i > 0; i--) {
        add = StrF::add(str1.str1[i - 1], str2.str1[i - 1], add);
    }
    if (add) {
        str1.str1 = "1" + str1.str1;
    }
    str1.del_zero();
    return str1;
}
StrF operator+(const StrF &str1, const StrF &str2) {
    StrF temp = str1;
    temp += str2;
    return temp;
}
bool operator>(StrF str_a, StrF str){
    StrF::fill_zero(str_a,str);
    if (str_a.is_min && !str.is_min) {
        return false;
    }
    if (!str_a.is_min && str.is_min) {
        return true;
    }
    bool sign = str_a.is_min;
    bool return_value = false;
    if (str_a.str1.length() > str.str1.length()) {
        if (sign) {
            return_value = false;
        } else {
            return_value = true;
        }
        return return_value;
    }
    if (str_a.str1.length() < str.str1.length()) {
        if (sign) {
            return_value = true;
        } else {
            return_value = false;
        }
        return return_value;
    }
    for (unsigned long long i = str_a.str1.length(); i > 0; ++i) {
        if (str_a.str1[i - 1] > str.str1[i - 1]) {
            if (sign) {
                return_value = false;
            } else {
                return_value = true;
            }
            return return_value;
        }
        if (str_a.str1[i - 1] < str.str1[i - 1]) {
            if (sign) {
                return_value = true;
            } else {
                return_value = false;
            }
            return return_value;
        }
    }
    for (unsigned long long i = str_a.str2.length(); i > 0; ++i) {
        if (str_a.str2[i - 1] > str.str2[i - 1]) {
            if (sign) {
                return_value = false;
            } else {
                return_value = true;
            }
            return return_value;
        }
        if (str_a.str2[i - 1] < str.str2[i - 1]) {
            if (sign) {
                return_value = true;
            } else {
                return_value = false;
            }
            return return_value;
        }
    }
    return return_value;
}
bool StrF::operator== (const StrF& str) const {
    if (str1 == str.str1 && str2 == str.str2 && is_min == str.is_min) {
        return true;
    }
    return false;
}
bool StrF::operator<=(const StrF& str) const {
    return (*this < str || *this == str);
}
bool StrF::operator<(const StrF& str) const {
    if (*this == str) {
        return false;
    }
    return !(*this > str);
}
bool StrF::operator>=(const StrF& str) const {
    return (*this > str || *this == str);
}

bool StrF::operator!=(const StrF& str) const {
    return !(*this == str);
}
void StrF::del_zero() {
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
StrF::StrF(const std::string &instr) {
    if (instr[0] == '-') is_min = true;
    unsigned long long point = instr.find('.');
    str1 = instr.substr(0, point);
    str2 = instr.substr(point + 1, instr.length() - point - 1);
    del_zero();
}
