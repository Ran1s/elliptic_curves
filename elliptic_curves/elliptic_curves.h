#pragma once
#include "finite_group.h"
#include <iostream>

class ec_point
{
public:
	ec_point();
	ec_point(finite_number a, finite_number b, finite_number x, finite_number y, bool null = false);
	ec_point(bool null);	
	ec_point(const ec_point &);
	ec_point & operator=(const ec_point &);
	
	friend ec_point operator+(ec_point, ec_point);
	friend ec_point operator-(const ec_point &, const ec_point &);
	friend ec_point operator*(ec_point, int);
	friend ec_point operator*(const int &, const ec_point &);

	ec_point & operator+=(const ec_point &);
	ec_point & operator-=(const ec_point &);
	ec_point & operator*=(const int &);

	ec_point operator-() const;

	friend bool operator==(const ec_point &, const ec_point &);
	friend bool operator!=(const ec_point &, const ec_point &);
	friend bool operator<(const ec_point &, const ec_point &);
	friend std::ostream & operator<<(std::ostream &, const ec_point &);
	friend std::istream & operator>>(std::istream &, ec_point &);

	finite_number get_x();
	finite_number get_y();
	finite_number get_a();
	finite_number get_b();
	modulo get_p();
private:
	finite_number x, y, a, b;
	bool null;
	static bool equal_group(const ec_point &);
	static bool equal_group(const ec_point &, const ec_point &);
};