#pragma once
#include <exception>

class parametres_of_ec_mismatch_values_exc : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Parametres of the ec mismatch values";
	}
};

class modulo_mismatch_values_exc : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Modulo mismatch values";
	}
};

class division_by_zero_exc : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Division by zero";
	}
};