#pragma once

#include <string>
#include <iostream>

class bigint {
private:
    std::string num;

    std::string add_strings(const std::string& n1,
                            const std::string& n2) const;

public:
    bigint();
    bigint(size_t n);
    bigint(const std::string& n);
    bigint(const bigint& oth);

    bigint& operator=(const bigint& oth) = default;

    friend std::ostream& operator<<(std::ostream& os, const bigint& b);

    bigint operator+(const bigint& oth) const;
    bigint& operator+=(const bigint& oth);

    bigint& operator++();
    bigint operator++(int);

    bigint operator<<(size_t shift) const;
    bigint& operator<<=(size_t shift);
    bigint& operator>>=(const bigint& b);

    bool operator<(const bigint& oth) const;
    bool operator>(const bigint& oth) const;
    bool operator<=(const bigint& oth) const;
    bool operator>=(const bigint& oth) const;
    bool operator==(const bigint& oth) const;
    bool operator!=(const bigint& oth) const;

    bigint operator-(const bigint& oth) const;
};
