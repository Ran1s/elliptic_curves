//#include "finite_group.h"

finite_number::finite_number() : value(0) { }

finite_number::finite_number(class modulo modulo, int value) : modulo(modulo), value(value)
{
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

finite_number & finite_number::operator+=(const finite_number & finite_number)
{
	if (this->modulo != finite_number.modulo)
	{
		throw modulo_mismatch_values_exc();
	}
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

finite_number finite_number::mult_inverse() const
{
	return pow(*this, int(this->modulo) - 2);
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
	out << finite_number.modulo << " "  << finite_number.value;
	return out;
}

std::istream & operator>>(std::istream & in, finite_number & finite_number)
{
	in >> finite_number.modulo >> finite_number.value;
	finite_number.value %= int(finite_number.modulo);
	return in;
}

modulo::modulo() : value(1) { }

modulo::modulo(int value) : value(value) { }

modulo::modulo(const modulo & modulo)
{
	*this = modulo;
}

modulo & modulo::operator=(const modulo & modulo)
{
	value = modulo.value;
	return *this;
}

modulo::iterator modulo::begin()
{
	return iterator(finite_number(value, 0));
}

modulo::iterator modulo::end()
{
	return iterator(finite_number(value, 0), true);
}

modulo::const_iterator modulo::begin() const
{
	return const_iterator(finite_number(value, 0));
}

modulo::const_iterator modulo::end() const
{
	return const_iterator(finite_number(value, 0), true);
}

modulo::operator int() const
{
	return value;
}

bool operator==(const modulo & lhs, const modulo & rhs)
{
	return lhs.value == rhs.value;
}

bool operator!=(const modulo & lhs, const modulo & rhs)
{
	return !(lhs.value == rhs.value);
}

std::ostream & operator<<(std::ostream & out, const modulo & modulo)
{
	out << modulo.value;
	return out;
}

std::istream & operator >> (std::istream & in, modulo & modulo)
{
	in >> modulo.value;
	return in;
}