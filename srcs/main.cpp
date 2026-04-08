#include <iostream>
#include "Parser.hpp"
#include "Solver.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./computor \"equation\"" << std::endl;
		return (1);
	}

	Parser		parser(argv[1]);
	Polynomial	poly = parser.parse();
	Solver		solver(poly);

	solver.solve();
	return (0);
}
