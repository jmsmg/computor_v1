#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include <map>
#include <string>

class	Polynomial
{
	private:
		std::map<int, double>	_terms;

	public:
		Polynomial();
		Polynomial(const Polynomial &obj);
		Polynomial	&operator=(const Polynomial &obj);
		~Polynomial();

		void		setTerm(int exponent, double coefficient);
		double		getCoefficient(int exponent) const;
		int			getDegree(void) const;
		void		reduce(void);
		std::string	toReducedForm(void) const;
		Polynomial	operator-(const Polynomial &obj) const;
};

#endif
