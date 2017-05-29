#include "finite_number.h"
#include "exceptions.h"
#include "modulo.h"
#include "utilities.h"

finite_number::finite_number() : value(0) { }

finite_number::finite_number(class modulo modulo, int value) : modulo(modulo), value(value)
{
	this->value %= int(modulo);
	this->value += int(modulo);
	this->value %= int(modulo);
}

finite_number::finite_number(const finite_number & finite_number)
{
	*this = finite_number;
}

finite_number & finite_number::operator=(const finite_number & finite_number)
{
	modulo = finite_number.modulo;
	value = finite_number.value;
	return *this;
}

bool finite_number::equal_group(const finite_number & lhs, const finite_number & rhs)
{
	return lhs.modulo == rhs.modulo;
}

finite_number & finite_number::operator+=(const finite_number & finite_number)
{
	if (this->modulo != finite_number.modulo)
	{
		throw modulo_mismatch_values_exc();
	}
	else
	{
		*this = *this + finite_number;
		return *this;
	}
}

finite_number & finite_number::operator*=(const finite_number & finite_number)
{
	if (this->modulo != finite_number.modulo)
	{
		throw modulo_mismatch_values_exc();
	}
	else
	{
		*this = *this * finite_number;
		return *this;
	}
}

finite_number & finite_number::operator-=(const finite_number & finite_number)
{
	if (this->modulo != finite_number.modulo)
	{
		throw modulo_mismatch_values_exc();
	}
	else
	{
		*this = *this - finite_number;
		return *this;
	}
}

finite_number & finite_number::operator/=(const finite_number & finite_number)
{
	if (this->modulo != finite_number.modulo)
	{
		throw modulo_mismatch_values_exc();
	}
	else
	{
		*this = *this / finite_number;
		return *this;
	}
}

finite_number & finite_number::operator+=(const int & value)
{
	*this += finite_number(this->modulo, value);
	return *this;
}

finite_number & finite_number::operator*=(const int & value)
{
	*this *= finite_number(this->modulo, value);
	return *this;
}

finite_number & finite_number::operator-=(const int & value)
{
	*this -= finite_number(this->modulo, value);
	return *this;
}

finite_number & finite_number::operator/=(const int & value)
{
	*this /= finite_number(this->modulo, value);
	return *this;
}

finite_number & finite_number::operator++()
{
	*this += 1;
	return *this;
}

finite_number finite_number::operator++(int)
{
	finite_number finite_number = *this;
	++(*this);
	return finite_number;
}

finite_number & finite_number::operator--()
{
	*this -= 1;
	return *this;
}

finite_number finite_number::operator--(int)
{
	finite_number finite_number = *this;
	--(*this);
	return finite_number;
}

finite_number finite_number::operator-() const
{
	return *this * -1;
}

finite_number finite_number::mult_inverse() const
{
	//return pow(*this, int(this->modulo) - 2);
	return finite_number(modulo, gcd(int(modulo), value).first);
}

modulo finite_number::get_modulo() const
{
	return modulo;
}

finite_number::operator int() const
{
	return value;
}

finite_number operator+(const finite_number & lhs, const finite_number & rhs)
{
	if (lhs.modulo != rhs.modulo)
	{
		throw modulo_mismatch_values_exc();
	}
	else
	{
		return finite_number(lhs.modulo, lhs.value + rhs.value);
	}
}

finite_number operator*(const finite_number & lhs, const finite_number & rhs)
{
	if (lhs.modulo != rhs.modulo)
	{
		throw modulo_mismatch_values_exc();
	}
	else
	{
		return finite_number(lhs.modulo, lhs.value * rhs.value);
	}
}

finite_number operator-(const finite_number & lhs, const finite_number & rhs)
{
	if (lhs.modulo != rhs.modulo)
	{
		throw modulo_mismatch_values_exc();
	}
	else
	{
		return lhs + rhs * finite_number(rhs.modulo, -1);
	}
}

finite_number operator/(const finite_number & lhs, const finite_number & rhs)
{
	if (lhs.modulo != rhs.modulo)
	{
		throw modulo_mismatch_values_exc();
	}
	else if (rhs.value == 0)
	{
		throw division_by_zero_exc();
	}
	else
	{
		return lhs * rhs.mult_inverse();
	}
}

finite_number operator+(const finite_number & finite_number, const int & int_number)
{
	return finite_number + finite_number::finite_number(finite_number.modulo, int_number);
}

finite_number operator*(const finite_number & finite_number, const int & int_number)
{
	return finite_number * finite_number::finite_number(finite_number.modulo, int_number);
}

finite_number operator-(const finite_number & finite_number, const int & int_number)
{
	return finite_number - finite_number::finite_number(finite_number.modulo, int_number);
}

finite_number operator/(const finite_number & finite_number, const int & int_number)
{
	return finite_number / finite_number::finite_number(finite_number.modulo, int_number);
}

finite_number operator+(const int & lhs, const finite_number & rhs)
{
	return rhs + lhs;
}

finite_number operator*(const int & lhs, const finite_number & rhs)
{
	return rhs * lhs;
}

finite_number operator-(const int & lhs, const finite_number & rhs)
{
	return rhs - lhs;
}

finite_number operator/(const int & lhs, const finite_number & rhs)
{
	return rhs / lhs;
}

bool operator==(const finite_number & lhs, const finite_number & rhs)
{
	if (lhs.modulo != rhs.modulo)
	{
		throw modulo_mismatch_values_exc();
	}
	else
	{
		return lhs.value == rhs.value;
	}
}

bool operator!=(const finite_number & lhs, const finite_number & rhs)
{
	return !(lhs == rhs);
}

bool operator<(const finite_number & lhs, const finite_number & rhs)
{
	if (lhs.modulo != rhs.modulo)
	{
		throw modulo_mismatch_values_exc();
	}
	else
	{
		return lhs.value < rhs.value;
	}
}

bool operator>(const finite_number & lhs, const finite_number & rhs)
{
	return rhs < lhs;
}

bool operator<=(const finite_number & lhs, const finite_number & rhs)
{
	return lhs < rhs || lhs == rhs;
}

bool operator>=(const finite_number & lhs, const finite_number & rhs)
{
	return rhs <= lhs;
}

finite_number pow(finite_number finite_number, int p)
{
	if (p >= 0)
	{
		class finite_number result(finite_number.modulo, 1);
		while (p > 0)
		{
			if (p % 2 == 0)
			{
				p /= 2;
				finite_number *= finite_number;
			}
			else
			{
				p--;
				result *= finite_number;
			}
		}
		return result;
	}
	else
	{
		return pow(finite_number.mult_inverse(), -p);
	}
}

std::ostream & operator<<(std::ostream & out, const finite_number & finite_number)
{
	out << finite_number.modulo << " " << finite_number.value;
	return out;
}

std::istream & operator >> (std::istream & in, finite_number & finite_number)
{
	in >> finite_number.modulo >> finite_number.value;
	finite_number.value %= int(finite_number.modulo);
	return in;
}