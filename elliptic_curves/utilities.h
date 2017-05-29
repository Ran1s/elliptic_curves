#pragma once
#include <utility>
#include <algorithm>
#include <vector>
#include "elliptic_curves.h"

//ec_point qwe;
//bool single_generator(std::vector<ec_point>, ec_point &);

template<typename T>
constexpr bool check_type = std::is_same<T, int>::value || std::is_same<T, long long>::value || std::is_same<T, modulo>::value;

template<typename T>
std::pair<T, T> gcd(T a, T b)
{
	static_assert(check_type<T>, "int and long long are allowed only");
	if (a < b)
	{
		std::swap(a, b);
	}

	if (b == 0)
	{
		return{ 0, 1 };
	}
	else
	{
		auto xy = gcd(b, a % b);
		return{ xy.second - (a / b) * xy.first, xy.first };
	}
}

template<typename T>
std::vector<T> primes(T n)
{
	static_assert(check_type<T>, "int and long long are allowed only");
	std::vector<bool> primes(n + 1, true);
	primes[0] = false;
	primes[1] = false;

	for (T i = 2; i <= n; i++)
	{
		for (T j = 2; i * j <= n; j++)
		{
			primes[i * j] = false;
		}
	}

	std::vector<T> result;
	for (T i = 2; i <= n; i++)
	{
		if (primes[i])
		{
			result.push_back(i);
		}
	}
	return result;
}