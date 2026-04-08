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
	int												degree;
	std::map<int, double>::const_iterator			it;

	degree = 0;
	it = this->_terms.begin();
	while (it != this->_terms.end())
	{
		if (std::abs(it->second) > 1e-10 && it->first > degree)
			degree = it->first;
		++it;
	}
	return (degree);
}

void	Polynomial::reduce(void)
{
}

std::string	Polynomial::toReducedForm(void) const
{
	std::ostringstream						oss;
	bool									first;
	std::map<int, double>::const_iterator	it;

	first = true;
	if (this->_terms.empty())
	{
		oss << "0 = 0";
		return (oss.str());
	}
	it = this->_terms.begin();
	while (it != this->_terms.end())
	{
		double	coef = it->second;
		int		exp = it->first;

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
		++it;
	}
	if (first)
		oss << "0";
	oss << " = 0";
	return (oss.str());
}

Polynomial	Polynomial::operator-(const Polynomial &obj) const
{
	Polynomial									result(*this);
	std::map<int, double>::const_iterator		it;

	it = obj._terms.begin();
	while (it != obj._terms.end())
	{
		result._terms[it->first] -= it->second;
		++it;
	}
	return (result);
}
