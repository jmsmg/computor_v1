#include "Solver.hpp"
#include <iostream>

Solver::Solver()
{
}

Solver::Solver(const Polynomial &poly) : _poly(poly)
{
}

Solver::Solver(const Solver &obj)
{
	*this = obj;
}

Solver	&Solver::operator=(const Solver &obj)
{
	if (this != &obj)
	{
		this->_poly = obj._poly;
	}
	return (*this);
}

Solver::~Solver()
{
}

void	Solver::setPolynomial(const Polynomial &poly)
{
	this->_poly = poly;
}

double	Solver::_sqrt(double n)
{
	double	x;
	double	epsilon;

	if (n < 0)
		return (-1);
	if (n == 0)
		return (0);
	x = n;
	epsilon = 1e-10;
	while (true)
	{
		double	next = (x + n / x) / 2.0;
		double	diff = next - x;

		if (diff < 0)
			diff = -diff;
		if (diff < epsilon)
			break ;
		x = next;
	}
	return (x);
}

void	Solver::_solveDegree0(void)
{
	double	c;

	c = this->_poly.getCoefficient(0);
	if (c == 0)
		std::cout << "All real numbers are solutions." << std::endl;
	else
		std::cout << "No solution." << std::endl;
}

void	Solver::_solveDegree1(void)
{
	double	b;
	double	c;
	double	solution;

	b = this->_poly.getCoefficient(1);
	c = this->_poly.getCoefficient(0);
	solution = -c / b;
	std::cout << "The solution is:" << std::endl;
	std::cout << solution << std::endl;
}

void	Solver::_solveDegree2(void)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;

	a = this->_poly.getCoefficient(2);
	b = this->_poly.getCoefficient(1);
	c = this->_poly.getCoefficient(0);
	discriminant = b * b - 4 * a * c;
	if (discriminant > 0)
	{
		double	sqrtD = this->_sqrt(discriminant);
		double	x1 = (-b + sqrtD) / (2 * a);
		double	x2 = (-b - sqrtD) / (2 * a);

		std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;
		if (x1 > x2)
		{
			std::cout << x1 << std::endl;
			std::cout << x2 << std::endl;
		}
		else
		{
			std::cout << x2 << std::endl;
			std::cout << x1 << std::endl;
		}
	}
	else if (discriminant == 0)
	{
		double	x = -b / (2 * a);

		std::cout << "Discriminant is zero, the solution is:" << std::endl;
		std::cout << x << std::endl;
	}
	else
	{
		double	sqrtD = this->_sqrt(-discriminant);
		double	realPart = -b / (2 * a);
		double	imagPart = sqrtD / (2 * a);

		if (imagPart < 0)
			imagPart = -imagPart;
		if (realPart == 0)
			realPart = 0;
		std::cout << "Discriminant is strictly negative, the two complex solutions are:" << std::endl;
		std::cout << realPart << " + " << imagPart << "i" << std::endl;
		std::cout << realPart << " - " << imagPart << "i" << std::endl;
	}
}

void	Solver::solve(void)
{
	int	degree;

	std::cout << "Reduced form: " << this->_poly.toReducedForm() << std::endl;
	degree = this->_poly.getDegree();
	std::cout << "Polynomial degree: " << degree << std::endl;
	if (degree > 2)
	{
		std::cout << "The polynomial degree is strictly greater than 2, I can't solve." << std::endl;
		return ;
	}
	switch (degree)
	{
		case 0:
			this->_solveDegree0();
			break ;
		case 1:
			this->_solveDegree1();
			break ;
		case 2:
			this->_solveDegree2();
			break ;
	}
}
