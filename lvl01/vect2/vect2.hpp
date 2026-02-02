#pragma once

#include <iostream>

class vect2
{
public:
    vect2();
    vect2(int x, int y);
    vect2(const vect2 &other);
    vect2 &operator=(const vect2 &other);
    ~vect2();

    int getX(void) const;
    int getY(void) const;

    int &operator[](int index);
    const int &operator[](int index) const;

    vect2 &operator++();
    vect2 operator++(int); 
    vect2 &operator--();
    vect2 operator--(int);

    bool operator==(const vect2 &other) const;
    bool operator!=(const vect2 &other) const;

    vect2 &operator+=(int value);
    vect2 &operator-=(int value);
    vect2 &operator*=(int value);

    vect2 &operator+=(const vect2 &other);
    vect2 &operator-=(const vect2 &other);
    vect2 &operator*=(const vect2 &other);

    vect2 operator+(int value) const;
    vect2 operator-(int value) const;
    vect2 operator*(int value) const;

    vect2 operator+(const vect2 &other) const;
    vect2 operator-(const vect2 &other) const;
    vect2 operator*(const vect2 &other) const;

    vect2 operator-(void) const;

private:
    int _x;
    int _y;
};

std::ostream &operator<<(std::ostream &out, const vect2 &obj);
vect2 operator*(int lhs, const vect2 &rhs);
