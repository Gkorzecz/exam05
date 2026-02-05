#include "bigint.hpp"

bigint::bigint() : _string("0")
{}

bigint::bigint(unsigned int num)
{
	std::ostringstream oss;
	oss << num;
	this->_string = oss.str();
}

bigint::bigint(const bigint &other)
{
	this->_string = other._string;
}

bigint &bigint::operator=(const bigint &other)
{
	if (this != &other)
		this->_string = other._string;
	return (*this);
}

bigint::~bigint()
{}

std::string bigint::getString() const
{
	return (this->_string);
}

bigint bigint::operator+(const bigint &other) const
{
	bigint copy(*this);

	std::string str1 = copy._string;
	std::string str2 = other._string;

	if (str2.size() > str1.size())
    	std::swap(str1, str2);

	std::string result;
	int i = str1.length() - 1;
	int j = str2.length() - 1;
	int carry = 0;

	while(i >= 0 || j >= 0 || carry)
	{
		int digit1 = 0;
		int digit2 = 0;

		if (i >= 0)
			digit1 = str1[i] - '0';
		if (j >= 0)
			digit2 = str2[j] - '0';
		int sum = digit1 + digit2 + carry;
		
		result.insert(result.begin(), (sum % 10) + '0');
		carry = sum / 10;

		i--;
		j--;
	}
	copy._string = result;
	return (copy);
}

bigint& bigint::operator+=(const bigint& other)
{
    *this = *this + other;
    return *this;
}

bigint bigint::operator++(int)
{
    bigint old(*this);
    ++(*this);
    return old;
}

bigint &bigint::operator++()
{
	bigint	copy(1);
	*this += copy;
	return (*this);
}

bool bigint::operator>(const bigint &other) const
{
	if (this->_string.size() > other._string.size())
		return(true);
	if (this->_string.size() < other._string.size())
		return(false);

	for (size_t i = 0; i < this->_string.size(); i++)
	{
		if (this->_string[i] != other._string[i])
		{
			if (this->_string[i] > other._string[i])
				return(true);
			if (this->_string[i] < other._string[i])
				return(false);
		}
	}
	return (false);
}

bool bigint::operator<(const bigint &other) const
{
	if (this->_string.size() < other._string.size())
		return(true);
	if (this->_string.size() > other._string.size())
		return(false);

	for (size_t i = 0; i < this->_string.size(); i++)
	{
		if (this->_string[i] != other._string[i])
		{
			if (this->_string[i] < other._string[i])
				return(true);
			if (this->_string[i] > other._string[i])
				return(false);
		}
	}
	return (false);
}

bool bigint::operator==(const bigint &other) const
{
	if (this->_string == other._string)
		return(true);
	return(false);
}

bool bigint::operator!=(const bigint &other) const
{
	if (this->_string != other._string)
		return(true);
	return(false);
}

bool bigint::operator>=(const bigint &other) const
{
	if (*this > other || *this == other)
		return (true);
	return (false);
}

bool bigint::operator<=(const bigint &other) const
{
	if (*this < other || *this == other)
		return (true);
	return (false);
}

bigint bigint::operator<<(unsigned int shift) const
{
	bigint copy(*this);
	if(copy._string == "0")
		return(copy);
	copy._string.append(shift, '0');
	return(copy);
}

bigint &bigint::operator<<=(unsigned int shift)
{
	if (this->_string == "0")
		return(*this);
	this->_string.append(shift, '0');
	return(*this);
}

bigint &bigint::operator>>=(const bigint& other)
{
	if (this->_string == "0")
		return(*this);
	std::stringstream ss;
	ss << other;
	size_t shift = 0;
	ss >> shift;

	if (this->_string.size() > shift)
		this->_string.erase((this->_string.begin() + (this->_string.size() - shift)), this->_string.end());
	else
		this->_string = "0";
	return(*this);
}

std::ostream &operator<<(std::ostream &out, const bigint &obj)
{
	out << obj.getString();
	return(out);
}

// static std::string normalize(std::string s)
// {
//     size_t i = 0;
//     while (i + 1 < s.size() && s[i] == '0')
//         ++i;
//     return s.substr(i);
// }