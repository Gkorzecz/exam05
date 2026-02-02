#pragma once
#include <iostream>

struct vect2 {

	int x, y;

	vect2(int a = 0, int b = 0) : x(a), y(b) {}
	vect2(const vect2 &v) : x(v.x), y(v.y) {}
	vect2 &operator=(const vect2 &v) { x = v.x; y = v.y; return *this;}

	vect2 operator+(int i) const {return vect2(x + i, y + i);}
	vect2 operator*(int i) const {return vect2(x * i, y * i);}
	vect2 operator-(int i) const {return vect2(x - i, y - i);}

	vect2 operator+(const vect2 &v) const { return vect2(x + v.x, y + v.y);}
	vect2 operator-(const vect2 &v) const { return vect2(x - v.x, y - v.y);}
	vect2 operator*(const vect2 &v) const { return vect2(x * v.x, y * v.y);}

	vect2 operator+=(int i) {x += i; x += i; return *this;}
	vect2 operator-=(int i) {x -= i; x -= i; return *this;}
	vect2 operator*=(int i) {x *= i; x *= i; return *this;}

	vect2 operator+=(const vect2 &v) {x += v.x; y += v.y; return *this;}
	vect2 operator-=(const vect2 &v) {x -= v.x; y -= v.y; return *this;}
	vect2 operator*=(const vect2 &v) {x *= v.x; y *= v.y; return *this;}

	vect2 &operator++() {x++; y++; return *this;}
	vect2 &operator--() {x--; y--; return *this;}

	vect2 operator+() const {return(*this);}
	vect2 operator-() const {return(vect2(-x, -y));}

	vect2 operator++(int) {vect2 tmp(*this); x++; y++; return tmp;}
	vect2 operator--(int) {vect2 tmp(*this); x--; y--; return tmp;}

	bool operator==(const vect2 &v) const {return(v.x == x && v.y == y);}
	bool operator!=(const vect2 &v) const {return(!(v == *this));}

	void print() const {std::cout << "{" << x << ", " << y << "}" << std::endl;}
};

inline vect2 operator+(int i, const vect2 &v) { return(v + i);}
inline vect2 operator*(int i, const vect2 &v) { return(v * i);}

inline std::ostream &operator<<(std::ostream &os, const vect2 &v)
{
	os << "{" << v.x << ", " << v.y << "}";
	return os;
}
