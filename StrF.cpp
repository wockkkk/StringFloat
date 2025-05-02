#include "StrF.h"
void StrF::fill_zero(StrF &str1, StrF &str2) {
    if (str1.str_i.length() > str2.str_i.length()) {
        for (; 0 != (str1.str_i.length() - str2.str_i.length()); str2.str_i = "0" + str2.str_i) {
        }
    } else if (str1.str_i.length() < str2.str_i.length()) {
        for (; 0 != (str2.str_i.length() - str1.str_i.length()); str1.str_i = "0" + str1.str_i) {
        }
    }
    if (str1.str_m.length() > str2.str_m.length()) {
        for (; 0 != (str1.str_m.length() - str2.str_m.length()); str2.str_m += "0") {
        }
    } else if (str1.str_m.length() < str2.str_m.length()) {
        for (; 0 != (str2.str_m.length() - str1.str_m.length()); str1.str_m += "0") {
        }
    }
}

StrF StrF::plus(StrF str) {
    fill_zero(*this, str);
    bool add = false;
    for (unsigned long long i = str_m.length(); i > 0; i--) {
        add = StrF::add(str_m[i - 1], str.str_m[i - 1], add);
    }
    for (unsigned long long i = str_i.length(); i > 0; i--) {
        add = StrF::add(str_i[i - 1], str.str_i[i - 1], add);
    }
    if (add) {
        str_i = "1" + str_i;
    }
    del_zero();
    return *this;
}
StrF StrF::min(StrF str) {
    fill_zero(*this, str);
    bool sub = false;
    for (unsigned long long i = str_m.length(); i > 0; i--) {
        sub = StrF::sub(str_m[i - 1], str.str_m[i - 1], sub);
    }
    for (unsigned long long i = str_i.length(); i > 0; i--) {
        sub = StrF::sub(str_i[i - 1], str.str_i[i - 1], sub);
    }
    del_zero();
    return *this;
}
StrF operator+=(StrF &str1, StrF str2) {
    if (str1.is_min && !str2.is_min) {
        if (str2 > str1.abs()) {
            str1.min(str2);
            str1.is_min = false;
        } else {
            str1 = str2.min(str1);
            str1.is_min = true;
        }
    } else if (!str1.is_min && str2.is_min) {
        if (str1>str2.abs()) {
            str1.min(str2);
            str1.is_min = false;
        } else {
            str1 = str2.min(str1);
            str1.is_min = true;
        }
    } else {
        str1.plus(str2);
    }
    return str1;
}
StrF operator+(const StrF &str1, const StrF &str2) {
    StrF temp = str1;
    temp += str2;
    return temp;
}
bool operator>(StrF str_a, StrF str) {
    StrF::fill_zero(str_a, str);
    if (str_a.is_min && !str.is_min) {
        return false;
    }
    if (!str_a.is_min && str.is_min) {
        return true;
    }
    bool sign = str_a.is_min;
    bool return_value = false;
    if (str_a.str_i.length() > str.str_i.length()) {
        if (sign) {
            return_value = false;
        } else {
            return_value = true;
        }
        return return_value;
    }
    if (str_a.str_i.length() < str.str_i.length()) {
        if (sign) {
            return_value = true;
        } else {
            return_value = false;
        }
        return return_value;
    }
    for (unsigned long long i = str_a.str_i.length(); i > 0; --i) {
        if (str_a.str_i[i - 1] > str.str_i[i - 1]) {
            if (sign) {
                return_value = false;
            } else {
                return_value = true;
            }
            return return_value;
        }
        if (str_a.str_i[i - 1] < str.str_i[i - 1]) {
            if (sign) {
                return_value = true;
            } else {
                return_value = false;
            }
            return return_value;
        }
    }
    for (unsigned long long i = str_a.str_m.length(); i > 0; --i) {
        if (str_a.str_m[i - 1] > str.str_m[i - 1]) {
            if (sign) {
                return_value = false;
            } else {
                return_value = true;
            }
            return return_value;
        }
        if (str_a.str_m[i - 1] < str.str_m[i - 1]) {
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
bool StrF::operator==(const StrF &str) const {
    if (str_i == str.str_i && str_m == str.str_m && is_min == str.is_min) {
        return true;
    }
    return false;
}
bool StrF::operator<=(const StrF &str) const { return (*this < str || *this == str); }
bool StrF::operator<(const StrF &str) const {
    if (*this == str) {
        return false;
    }
    return !(*this > str);
}
bool StrF::operator>=(const StrF &str) const { return (*this > str || *this == str); }

bool StrF::operator!=(const StrF &str) const { return !(*this == str); }
void StrF::del_zero() {
    unsigned long long temp = str_i.length();
    for (int i = 0; i < temp; ++i) {
        if (str_i[i] == '0') {
            str_i.erase(i, 1);
        } else {
            break;
        }
    }
    if (str_i.empty() && str_m.empty() && is_min) {
        is_min = false;
    }
    for (unsigned long long i = str_m.length(); i != 0; --i) {
        if (str_m[i - 1] == '0') {
            str_m.erase(i - 1, 1);
        } else {
            break;
        }
    }
}
StrF::StrF(const std::string &instr) {
    unsigned long long point = instr.find('.');
    if (instr[0] == '-') {
        is_min = true;
        str_i = instr.substr(1, point-1);
    } else {
        str_i = instr.substr(0, point);
    }
    str_m = instr.substr(point + 1, instr.length() - point - 1);
    del_zero();
}
