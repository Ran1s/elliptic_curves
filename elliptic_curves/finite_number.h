#pragma once

#include <iostream>
#include "modulo.h"

class modulo;

class finite_number
{
public:
	finite_number();
	finite_number(class modulo modulo, int value);
	finite_number(const finite_number &);
	finite_number & operator=(const finite_number &);

	friend finite_number operator+(const finite_number &, const finite_number &);
	friend finite_number operator*(const finite_number &, const finite_number &);
	friend finite_number operator-(const finite_number &, const finite_number &);
	friend finite_number operator/(const finite_number &, const finite_number &);
	friend finite_number operator+(const finite_number &, const int &);
	friend finite_number operator*(const finite_number &, const int &);
	friend finite_number operator-(const finite_number &, const int &);
	friend finite_number operator/(const finite_number &, const int &);
	friend finite_number operator+(const int &, const finite_number &);
	friend finite_number operator*(const int &, const finite_number &);
	friend finite_number operator-(const int &, const finite_number &);
	friend finite_number operator/(const int &, const finite_number &);
	friend bool operator==(const finite_number &, const finite_number &);
	friend bool operator!=(const finite_number &, const finite_number &);
	friend bool operator<(const finite_number &, const finite_number &);
	friend bool operator>(const finite_number &, const finite_number &);
	friend bool operator<=(const finite_number &, const finite_number &);
	friend bool operator>=(const finite_number &, const finite_number &);

	static bool equal_group(const finite_number &, const finite_number &);

	finite_number & operator+=(const finite_number &);
	finite_number & operator*=(const finite_number &);
	finite_number & operator-=(const finite_number &);
	finite_number & operator/=(const finite_number &);
	finite_number & operator+=(const int &);
	finite_number & operator*=(const int &);
	finite_number & operator-=(const int &);
	finite_number & operator/=(const int &);
	finite_number & operator++();
	finite_number operator++(int);
	finite_number & operator--();
	finite_number operator--(int);
	finite_number operator-() const;



	extern friend finite_number pow(finite_number, int);
	finite_number mult_inverse() const;
	modulo get_modulo() const;

	operator int() const;

	friend std::ostream & operator<<(std::ostream &, const finite_number &);
	friend std::istream & operator >> (std::istream &, finite_number &);
private:
	modulo modulo;
	int value;
};
