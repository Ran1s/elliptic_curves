#pragma once
#include <iostream>

template<typename value_type>
class finite_iterator : public std::iterator<std::input_iterator_tag, value_type>
{
	friend class modulo;
public:
	finite_iterator(const finite_iterator &);
	template <typename value_type>
	friend bool operator!=(finite_iterator<value_type> const &, finite_iterator<value_type> const &);
	template <typename value_type>
	friend bool operator==(finite_iterator<value_type> const &, finite_iterator<value_type> const &);
	typename finite_iterator::value_type operator*() const;
	finite_iterator & operator++();

	template <typename value_type>
	friend std::ostream & operator<<(std::ostream &, const finite_iterator<value_type> &);
	template <typename value_type>
	friend std::istream & operator >> (std::istream &, finite_iterator<value_type> &);
private:
	finite_iterator(value_type value, bool overflowed = false);
	value_type value;
	bool overflowed = false;
};

class modulo
{
public:
	typedef finite_iterator<class finite_number> iterator;
	typedef finite_iterator<const class finite_number> const_iterator;

	modulo();
	modulo(int);
	modulo(const modulo &);
	modulo & operator=(const modulo &);

	friend bool operator==(const modulo &, const modulo &);
	friend bool operator!=(const modulo &, const modulo &);

	modulo & operator++();
	modulo operator++(int);


	iterator begin();
	iterator end();

	const_iterator begin() const;
	const_iterator end() const;

	operator int() const;

	friend std::ostream & operator<<(std::ostream &, const modulo &);
	friend std::istream & operator >> (std::istream &, modulo &);
private:
	int value;
};


template<typename value_type>
inline finite_iterator<value_type>::finite_iterator(const finite_iterator & finite_iterator) : value(finite_iterator.value), overflowed(finite_iterator.overflowed) { }

template<typename value_type>
inline typename finite_iterator<value_type>::value_type finite_iterator<value_type>::operator*() const
{
	return value;
}

template<typename value_type>
inline finite_iterator<value_type> & finite_iterator<value_type>::operator++()
{
	++value;
	if (value == 0)
	{
		overflowed = true;
	}
	return *this;
}

template<typename value_type>
inline finite_iterator<value_type>::finite_iterator(value_type value, bool overflowed = false) : value(value), overflowed(overflowed) { }

template<typename value_type>
inline bool operator!=(finite_iterator<value_type> const & lhs, finite_iterator<value_type> const & rhs)
{
	return !(lhs == rhs);
}

template<typename value_type>
inline bool operator==(finite_iterator<value_type> const & lhs, finite_iterator<value_type> const & rhs)
{
	return lhs.value == rhs.value && lhs.overflowed == rhs.overflowed;
}

template<typename value_type>
inline std::ostream & operator<<(std::ostream & out, const finite_iterator<value_type> & finite_iterator)
{
	out << finite_iterator.value;
	return out;
}

template<typename value_type>
inline std::istream & operator >> (std::istream & in, finite_iterator<value_type> & finite_iterator)
{
	in >> finite_iterator.value;
	return in;
}