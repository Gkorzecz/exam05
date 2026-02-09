#pragma once
#include <iostream>
#include <ostream>

class vect2
{
    private:
        int _x;
        int _y;

    public:
        vect2();
        vect2(int x, int y);
        vect2(const vect2 &other);
        vect2 &operator=(const vect2 &other);
        ~vect2();

        int &operator[](int index);
        const int &operator[](int index) const;

        vect2 &operator++();
        vect2 &operator--();
        vect2 operator++(int);
        vect2 operator--(int);

        vect2 &operator+=(const vect2 &other);
        vect2 &operator-=(const vect2 &other);

        vect2 operator+(const vect2 &other) const;
        vect2 operator-(const vect2 &other) const;

        vect2 &operator*=(int value);
        vect2 operator*(int value) const;
        vect2 operator-() const;

        bool operator==(const vect2 &other) const;
        bool operator!=(const vect2 &other) const;
};

std::ostream &operator<<(std::ostream &out, const vect2 &v);
vect2 operator*(int value, const vect2 &v);