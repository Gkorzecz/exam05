#include "bigint.hpp"

#include <algorithm>
#include <cctype>

bigint::bigint() : num("0")
{}

bigint::bigint(size_t n) : num(std::to_string(n))
{}

bigint::bigint(const bigint& oth) : num(oth.num)
{}

bigint::bigint(const std::string& n)
{
    if (n.empty() || !std::all_of(n.begin(), n.end(), [](unsigned char c){ return std::isdigit(c); }) || (n.size() > 1 && n[0] == '0'))
        num = "0";
    else
        num = n;
}

std::ostream& operator<<(std::ostream& os, const bigint& b)
{
    return (os << b.num);
}

std::string bigint::add_strings(const std::string& n1, const std::string& n2) const
{
    std::string result;
    int carry = 0;
    int i = static_cast<int>(n1.size()) - 1;
    int j = static_cast<int>(n2.size()) - 1;

    while (i >= 0 || j >= 0 || carry)
    {
        int sum = carry;
        if (i >= 0)
            sum += n1[i--] - '0';
        if (j >= 0)
            sum += n2[j--] - '0';

        result.push_back(char(sum % 10 + '0'));
        carry = sum / 10;
    }

    std::reverse(result.begin(), result.end());
    return (result);
}

bigint bigint::operator+(const bigint& oth) const
{
    return bigint(add_strings(num, oth.num));
}

bigint& bigint::operator+=(const bigint& oth) {
    num = add_strings(num, oth.num);
    return *this;
}

bigint& bigint::operator++() {
    return *this += bigint(1);
}

bigint bigint::operator++(int) {
    bigint tmp(*this);
    ++(*this);
    return tmp;
}

bigint bigint::operator<<(size_t shift) const {
    return bigint(num + std::string(shift, '0'));
}

bigint& bigint::operator<<=(size_t shift) {
    num += std::string(shift, '0');
    return *this;
}

bigint& bigint::operator>>=(const bigint& b) {
    if (bigint(num.size()) <= b)
        num = "0";
    else {
        bigint i(0);
        while (i < b) {
            num.pop_back();
            ++i;
        }
    }
    return *this;
}

bool bigint::operator<(const bigint& oth) const {
    if (num.size() != oth.num.size())
        return num.size() < oth.num.size();
    return num < oth.num;
}

bool bigint::operator>(const bigint& oth) const {
    return oth < *this;
}

bool bigint::operator<=(const bigint& oth) const {
    return !(*this > oth);
}

bool bigint::operator>=(const bigint& oth) const {
    return !(*this < oth);
}

bool bigint::operator==(const bigint& oth) const {
    return num == oth.num;
}

bool bigint::operator!=(const bigint& oth) const {
    return num != oth.num;
}

bigint bigint::operator-(const bigint& oth) const {
    (void)oth;
    return bigint();
}
