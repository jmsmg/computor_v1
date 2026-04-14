#include "Polynomial.hpp"
#include <sstream>
#include <cmath>

Polynomial::Polynomial()
{
}

Polynomial::Polynomial(const Polynomial &obj)
{
	*this = obj;
}

Polynomial	&Polynomial::operator=(const Polynomial &obj)
{
	if (this != &obj)
	{
		this->_terms = obj._terms;
	}
	return (*this);
}

Polynomial::~Polynomial()
{
}

void	Polynomial::setTerm(int exponent, double coefficient)
{
	this->_terms[exponent] += coefficient;
}

double	Polynomial::getCoefficient(int exponent) const
{
	std::map<int, double>::const_iterator	it = this->_terms.find(exponent);

	if (it != this->_terms.end())
		return (it->second);
	return (0.0);
}

int	Polynomial::getDegree(void) const
{
	int	degree;

	degree = 0;
	for (const auto &term : this->_terms)
	{
		if (std::abs(term.second) > 1e-10 && term.first > degree)
			degree = term.first;
	}
	return (degree);
}

void	Polynomial::reduce(void)
{
}

std::string	Polynomial::toReducedForm(void) const
{
	std::ostringstream	oss;
	bool				first;

	first = true;
	if (this->_terms.empty())
	{
		oss << "0 = 0";
		return (oss.str());
	}
	for (const auto &term : this->_terms)
	{
		double	coef = term.second;
		int		exp = term.first;

		if (std::abs(coef) < 1e-10)
			coef = 0;
		if (first)
		{
			oss << coef << " * X^" << exp;
			first = false;
		}
		else
		{
			if (coef >= 0)
				oss << " + " << coef << " * X^" << exp;
			else
				oss << " - " << -coef << " * X^" << exp;
		}
	}
	if (first)
		oss << "0";
	oss << " = 0";
	return (oss.str());
}

Polynomial	Polynomial::operator-(const Polynomial &obj) const
{
	Polynomial	result(*this);

	for (const auto &term : obj._terms)
		result._terms[term.first] -= term.second;
	return (result);
}
