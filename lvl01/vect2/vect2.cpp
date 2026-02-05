#include "vect2.hpp"
#include <cassert>

vect2::vect2() : _x(0), _y(0)
{
}

vect2::vect2(int x, int y) : _x(x), _y(y)
{
}

vect2::vect2(const vect2 &other) : _x(other._x), _y(other._y)
{
}

vect2 &vect2::operator=(const vect2 &other)
{
    if (this != &other)
    {
        _x = other._x;
        _y = other._y;
    }
    return (*this);
}

vect2::~vect2()
{
}

int vect2::getX(void) const
{
    return (_x);
}

int vect2::getY(void) const
{
    return (_y);
}

int &vect2::operator[](int index)
{
    if (index == 0)
        return (_x);
    return (_y);
}

const int &vect2::operator[](int index) const
{
    if (index == 0)
        return (_x);
    return (_y);
}


// int &vect2::operator[](int index)
// {
//     assert(index == 0 || index == 1);
//     return (index == 0 ? _x : _y);
// }

// const int &vect2::operator[](int index) const
// {
//     assert(index == 0 || index == 1);
//     return (index == 0 ? _x : _y);
// }

vect2 &vect2::operator++()
{
    ++_x;
    ++_y;
    return (*this);
}

vect2 vect2::operator++(int)
{
    vect2 tmp(*this);
    ++(*this);
    return (tmp);
}

vect2 &vect2::operator--()
{
    --_x;
    --_y;
    return (*this);
}

vect2 vect2::operator--(int)
{
    vect2 tmp(*this);
    --(*this);
    return (tmp);
}

bool vect2::operator==(const vect2 &other) const
{
    return (_x == other._x && _y == other._y);
}

bool vect2::operator!=(const vect2 &other) const
{
    return (!(*this == other));
}

vect2 &vect2::operator+=(int value)
{
    _x += value;
    _y += value;
    return (*this);
}

vect2 &vect2::operator-=(int value)
{
    _x -= value;
    _y -= value;
    return (*this);
}

vect2 &vect2::operator*=(int value)
{
    _x *= value;
    _y *= value;
    return (*this);
}

vect2 &vect2::operator+=(const vect2 &other)
{
    _x += other._x;
    _y += other._y;
    return (*this);
}

vect2 &vect2::operator-=(const vect2 &other)
{
    _x -= other._x;
    _y -= other._y;
    return (*this);
}

vect2 vect2::operator+(int value) const
{
    vect2 tmp(*this);
    tmp += value;
    return (tmp);
}

vect2 vect2::operator-(int value) const
{
    vect2 tmp(*this);
    tmp -= value;
    return (tmp);
}

vect2 vect2::operator*(int value) const
{
    vect2 tmp(*this);
    tmp *= value;
    return (tmp);
}

vect2 vect2::operator+(const vect2 &other) const
{
    vect2 tmp(*this);
    tmp += other;
    return (tmp);
}

vect2 vect2::operator-(const vect2 &other) const
{
    vect2 tmp(*this);
    tmp -= other;
    return (tmp);
}

vect2 vect2::operator-(void) const
{
    return (vect2(-_x, -_y));
}


std::ostream &operator<<(std::ostream &out, const vect2 &obj)
{
    out << "{" << obj.getX() << ", " << obj.getY() << "}";
    return (out);
}

vect2 operator*(int lhs, const vect2 &rhs)
{
    return (rhs * lhs);
}
