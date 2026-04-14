#include "Parser.hpp"
#include <sstream>
#include <vector>
#include <cstdlib>

Parser::Parser() : _input("")
{
}

Parser::Parser(const std::string &input) : _input(input)
{
}

Parser::Parser(const Parser &obj)
{
	*this = obj;
}

Parser	&Parser::operator=(const Parser &obj)
{
	if (this != &obj)
	{
		this->_input = obj._input;
	}
	return (*this);
}

Parser::~Parser()
{
}

void	Parser::setInput(const std::string &input)
{
	this->_input = input;
}

static std::string	trim(const std::string &str)
{
	size_t	start;
	size_t	end;

	start = str.find_first_not_of(" \t");
	if (start == std::string::npos)
		return ("");
	end = str.find_last_not_of(" \t");
	return (str.substr(start, end - start + 1));
}

static std::string	removeSpaces(const std::string &str)
{
	std::string	result;

	for (char c : str)
	{
		if (c != ' ' && c != '\t')
			result += c;
	}
	return (result);
}

void	Parser::_parseTerm(const std::string &term, int &exponent, double &coefficient)
{
	std::string	t;
	size_t		starPos;
	std::string	coefStr;
	std::string	varStr;
	size_t		caretPos;

	t = removeSpaces(term);
	if (t.empty())
	{
		coefficient = 0;
		exponent = 0;
		return ;
	}
	starPos = t.find('*');
	if (starPos == std::string::npos)
	{
		coefficient = 0;
		exponent = 0;
		return ;
	}
	coefStr = t.substr(0, starPos);
	varStr = t.substr(starPos + 1);
	coefficient = std::stod(coefStr);
	caretPos = varStr.find('^');
	if (caretPos != std::string::npos)
	{
		std::string	expStr = varStr.substr(caretPos + 1);
		exponent = std::stoi(expStr);
	}
	else
		exponent = 1;
}

Polynomial	Parser::_parseSide(const std::string &side)
{
	Polynomial					poly;
	std::string					s;
	std::vector<std::string>	terms;
	std::string					current;
	bool						firstChar;

	s = trim(side);
	if (s.empty())
		return (poly);
	firstChar = true;
	for (size_t i = 0; i < s.length(); ++i)
	{
		char	c = s[i];

		if ((c == '+' || c == '-') && !firstChar)
		{
			std::string	t = trim(current);
			if (!t.empty())
				terms.push_back(t);
			current.clear();
			if (c == '-')
				current = "-";
		}
		else
		{
			current += c;
			if (c != ' ' && c != '\t')
				firstChar = false;
		}
	}
	std::string	t = trim(current);
	if (!t.empty())
		terms.push_back(t);
	for (const auto &term : terms)
	{
		int		exp;
		double	coef;

		this->_parseTerm(term, exp, coef);
		poly.setTerm(exp, coef);
	}
	return (poly);
}

Polynomial	Parser::parse(void)
{
	size_t		eqPos;
	std::string	left;
	std::string	right;
	Polynomial	leftPoly;
	Polynomial	rightPoly;
	Polynomial	result;

	eqPos = this->_input.find('=');
	if (eqPos == std::string::npos)
		return (Polynomial());
	left = this->_input.substr(0, eqPos);
	right = this->_input.substr(eqPos + 1);
	leftPoly = this->_parseSide(left);
	rightPoly = this->_parseSide(right);
	result = leftPoly - rightPoly;
	result.reduce();
	return (result);
}
