#include "modulo.h"
#include "finite_group.h"

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

modulo & modulo::operator++()
{
	++value;
	return *this;
}

modulo modulo::operator++(int)
{
	modulo modulo(*this);
	++(*this);
	return modulo;
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