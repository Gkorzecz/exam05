#include "vect2.hpp"

vect2::vect2() : _x(0), _y(0)
{}

vect2::vect2(int x, int y) : _x(x), _y(y)
{}

vect2::vect2(const vect2 &other) : _x(other._x), _y(other._y)
{}

vect2 &vect2::operator=(const vect2 &other)
{
    if (this != &other)
    {
        this->_x = other._x;
        this->_y = other._y;
    }
    return(*this);
}

vect2::~vect2()
{}

int &vect2::operator[](int index)
{
    if (index == 0)
        return(this->_x);
    return(this->_y);
}

const int &vect2::operator[](int index) const
{
    if (index == 0)
        return(this->_x);
    return(this->_y);
}

vect2 &vect2::operator++()
{
    this->_x += 1;
    this->_y += 1;
    return(*this);
}

vect2 &vect2::operator--()
{
    this->_x -= 1;
    this->_y -= 1;
    return(*this);
}

vect2 vect2::operator++(int)
{
    vect2 copy(*this);
    this->_x += 1;
    this->_y += 1;
    return(copy);
}

vect2 vect2::operator--(int)
{
    vect2 copy(*this);
    this->_x -= 1;
    this->_y -= 1;
    return(copy);
}

vect2 &vect2::operator+=(const vect2 &other)
{
    this->_x += other._x;
    this->_y += other._y;
    return(*this);
}

vect2 &vect2::operator-=(const vect2 &other)
{
    this->_x -= other._x;
    this->_y -= other._y;
    return(*this);
}

vect2 vect2::operator+(const vect2 &other) const
{
    vect2 copy(*this);
    copy += other;
    return(copy);
}

vect2 vect2::operator-(const vect2 &other) const
{
    vect2 copy(*this);
    copy -= other;
    return(copy);
}

vect2 &vect2::operator*=(int value)
{
    this->_x *= value;
    this->_y *= value;
    return(*this);
}

vect2 vect2::operator*(int value) const
{
    vect2 copy(*this);
    copy._x *= value;
    copy._y *= value;
    return(copy);
}

vect2 vect2::operator-() const
{
    return(vect2(-_x, -_y));
}

bool vect2::operator==(const vect2 &other) const
{
    if (this->_x == other._x && this->_y == other._y)
        return(true);
    return(false);
}

bool vect2::operator!=(const vect2 &other) const
{
    return(!(*this == other));
}

std::ostream &operator<<(std::ostream &out, const vect2 &v)
{
    out << "{" << v[0] << ", " << v[1] << "}";
    return(out);
}

vect2 operator*(int value, const vect2 &v)
{
    return(v * value);
}