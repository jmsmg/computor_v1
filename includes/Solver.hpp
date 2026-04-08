#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "Polynomial.hpp"

class	Solver
{
	private:
		Polynomial	_poly;

		void	_solveDegree0(void);
		void	_solveDegree1(void);
		void	_solveDegree2(void);
		double	_sqrt(double n);

	public:
		Solver();
		Solver(const Polynomial &poly);
		Solver(const Solver &obj);
		Solver	&operator=(const Solver &obj);
		~Solver();

		void	setPolynomial(const Polynomial &poly);
		void	solve(void);
};

#endif
