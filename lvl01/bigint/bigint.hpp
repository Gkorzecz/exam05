#pragma once

#include <string>
#include <iostream>
#include <ostream>
#include <sstream>

class bigint
{
	private:
		std::string _string;
	
	public:
		bigint();
		bigint(unsigned int num);
		bigint(const bigint &other);
		bigint &operator=(const bigint &other);
		~bigint();

		bigint operator+(const bigint &other) const;
		bigint &operator+=(const bigint &other);
		bigint operator++(int);
		bigint &operator++();
		bool operator>(const bigint &other) const;
		bool operator<(const bigint &other) const;
		bool operator==(const bigint &other) const;
		bool operator!=(const bigint &other) const;
		bool operator>=(const bigint &other) const;
		bool operator<=(const bigint &other) const;

		bigint operator<<(unsigned int shift) const;
		bigint &operator<<=(unsigned int shift);
		bigint &operator>>=(const bigint& other);

		std::string getString() const;
	
};

std::ostream &operator<<(std::ostream &out, const bigint &obj);