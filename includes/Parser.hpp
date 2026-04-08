#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include "Polynomial.hpp"

class	Parser
{
	private:
		std::string	_input;

		Polynomial	_parseSide(const std::string &side);
		void		_parseTerm(const std::string &term, int &exponent, double &coefficient);

	public:
		Parser();
		Parser(const std::string &input);
		Parser(const Parser &obj);
		Parser	&operator=(const Parser &obj);
		~Parser();

		void		setInput(const std::string &input);
		Polynomial	parse(void);
};

#endif
