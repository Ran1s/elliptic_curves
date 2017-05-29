#include "elliptic_curves.h"
#include <algorithm>

ec_point::ec_point() : a(), b(), x(), y(), null(false) { }

ec_point::ec_point(finite_number a, finite_number b, finite_number x, finite_number y, bool null) : a(a), b(b), x(x), y(y), null(null)
{
	if (!equal_group(*this))
	{
		throw modulo_mismatch_values_exc();
	}
}

ec_point::ec_point(bool null) : a(), b(), x(), y(), null(null) { }

ec_point::ec_point(const ec_point & ec_point)
{
	*this = ec_point;
}

ec_point & ec_point::operator=(const ec_point & ec_point)
{
	a = ec_point.a;
	b = ec_point.b;
	x = ec_point.x;
	y = ec_point.y;
	null = ec_point.null;
	return *this;
}

ec_point & ec_point::operator+=(const ec_point & ec_point)
{
	if (a != ec_point.a || b != ec_point.b)
	{
		throw parametres_of_ec_mismatch_values_exc();
	}
	*this = *this + ec_point;
	return *this;
}

ec_point & ec_point::operator-=(const ec_point & ec_point)
{
	*this += -ec_point;
	return *this;
}

ec_point & ec_point::operator*=(const int & num)
{
	*this = *this * num;
	return *this;
}

ec_point ec_point::operator-() const
{
	return ec_point(a, b, x, -y);
}

finite_number ec_point::get_x()
{
	return x;
}

finite_number ec_point::get_y()
{
	return y;
}

finite_number ec_point::get_a()
{
	return a;
}

finite_number ec_point::get_b()
{
	return b;
}

modulo ec_point::get_p()
{
	return a.get_modulo();
}

bool ec_point::equal_group(const ec_point & ec_point)
{
	return finite_number::equal_group(ec_point.a, ec_point.b) && finite_number::equal_group(ec_point.a, ec_point.x) && finite_number::equal_group(ec_point.a, ec_point.y);
}

bool ec_point::equal_group(const ec_point & lhs, const ec_point & rhs)
{
	return equal_group(lhs) && equal_group(rhs) && finite_number::equal_group(lhs.a, rhs.a);
}

ec_point operator+(ec_point lhs, ec_point rhs)
{
	if (lhs.a != rhs.a || lhs.b != rhs.b)
	{
		throw parametres_of_ec_mismatch_values_exc();
	}
	if (!ec_point::equal_group(lhs, rhs))
	{
		throw modulo_mismatch_values_exc();
	}

	if (rhs.null)
	{
		std::swap(lhs, rhs);
	}

	if (lhs.null)
	{
		return rhs;
	}

	finite_number lambda;
	if (lhs == rhs)
	{
		if (lhs.y == 0)
		{
			return ec_point(lhs.a, lhs.b, lhs.x, lhs.y, true);
		}
		lambda = (3 * pow(lhs.x, 2) + lhs.a) / (2 * lhs.y);
	}
	else
	{
		if (lhs.x == rhs.x)
		{
			return ec_point(lhs.a, lhs.b, lhs.x, lhs.y, true);
		}
		lambda = (rhs.y - lhs.y) / (rhs.x - lhs.x);
	}

	finite_number x, y;
	x = pow(lambda, 2) - lhs.x - rhs.x;
	y = lambda * (lhs.x - x) - lhs.y;
	
	return ec_point(lhs.a, lhs.b, x, y);
}

ec_point operator-(const ec_point & lhs, const ec_point & rhs)
{
	return lhs + -rhs;
}

ec_point operator*(ec_point lhs, int rhs)
{
	if (rhs >= 0)
	{
		ec_point result(true);
		while (rhs > 0)
		{
			if (rhs % 2 == 0)
			{
				rhs /= 2;
				lhs += lhs;
			}
			else
			{
				rhs--;
				result += lhs;
			}
		}
		return result;
	}
	else
	{
		return -lhs * -rhs;
	}
}

ec_point operator*(const int & lhs, const ec_point & rhs)
{
	return rhs * lhs;
}

bool operator==(const ec_point & lhs, const ec_point & rhs)
{
	if (lhs.a != rhs.a || lhs.b != rhs.b)
	{
		throw parametres_of_ec_mismatch_values_exc();
	}
	if (!ec_point::equal_group(lhs, rhs))
	{
		throw modulo_mismatch_values_exc();
	}
	if (lhs.null || rhs.null)
	{
		return lhs.a == rhs.a && lhs.b == rhs.b && lhs.null == rhs.null;
	}
	else
	{
		return lhs.a == rhs.a && lhs.b == rhs.b && lhs.x == rhs.x && lhs.y == rhs.y;
	}	
}

bool operator!=(const ec_point & lhs, const ec_point & rhs)
{
	return !(lhs == rhs);
}

bool operator<(const ec_point & lhs, const ec_point & rhs)
{
	if (lhs.a != rhs.a || lhs.b != rhs.b)
	{
		throw parametres_of_ec_mismatch_values_exc();
	}
	if (!ec_point::equal_group(lhs, rhs))
	{
		throw modulo_mismatch_values_exc();
	}
	if (lhs.null)
	{
		return true;
	}
	else if (rhs.null)
	{
		return false;
	}
	else if (lhs.x < rhs.x)
	{
		return true;
	}
	else if (lhs.x > rhs.x)
	{
		return false;
	}
	else
	{
		return lhs.y < rhs.y;
	}
}

std::ostream & operator<<(std::ostream & out, const ec_point & ec_point)
{
	out << ec_point.a << std::endl;
	out << ec_point.b << std::endl;
	if (ec_point.null)
	{
		out << "INF" << std::endl;
		out << "INF" << std::endl;
	}
	else
	{
		out << ec_point.x << std::endl;
		out << ec_point.y << std::endl;
	}
	
	return out;
}

std::istream & operator >> (std::istream & in, ec_point & ec_point)
{
	in >> ec_point.a;
	in >> ec_point.b;
	in >> ec_point.x;
	in >> ec_point.y;
	return in;
}
